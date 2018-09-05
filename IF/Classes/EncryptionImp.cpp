//
//  EncryptionImp.cpp
//  WarZ
//
//  Created by kakalong on 16/4/18.
//
//

#include "EncryptionImp.hpp"
#include "CCLuaEngine.h"
#include "CCThreadManager.h"
#include "external/unzip/unzip.h"
#include <sys/stat.h>
#include "xxtea/xxtea.h"

#define ENCRYPTION_ENTRY     "encrypt"
#define ENCRYPTION_TEMP_FILE "encrypt_temp.zip"
#define ENCRYPTION_LUAC_FILE "encrypt.luac"

const static bool ENCRYPT_LUAC_USE_XXTEA = true;

EncryptionDownloader::EncryptionDownloader(const string& path):_urlPath(path),Ref() {
    _callback = nullptr;
    _filePath = "";
    _start = false;
    retain();
}

void EncryptionDownloader::setCallback(const PathCallback &callback) {
    _callback = callback;
}

void EncryptionDownloader::_mainThreadCallback(Ref* obj) {
    if (_callback) {
        _callback(_filePath);
    }
    
    release();
}

void EncryptionDownloader::doCallback(const string& error) {
    if (!error.empty()) {
        CCLOG("EncryptionDownloader : %s",error.c_str());
    }
    
    CCThreadManager::getInstance()->runInMainThread(this, callfuncO_selector(EncryptionDownloader::_mainThreadCallback));
}

void EncryptionDownloader::start() {
    if (_start) {
        return;
    }
    
    _start = true;
    
    std::thread([&](){
        // DOWNLOAD FILE
        
        // open file
        auto writePath = FileUtils::getInstance()->getWritablePath();
        auto filePath = writePath + ENCRYPTION_TEMP_FILE;
        auto fp = fopen(filePath.c_str(),"w+");
        if (!fp) {
            doCallback("can not open file to download");
            return;
        }
        
        // start curl
        auto curl = curl_easy_init();
        if (!curl) {
            fclose(fp);
            doCallback("can not init curl");
            return;
        }
        
        // start download
        curl_easy_setopt(curl, CURLOPT_URL, _urlPath.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL,1L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        CURLcode retcode = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
        
        // check download
        if (retcode) {
            auto error = CCCommonUtils::format("curl error : %d",retcode);
            doCallback(error);
            return;
        }
        
        // unzip file
        auto zipFile = unzOpen(filePath.c_str());
        if (!zipFile) {
            doCallback("unzip : can not open zip file");
            return;
        }
        unz_global_info zipInfo;
        if (unzGetGlobalInfo(zipFile, &zipInfo) != UNZ_OK) {
            unzClose(zipFile);
            doCallback("unzip : can not read zip info");
            return;
        }
        static const int ENCRY_BUFFER_SIZE = 8192;
        static int NAME_SIZE   = 512;
        char fileBuffer[ENCRY_BUFFER_SIZE];
        for (uLong i = 0; i < zipInfo.number_entry; ++i) {
            unz_file_info fileInfo;
            char fileName[NAME_SIZE];
            if (unzGetCurrentFileInfo(zipFile, &fileInfo, fileName, NAME_SIZE, nullptr, 0, nullptr, 0) != UNZ_OK) {
                unzClose(zipFile);
                doCallback("unzip : can not read file info");
                return;
            }
            if (unzOpenCurrentFile(zipFile) != UNZ_OK) {
                unzClose(zipFile);
                doCallback("unzip : can not open current file");
                return;
            }
            auto currentFilePath = writePath + fileName;
            auto fpWrite = fopen(currentFilePath.c_str(), "w+");
            if (!fpWrite) {
                unzOpenCurrentFile(zipFile);
                unzClose(zipFile);
                doCallback("unzip : can not open file to write");
                return;
            }
            auto errorCode = UNZ_OK;
            do {
                errorCode = unzReadCurrentFile(zipFile,fileBuffer,ENCRY_BUFFER_SIZE);
                if (errorCode < 0) {
                    // read error
                    unzOpenCurrentFile(zipFile);
                    unzClose(zipFile);
                    fclose(fpWrite);
                    auto error = CCCommonUtils::format("unzip : read file error : %d",errorCode);
                    doCallback(error);
                    return;
                }
                if (errorCode > 0) {
                    // read finish
                    fwrite(fileBuffer, errorCode, 1, fpWrite);
                }
            } while (errorCode > 0);
            fclose(fpWrite);
            unzCloseCurrentFile(zipFile);
            
            // Goto next entry listed in the zip file.
            if ((i+1) < zipInfo.number_entry)
            {
                if (unzGoToNextFile(zipFile) != UNZ_OK)
                {
                    doCallback("unzip : can not read next file");
                    unzClose(zipFile);
                    return;
                }
            }
        }
        unzClose(zipFile);
        
        // mark file path and callback
        _filePath = writePath + ENCRYPTION_LUAC_FILE;
        doCallback("download finish");
        
    }).detach();
}







EncryptionController* EncryptionController::_instance = nullptr;
EncryptionController* EncryptionController::getInstance() {
    if (!_instance) {
        _instance = new EncryptionController();
    }
    
    return _instance;
}

void EncryptionController::purge() {
    _instance = nullptr;
    
    if (_downloader) {
        // in downloading
        _downloader->setCallback(nullptr);
        _downloader->release();
    }
    
    if (_callback) {
        // wait for callback
        doCallback(false);
    }
    
    delete this;
}

EncryptionController::EncryptionController() {
    _callback = nullptr;
    _downloadFinish = false;
    _downloader = nullptr;
}

const string EncryptionController::encrypt(const string &content,int index) {
    if (!_downloadFinish) {
        CCLOG("EncryptionImp : not init!");
        return "";
    }
    
    string ret("");
    
    // check content
    if (content.empty()) {
        CCLOG("EncryptionImp : content empty!");
        return ret;
    }
    
    // check lua state
    auto engine = LuaEngine::getInstance();
    auto state = engine->getLuaStack()->getLuaState();
    
    if (!state) {
        CCLOG("EncryptionImp : lua state error!");
        return ret;
    }
    
    //    // check lua file
    //    if (!FileUtils::getInstance()->isFileExist(_filePath)) {
    //        CCLOG("EncryptionImp : lua file not exist!");
    //        return ret;
    //    }
    //
    //    engine->executeScriptFile(_filePath.c_str());
    
    lua_getglobal(state, ENCRYPTION_ENTRY);
    lua_pushstring(state, content.c_str());
    lua_pushinteger(state, index);
    
    // lua call
    if (lua_pcall(state, 2, 1, 0)) {
        CCLOG("EncryptionImp : lua runtime error : %s",lua_tostring(state, -1));
    } else if (!lua_isstring(state, -1)) {
        CCLOG("EncryptionImp : lua return type error!");
    } else {
        ret.append(lua_tostring(state, -1));
    }
    
    lua_pop(state, 1);
    return ret;    
}

void EncryptionController::dump() {
    string ret("");
    
    // check lua state
    auto engine = LuaEngine::getInstance();
    auto state = engine->getLuaStack()->getLuaState();
    
    if (!state) {
        CCLOG("EncryptionController : lua state error!");
        return;
    }
    
    lua_getglobal(state, "dump");
    string file = FileUtils::getInstance()->getWritablePath() + ENCRYPTION_LUAC_FILE;
    lua_pushstring(state, file.c_str());
    
    // lua call
    if (lua_pcall(state, 1, 1, 0)) {
        CCLOG("EncryptionController : lua runtime error : %s",lua_tostring(state, -1));
    } else if (!lua_isstring(state, -1)) {
        CCLOG("EncryptionController : lua return type error!");
    } else {
        ret.append(lua_tostring(state, -1));
    }
    
    lua_pop(state, 1);
    
    // do xxtea encrypt
    ssize_t fileSize = 0;
    auto readFile = FileUtils::getInstance()->getFileData(ret, "rb", &fileSize);
    xxtea_long xxteaFileSize = 0;
    unsigned char xxteaKey[] = "xxtea_test_for_warz_the_key";
    auto xxteaFile = xxtea_encrypt(readFile, fileSize, xxteaKey, sizeof(xxteaKey), &xxteaFileSize);
    auto fp = fopen(ret.c_str(), "wb");
    fwrite(xxteaFile, xxteaFileSize, 1, fp);
    fclose(fp);
    
    free(readFile);
    free(xxteaFile);
    
    //    // try to run the dump
    //    engine->executeScriptFile(ret.c_str());
    //
    //    lua_getglobal(state, "encrypt");
    //    lua_pushstring(state, ret.c_str());
    //    lua_pushinteger(state, 97);
    //    string testRet = "";
    //    // lua call
    //    if (lua_pcall(state, 2, 1, 0)) {
    //        CCLOG("EncryptionImp : lua runtime error : %s",lua_tostring(state, -1));
    //    } else if (!lua_isstring(state, -1)) {
    //        CCLOG("EncryptionImp : lua return type error!");
    //    } else {
    //        testRet.append(lua_tostring(state, -1));
    //    }
    //
    //    lua_pop(state, 1);
    //
    //    CCLOG("testRet : %s",testRet.c_str());
    //
    //    return;
    
    // start curl
    auto curl = curl_easy_init();
    if (!curl) {
        CCLOG("EncryptionController : curl not init");
        return;
    }
    
    struct curl_httppost *formpost = nullptr;
    struct curl_httppost *lastptr  = nullptr;
    struct curl_slist *headerlist  = nullptr;
    static const char buff[] = "Expect:";
    
    curl_formadd(&formpost, &lastptr,
                 CURLFORM_COPYNAME, "file",
                 CURLFORM_FILE, ret.c_str(),
                 CURLFORM_FILENAME, "encrypt.luac",
                 CURLFORM_END);
    
    headerlist = curl_slist_append(headerlist, buff);
    // start download
    curl_easy_setopt(curl, CURLOPT_URL, "https://10.0.0.210:12321/uploadByteCode");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL,1L);
    CURLcode retcode = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    
    curl_formfree(formpost);
    curl_slist_free_all (headerlist);
    
    // check download
    if (retcode) {
        CCLOG("EncryptionController : curl error : %d",retcode);
        return;
    }
}

void EncryptionController::loadString(const string& data) {
    if (_downloader || _callback) {
        CCLOG("EncryptionController : in downloading!");
        return;
    }
    
    _downloadFinish = true;
    string path = "";
    
    doLuaBuffer((unsigned char*)data.data(), data.size(), path);
}

void EncryptionController::download(const string& path,const BoolCallback &callback) {
    if (_downloadFinish) {
        CCLOG("EncryptionController : already init!");
        return;
    }
    
    if (_downloader || _callback) {
        CCLOG("EncryptionController : in downloading!");
        return;
    }
    
    _downloader = new EncryptionDownloader(path);
    _downloader->setCallback([&](const string& path){
        auto downloader = _downloader;

        _downloader = nullptr;
        
        if (path.empty()) {
            // return empty , call failed
            doCallback(false);
        } else {
            // load lua file
            loadLuaBuffer(path);
            _downloadFinish = true;
            doCallback(true);
        }
        
        downloader->release();
    });
    _downloader->start();
    
    _callback = callback;
}

void EncryptionController::doCallback(bool success) {
    if (_callback) {
        auto callback = _callback;
        _callback = nullptr;
        callback(success);
    }
}

void EncryptionController::loadLuaBuffer(const string& path) {
    ssize_t fileSize = 0;
    auto fileData = FileUtils::getInstance()->getFileData(path, "rb", &fileSize);
    doLuaBuffer(fileData, fileSize, path);
    free(fileData);
}
void EncryptionController::doLuaBuffer(unsigned char *fileData, ssize_t fileSize, const string& path) {
    auto state = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    
    int r = 0;

    if (ENCRYPT_LUAC_USE_XXTEA) {
        // decrypt XXTEA
        xxtea_long len = 0;
        unsigned char xxteaKey[] = "xxtea_test_for_warz_the_key";
        unsigned char* result = xxtea_decrypt(fileData,
                                              (xxtea_long)fileSize,
                                              (unsigned char*)xxteaKey,
                                              (xxtea_long)sizeof(xxteaKey),
                                              &len);
        r = luaL_loadbuffer(state, (char*)result, len, path.c_str());
        free(result);
    } else {
        r = luaL_loadbuffer(state, (char*)fileData, fileSize, path.c_str());
    }
    
    LuaEngine::getInstance()->getLuaStack()->executeFunction(0);
    
#if defined(COCOS2D_DEBUG) && COCOS2D_DEBUG > 0
    if (r)
    {
        switch (r)
        {
            case LUA_ERRSYNTAX:
                CCLOG("[LUA ERROR] load \"%s\", error: syntax error during pre-compilation.", path.c_str());
                break;
                
            case LUA_ERRMEM:
                CCLOG("[LUA ERROR] load \"%s\", error: memory allocation error.", path.c_str());
                break;
                
            case LUA_ERRFILE:
                CCLOG("[LUA ERROR] load \"%s\", error: cannot open/read file.", path.c_str());
                break;
                
            default:
                CCLOG("[LUA ERROR] load \"%s\", error: unknown.", path.c_str());
        }
    }
#endif
}



















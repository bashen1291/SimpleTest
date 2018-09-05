//
//  EncryptionImp.hpp
//  WarZ
//
//  Created by kakalong on 16/4/18.
//
//

#ifndef EncryptionImp_hpp
#define EncryptionImp_hpp

#include "CommonInclude.h"

typedef function<void(const string)> PathCallback;

class EncryptionDownloader : public Ref{
public:
    EncryptionDownloader(const string& urlPath);
    
    void setCallback(const PathCallback& callback);
    
    void start();
    
    void _mainThreadCallback(Ref* obj);
    
private:
    void doCallback(const string& error);
    
    PathCallback _callback;
    string _urlPath;
    string _filePath;
    bool _start;
};

typedef function<void(bool)> BoolCallback;

class EncryptionController {
public:
    static EncryptionController* getInstance();
    
    void download(const string& path,const BoolCallback& callback);
    
    void loadString(const string& data);
    
    const string encrypt(const string& content,int index);
    
    void dump();
    
    void purge();
    
private:
    EncryptionController();
    
    void doCallback(bool success);
    
    void loadLuaBuffer(const string& path);
    void doLuaBuffer(unsigned char * data,ssize_t size,const string& path);
            
    BoolCallback _callback;
    
    bool _downloadFinish;
    
    EncryptionDownloader* _downloader;
public:
    static EncryptionController* _instance;
};

#endif /* EncryptionImp_hpp */

//
//  encrypt.cpp
//  WarZ
//
//  Created by Kai Guo on 16/4/19.
//
//

#include "encrypt.hpp"
#include <stdio.h>
#include "CommonInclude.h"

#include <stdlib.h>
#include <string>
#include <zlib.h>

bool aes_encode_buf(const unsigned char* sourcestr, size_t len,  const char *key, std::vector<unsigned char>& result )
{
    AES_KEY aes;
    if(AES_set_encrypt_key((unsigned char*)key, 128, &aes) < 0)
    {
        return false;
    }

    size_t out_len = ((len - 1) / 16 + 1)* 16;
    unsigned char* srcResizeBuffer = (unsigned char*)sourcestr;
    if( out_len != len ) {
        srcResizeBuffer = (unsigned char *)malloc(sizeof(unsigned char) * out_len);
        memset(srcResizeBuffer + out_len - 16, 0, 16);
        memcpy(srcResizeBuffer ,sourcestr, len);
    }
    result.resize(out_len);
    unsigned char iv[AES_BLOCK_SIZE+1] = "1234567890123456";
    AES_cbc_encrypt(srcResizeBuffer, &result[0], out_len, &aes, (unsigned char*)iv, AES_ENCRYPT);
    if( srcResizeBuffer != sourcestr )
    {
        free(srcResizeBuffer);
    }
    return true;
}

bool aes_encode_buf_with_compress(const unsigned char* sourcestr, size_t len,  const char *key, std::vector<unsigned char>& result )
{
    vector<unsigned char> compressedBuf;
    long unsigned int  sizeCompressed = len + (len / 100) + 12;
    compressedBuf.resize(sizeCompressed);
    memset (compressedBuf.data(), 0x00, sizeCompressed);
    compress(compressedBuf.data(), &sizeCompressed, sourcestr, len);
    
//    result.clear();
//    result.insert(result.end(), compressedBuf.begin(), compressedBuf.begin() + sizeCompressed);
    
    AES_KEY aes;
    if(AES_set_encrypt_key((unsigned char*)key, 128, &aes) < 0)
    {
        return false;
    }
    len = sizeCompressed;
    size_t out_len = ((len - 1) / 16 + 1)* 16;
    unsigned char* srcResizeBuffer = (unsigned char*)compressedBuf.data();
    if( out_len != len ) {
        srcResizeBuffer = (unsigned char *)malloc(sizeof(unsigned char) * out_len);
        memset(srcResizeBuffer + out_len - 16, 0, 16);
        memcpy(srcResizeBuffer ,compressedBuf.data(), len);
    }
    result.resize(out_len);
    unsigned char iv[AES_BLOCK_SIZE+1] = "1234567890123456";
    AES_cbc_encrypt(srcResizeBuffer, &result[0], out_len, &aes, (unsigned char*)iv, AES_ENCRYPT);
    if( srcResizeBuffer != compressedBuf.data() )
    {
        free(srcResizeBuffer);
    }
    

    
    return true;
}
bool aes_decode_buf_with_uncompress(const unsigned char* sourcestr, size_t len,  const char *key, std::vector<unsigned char>& result );
bool aes_decode_buf(const unsigned char* sourcestr, size_t len,  const char *key, std::vector<unsigned char>& result )
{
    AES_KEY aes;
    if(AES_set_decrypt_key((unsigned char*)key, 128, &aes) < 0)
    {
        return false;
    }
    
    size_t out_len = ((len - 1) / 16 + 1)* 16;
    unsigned char* srcResizeBuffer = (unsigned char*)sourcestr;
    if( out_len != len ) {
        srcResizeBuffer = (unsigned char *)malloc(sizeof(unsigned char) * out_len);
        memset(srcResizeBuffer + out_len - 16, 0, 16);
        memcpy(srcResizeBuffer ,sourcestr, len);
    }
    result.resize(out_len);

    unsigned char iv[AES_BLOCK_SIZE+1] = "1234567890123456";
    AES_cbc_encrypt(srcResizeBuffer, &result[0], out_len, &aes, (unsigned char*)iv, AES_DECRYPT);
    if( srcResizeBuffer != sourcestr )
    {
        free(srcResizeBuffer);
    }
    
    return true;
}

bool aes_decode_buf_with_uncompress(const unsigned char* sourcestr, size_t len,  const char *key, std::vector<unsigned char>& result )
{
    AES_KEY aes;
    if(AES_set_decrypt_key((unsigned char*)key, 128, &aes) < 0)
    {
        return false;
    }
    
    size_t out_len = ((len - 1) / 16 + 1)* 16;
    unsigned char* srcResizeBuffer = (unsigned char*)sourcestr;
    if( out_len != len ) {
        srcResizeBuffer = (unsigned char *)malloc(sizeof(unsigned char) * out_len);
        memset(srcResizeBuffer + out_len - 16, 0, 16);
        memcpy(srcResizeBuffer ,sourcestr, len);
    }
    result.resize(out_len);
    
    unsigned char iv[AES_BLOCK_SIZE+1] = "1234567890123456";
    AES_cbc_encrypt(srcResizeBuffer, &result[0], out_len, &aes, (unsigned char*)iv, AES_DECRYPT);
    if( srcResizeBuffer != sourcestr )
    {
        free(srcResizeBuffer);
    }
    
    vector<unsigned char> uncompressbuffer;
    unsigned long int sizeUncompressed = 0;
    unsigned long int sizeAreaUncompressed = out_len * 4;
    do
    {
        uncompressbuffer.resize(sizeAreaUncompressed);
        memset (uncompressbuffer.data(), 0x00, uncompressbuffer.size());
        
        sizeUncompressed = sizeAreaUncompressed;
        long int res = uncompress(uncompressbuffer.data(), &sizeUncompressed, (unsigned char*)result.data(), (uLong)out_len);
        
        if (res == Z_BUF_ERROR)
        {
            sizeAreaUncompressed += (unsigned long)out_len;
            continue;
        }
        break;
    } while (true);
    vector<unsigned char> tmp;
    result.swap(tmp);
    result.insert(result.end(), uncompressbuffer.begin(), uncompressbuffer.begin() + sizeUncompressed);
    
    return true;
}

char *aes_encode(const char *sourcestr, const char *key = "")
{
//    if (strcmp(key, "") == 0) key = aeskey;

//    unsigned char iv[AES_BLOCK_SIZE+1] = "6543210987654321";  // 注意，iv绝对不能是const的，否则会段错误
    unsigned char * out = nullptr;
    char * sstr = nullptr;
    char * out2 = nullptr;
    
    do {
            
        AES_KEY aes;
        if(AES_set_encrypt_key((unsigned char*)key, 128, &aes) < 0)
        {
            break;
        }
        int len = strlen(sourcestr);
            
        unsigned char iv[AES_BLOCK_SIZE+1] = "1234567890123456";



        /* 计算补0后的长度 */
        int out_len = ((len - 1) / 16 + 1)* 16;
        sstr = (char *)malloc(sizeof(char) * out_len + 1);

        out = (unsigned char *)malloc(out_len + 1);
        if (out == NULL) {
            break;
        }
        /* 补0 */
        memset(sstr, 0, out_len+1);
        strcpy(sstr, sourcestr);
        AES_cbc_encrypt((unsigned char*)sstr, out, out_len, &aes, (unsigned char*)iv, AES_ENCRYPT);
        /* 这里的长度一定要注意，不能用strlen来获取，加密后的字符串中可能会包含\0 */

        cocos2d::base64Encode(out, out_len, &out2);

            
    } while (0);
    
    if(out)free(out);
    if(sstr)free(sstr);
    return out2;
}

char *aes_decode(const char *crypttext, const char *key = "")
{
    unsigned char* cryptRaw = nullptr;
    char *out = nullptr;
do {
//    if (strcmp(key, "") == 0) key = aeskey;
    unsigned char iv[AES_BLOCK_SIZE+1] = "1234567890123456";

    int cryptRaw_len = cocos2d::base64Decode( (const unsigned char*)crypttext,strlen(crypttext), &cryptRaw);
    if(!cryptRaw_len)break;
        
    out = (char *) malloc(sizeof(char) * cryptRaw_len + 1);
    if(!out)break;
        
    memset(out, 0, cryptRaw_len + 1);
//    memset(out, 0, out_len + 1);
    AES_KEY aes;
    if(AES_set_decrypt_key((unsigned char*)key, 128, &aes) < 0)
    {
        break;
    }
    
    AES_cbc_encrypt((unsigned char*)cryptRaw, (unsigned char*)out, cryptRaw_len, &aes, (unsigned char*)iv, AES_DECRYPT);
    
} while(0);
    if(cryptRaw)free(cryptRaw);
    return out;
}

char *aes_decode_gzip(const char *crypttext, const char *key = "")
{
    unsigned char* cryptRaw = nullptr;
    unsigned char* gzipCryptRaw = nullptr;
    char *out = nullptr;
    do {
        //    if (strcmp(key, "") == 0) key = aeskey;
        unsigned char iv[AES_BLOCK_SIZE+1] = "1234567890123456";
        
        int gzipCryptRaw_len = cocos2d::base64Decode( (const unsigned char*)crypttext,strlen(crypttext), &gzipCryptRaw);
        if(!gzipCryptRaw_len)break;
        
        int cryptRaw_len = ZipUtils::inflateMemory((unsigned char*)gzipCryptRaw, gzipCryptRaw_len, &cryptRaw);
        if (!cryptRaw_len) {
            break;
        }
        
        out = (char *) malloc(sizeof(char) * cryptRaw_len + 1);
        if(!out)break;
        
        memset(out, 0, cryptRaw_len + 1);
        //    memset(out, 0, out_len + 1);
        AES_KEY aes;
        if(AES_set_decrypt_key((unsigned char*)key, 128, &aes) < 0)
        {
            break;
        }
        
        AES_cbc_encrypt((unsigned char*)cryptRaw, (unsigned char*)out, cryptRaw_len, &aes, (unsigned char*)iv, AES_DECRYPT);
        
    } while(0);
    if(cryptRaw)free(cryptRaw);
    if(gzipCryptRaw)free(gzipCryptRaw);
    return out;
}

const char* getSpecString() {
    static const char* pwd = "BdbiPmcqruPmcqBdbiuJwGz8";
    return &pwd[8];
}

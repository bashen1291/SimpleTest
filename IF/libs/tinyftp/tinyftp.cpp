/***************************************************************************
 *            connections.c
 *
 *  Copyright 2005 Dimitur Kirov
 *  dkirov@gmail.com
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#include "cocos2d.h"
#include <stdio.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <assert.h>
#include <netdb.h>
#include <errno.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <mach/error.h>
#else
//#include <error.h>
#endif
#include "tinyftp.h"

#include <stdio.h>
#include <stddef.h>

#ifdef __cplusplus
//extern "C"
//{
#endif

    enum {
        FALSE=false,
        TRUE=true
    };

    
    enum {
        CMD_USER,
        CMD_PASS,
        CMD_ACCT,
        CMD_CWD,
        CMD_CDUP,
        CMD_SMNT,
        CMD_QUIT,
        CMD_REIN,
        CMD_PORT,
        CMD_PASV,
        CMD_TYPE,
        CMD_STRU,
        CMD_MODE,
        CMD_RETR,
        CMD_STOR,
        CMD_STOU,
        CMD_APPE,
        CMD_ALLO,
        CMD_REST,
        CMD_RNFR,
        CMD_RNTO,
        CMD_ABOR,
        CMD_DELE,
        CMD_RMD,
        CMD_MKD,
        CMD_PWD,
        CMD_LIST,
        CMD_NLST,
        CMD_SITE,
        CMD_SYST,
        CMD_STAT,
        CMD_HELP,
        CMD_NOOP,
        CMD_UNKNOWN,
        CMD_EMPTY,
        CMD_CLOSE
    };
    
    /*
     Statichni funkcii za optimalna obrabotka na vhodnie komandi
     */
    static void set_data(char *src,char *dest) {
        //dest[0] = '\0';
        int i=0,y=0;
        bool hasbegun = FALSE;
        for(;;i++) {
            if(hasbegun==TRUE) {
                dest[y]=src[i];
                if(src[i]=='\0' || src[i]=='\n' || src[i]=='\r')
                    break;
                y++;
            } else {
                if(src[i]==' ' || src[i]=='    ')
                    continue;
                else {
                    dest[0]=src[i];
                    y=1;
                    hasbegun=TRUE;
                }
            }
        }
        dest[y]='\0';
    }
    
    static bool cmp2(char c1,char c2,char d1,char d2) {
        if(c1==d1 && c2 == d2)
            return TRUE;
        return FALSE;
    }
    static bool cmp3(char c1,char c2,char c3,char d1,char d2,char d3) {
        if(cmp2(c1,c2,d1,d2) && c3==d3)
            return TRUE;
        return FALSE;
    }
    
    static bool _cmp2(char c1,char c2,char *d,char *d1) {
        if(d[0]=='\0')
            return FALSE;
        if(d[1]=='\0')
            return FALSE;
        if(!cmp2(c1,c2,d[0],d[1]))
            return FALSE;
        set_data(d+2,d1);
        return TRUE;
    }
    static bool _cmp1(char c1,char *d,char *d1) {
        if(c1 != d[0])
            return FALSE;
        set_data(d+1,d1);
        return TRUE;
    }
    
    static bool _cmp3(char c1,char c2,char c3,char *d,char *d1) {
        if(d[0]=='\0')
            return FALSE;
        if(d[1]=='\0')
            return FALSE;
        if(d[2]=='\0')
            return FALSE;
        if(!cmp3(c1,c2,c3,d[0],d[1],d[2]))
            return FALSE;
        set_data(d+3,d1);
        return TRUE;
    }
    static int parse_input(char *input_buff,char *data_buff) {
        if(input_buff==NULL)
            return CMD_EMPTY;
        
        //To avoid Warning "not used"
        parse_input(NULL,NULL);
        
        int len = strlen(input_buff);
        if(len<3)
            return CMD_UNKNOWN;
        switch(input_buff[0]) {
            case 'A':
                switch(input_buff[1]) {
                    case 'B':
                        if(_cmp2('O','R',input_buff+2,data_buff))
                            return CMD_ABOR;
                    case 'C':
                        if(_cmp2('C','T',input_buff+2,data_buff))
                            return CMD_ACCT;
                    case 'L':
                        if(_cmp2('L','O',input_buff+2,data_buff))
                            return CMD_ALLO;
                    case 'P':
                        if(_cmp2('P','E',input_buff+2,data_buff))
                            return CMD_APPE;
                        return CMD_UNKNOWN;
                }
            case 'C':
                if(_cmp2('W','D',input_buff+1,data_buff))
                    return CMD_CWD;
                else if(_cmp3('D','U','P',input_buff+1,data_buff))
                    return CMD_CDUP;
                return CMD_UNKNOWN;
                
            case 'D':
                if(_cmp3('E','L','E',input_buff+1,data_buff))
                    return CMD_DELE;
                return CMD_UNKNOWN;
            case 'H':
                if(_cmp3('E','L','P',input_buff+1,data_buff))
                    return CMD_HELP;
                return CMD_UNKNOWN;
            case 'L':
                if(_cmp3('I','S','T',input_buff+1,data_buff))
                    return CMD_LIST;
                return CMD_UNKNOWN;
            case 'M':
                switch(input_buff[1]) {
                    case 'K':
                        if(_cmp1('D',input_buff+2,data_buff))
                            return CMD_MKD;
                    case 'O':
                        if(_cmp2('D','E',input_buff+2,data_buff))
                            return CMD_MODE;
                        return CMD_UNKNOWN;
                }
            case 'N':
                switch(input_buff[1]) {
                    case 'L':
                        if(_cmp2('S','T',input_buff+2,data_buff))
                            return CMD_NLST;
                    case 'O':
                        if(_cmp2('O','P',input_buff+2,data_buff))
                            return CMD_NOOP;
                        return CMD_UNKNOWN;
                }
            case 'P':
                switch(input_buff[1]) {
                    case 'A':
                        if(_cmp1('S',input_buff+2,data_buff))  {
                            if(_cmp1('S',input_buff+3,data_buff))
                                return CMD_PASS;
                            if(_cmp1('V',input_buff+3,data_buff))
                                return CMD_PASV;
                            return CMD_UNKNOWN;
                        }
                    case 'O':
                        if(_cmp2('R','T',input_buff+2,data_buff))
                            return CMD_PORT;
                    case 'W':
                        if(_cmp1('D',input_buff+2,data_buff))
                            return CMD_PWD;
                        return CMD_UNKNOWN;
                }
            case 'Q':
                if(_cmp3('U','I','T',input_buff+1,data_buff))
                    return CMD_QUIT;
                return CMD_UNKNOWN;
            case 'R':
                switch(input_buff[1]) {
                    case 'E':
                        switch(input_buff[2]) {
                            case 'I':
                                if(_cmp1('N',input_buff+3,data_buff))
                                    return CMD_REIN;
                            case 'S':
                                if(_cmp1('T',input_buff+3,data_buff))
                                    return CMD_REST;
                            case 'T':
                                if(_cmp1('R',input_buff+3,data_buff))
                                    return CMD_RETR;
                                return CMD_UNKNOWN;
                        }
                        return CMD_UNKNOWN;
                    case 'M':
                        if(_cmp1('D',input_buff+2,data_buff))
                            return CMD_RMD;
                    case 'N':
                        switch(input_buff[2]) {
                            case 'F':
                                if(_cmp1('R',input_buff+3,data_buff))
                                    return CMD_RNFR;
                            case 'T':
                                if(_cmp1('O',input_buff+3,data_buff))
                                    return CMD_RNTO;
                                return CMD_UNKNOWN;
                        }
                        return CMD_UNKNOWN;
                }
            case 'S':
                switch(input_buff[1]) {
                    case 'I':
                        if(_cmp2('T','E',input_buff+2,data_buff))
                            return CMD_SITE;
                    case 'M':
                        if(_cmp2('N','T',input_buff+2,data_buff))
                            return CMD_SMNT;
                    case 'T':
                        switch(input_buff[2]) {
                            case 'A':
                                if(_cmp1('T',input_buff+3,data_buff))
                                    return CMD_STAT;
                            case 'O':
                                if(_cmp1('R',input_buff+3,data_buff))
                                    return CMD_STOR;
                                if(_cmp1('U',input_buff+3,data_buff))
                                    return CMD_STOU;
                            case 'R':
                                if(_cmp1('U',input_buff+3,data_buff))
                                    return CMD_STRU;
                        }
                        return CMD_UNKNOWN;
                    case 'Y':
                        if(_cmp2('S','T',input_buff+2,data_buff))
                            return CMD_SYST;
                        return CMD_UNKNOWN;
                }
            case 'T':
                if(_cmp3('Y','P','E',input_buff+1,data_buff))
                    return CMD_TYPE;
                return CMD_UNKNOWN;
            case 'U':
                if(_cmp3('S','E','R',input_buff+1,data_buff))
                    return CMD_USER;
                return CMD_UNKNOWN;
                return CMD_UNKNOWN;
        }
        return CMD_UNKNOWN;
    }
#ifdef __cplusplus
//}
#endif



/**
 * Check if directory exists. If it exists return an open descriptor to that directory.
 * If it is not a directory, or does not exists return NULL.
 */
static DIR * ensure_dir_exists(int sock,const char*path) {
    DIR *dir =opendir(path) ;
    if(dir==NULL) {
        printf("Error openning directory \"%s\", error was:\n  ",path);
        send_repl(sock,REPL_550);
        switch(errno) {
            case EACCES:
                printf("Access denied.\n");
                closedir(dir);
                return NULL;
            case EMFILE:
                printf("Too many file descriptors in use by process.\n");
                closedir(dir);
                return NULL;
            case ENFILE:
                printf("Too many files are currently open in the system.\n");
                closedir(dir);
                break;
            case ENOENT:
                printf("Directory does not exist, or is an empty string.\n");
                closedir(dir);
                return NULL;
            case ENOMEM:
                printf("Insufficient memory to complete the operation..\n");
                closedir(dir);
                return NULL;
            default:
            case ENOTDIR:
                printf("\"%s\" is not a directory.\n",path);
                closedir(dir);
                return NULL;
        }
    }
    return dir;
}


/**
 * Writes the file statics in a formated string, given a pointer to the string.
 */
static int write_file(char *line,const char *mode,int num,const char *user,const char * group,int size,const char *date,const char*fl_name) {
    sprintf(line,"%s %3d %-4s %-4s %8d %12s %s\r\n",mode,num,user,group,size,date,fl_name);
    //free(line);
    return 0;
}

/**
 * Check if the given directory is none of ".", or ".."
 */
static bool is_special_dir(const char *dir) {
    if(dir==NULL)
        return TRUE;
    int len = strlen(dir);
    if(len>2)
        return FALSE;
    if(dir[0]!='.')
        return FALSE;
    if(len==1)
        return TRUE;
    if(dir[1]=='.')
        return TRUE;
    return FALSE;
}

/**
 * Write file statics in a line using the buffer from stat(...) primitive
 */
static bool get_file_info_stat(const char *file_name, char *line,struct stat *s_buff){
    char date[16];
    char mode[11]    = "----------";
    line[0]='\0';
    struct passwd * pass_info = getpwuid(s_buff->st_uid);
    if(pass_info!=NULL) {
        struct group * group_info = getgrgid(s_buff->st_gid);
        if(group_info!=NULL) {
            int b_mask = s_buff->st_mode & S_IFMT;
            if(b_mask == S_IFDIR) {
                mode[0]='d';
            } else if(b_mask == S_IFREG){
                mode[0]='-';
            } else {
                return FALSE;
            }
            mode[1] = (s_buff->st_mode & S_IRUSR)?'r':'-';
            mode[2] = (s_buff->st_mode & S_IWUSR)?'w':'-';
            mode[3] = (s_buff->st_mode & S_IXUSR)?'x':'-';
            mode[4] = (s_buff->st_mode & S_IRGRP)?'r':'-';
            mode[5] = (s_buff->st_mode & S_IWGRP)?'w':'-';
            mode[6] = (s_buff->st_mode & S_IXGRP)?'x':'-';
            mode[7] = (s_buff->st_mode & S_IROTH)?'r':'-';
            mode[8] = (s_buff->st_mode & S_IWOTH)?'w':'-';
            mode[9] = (s_buff->st_mode & S_IXOTH)?'x':'-';
            long sttime = s_buff->st_mtime;
            strftime(date,13,"%b %d %H:%M",localtime(&sttime));
            
            write_file(
                       line,mode,s_buff->st_nlink,
                       pass_info->pw_name,
                       group_info->gr_name,
                       s_buff->st_size,date,
                       file_name
                       );
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * Empty function , similara to python's "pass" operator.
 */
static void do_nothing() { if(TRUE==FALSE) do_nothing();}

/**
 * Writes the file statistics in a line "line"
 */
static bool get_file_info(const char *file_name, char *line){
    if(line==NULL)
        return FALSE;
    struct stat s_buff;
    if(is_special_dir(file_name))
        do_nothing();//return FALSE;
    int status = stat(file_name,&s_buff);
    if(status==0) {
        return get_file_info_stat(file_name,line,&s_buff);
    }
    return FALSE;
}

/**
 * Get and send the info for the current directory
 */
bool write_list(int sock, int client_sock, const char *current_dir) {
    
    if(client_sock>0) {
        if(sock!=client_sock) {
            send_repl(sock,REPL_150);
        }
    }
    else {
        if(sock!=client_sock) {
            send_repl(sock,REPL_425);
        }
        return FALSE;
    }
    DIR *dir = ensure_dir_exists(sock,current_dir);
    if(dir==NULL) {
        if(sock!=client_sock) {
            close(client_sock);
            send_repl(sock,REPL_451);
        }
        return FALSE;
    }
    
    char line[300];
    while(1) {
        struct dirent *d_next = readdir(dir);
        if(d_next==NULL)
            break;
        line[0]='\0';
        if(get_file_info(d_next->d_name,line)) {
            if(send_repl_client(client_sock,line)) {
                if(sock!=client_sock)
                    send_repl(sock,REPL_451);
            }
        }
    }
    if(sock!=client_sock) {
        close(client_sock);
        send_repl(sock,REPL_226);
        //free(line);
    }
    //free(line);
    closedir(dir);
    return TRUE;
}

/**
 * Create a directory, called "new_dir"
 */
bool make_dir(int sock,const char *new_dir,char *reply) {
    
    struct stat s_buff;
    int status = stat(new_dir,&s_buff);
    if(status==0) {
        send_repl(sock,REPL_550);
        return FALSE;
    }
    status = mkdir(new_dir,0755);
    if(status!=0) {
        send_repl(sock,REPL_550);
        return FALSE;
    }
    reply[0]='\0';
    int len = sprintf(reply,REPL_257,new_dir);
    reply[len] ='\0';
    send_repl_len(sock,reply,len);
    return TRUE;
}

/**
 * Delete the directory called "removed_dir"
 */
bool remove_dir(int sock,const char *removed_dir) {
    if(is_special_dir(removed_dir)) {
        send_repl(sock,REPL_550);
        return FALSE;
    }
    struct stat s_buff;
    int status = stat(removed_dir,&s_buff);
    if(status!=0) {
        send_repl(sock,REPL_550);
        return FALSE;
    }
    int b_mask = s_buff.st_mode & S_IFMT;
    if(b_mask != S_IFDIR) {
        send_repl(sock,REPL_550);
        return FALSE;
    }
    status = rmdir(removed_dir);
    if(status!=0) {
        send_repl(sock,REPL_550);
        return FALSE;
    }
    send_repl(sock,REPL_250);
    return TRUE;
}

/**
 * Rename a file or directory. If operation is not successfull - return FALSE
 */
bool rename_fr(int sock,const char *from,const char *to) {
    if(is_special_dir(from)) {
        send_repl(sock,REPL_553);
        return FALSE;
    }
    struct stat s_buff;
    int status = stat(from,&s_buff);
    if(status!=0) {
        send_repl(sock,REPL_553);
        return FALSE;
    }
    status = stat(to,&s_buff);
    if(status==0) {
        send_repl(sock,REPL_553);
        return FALSE;
    }
    int b_mask = s_buff.st_mode & S_IFMT;
    if(b_mask == S_IFDIR || b_mask == S_IFREG) {
        int status = rename(from,to);
        if(status!=0) {
            send_repl(sock,REPL_553);
            return FALSE;
        }
    } else {
        send_repl(sock,REPL_553);
        return FALSE;
    }
    send_repl(sock,REPL_250);
    return TRUE;
}

/**
 * Delete a file, given its name
 */
bool delete_file(int sock,const char *delete_file) {
    
    struct stat s_buff;
    int status = stat(delete_file,&s_buff);
    if(status!=0) {
        send_repl(sock,REPL_550);
        return FALSE;
    }
    int b_mask = s_buff.st_mode & S_IFMT;
    if(b_mask != S_IFREG) {
        send_repl(sock,REPL_550);
        return FALSE;
    }
    status = unlink(delete_file);
    if(status!=0) {
        send_repl(sock,REPL_450);
        return FALSE;
    }
    send_repl(sock,REPL_250);
    return TRUE;
}

/**
 * Show stats about a file. If the file is a directory show stats about its content.
 */
bool stat_file(int sock, const char *file_path,char *reply) {
    char line[300];
    struct stat s_buff;
    int status = stat(file_path,&s_buff);
    if(status==0) {
        reply[0]='\0';
        int len = sprintf(reply,REPL_211_STATUS,file_path);
        send_repl_len(sock,reply,len);
        int b_mask = s_buff.st_mode & S_IFMT;
        if(b_mask == S_IFDIR) {
            if(getcwd(line,300)!=NULL) {
                int status = chdir(file_path);
                if(status != 0) {
                    send_repl(sock,REPL_450);
                    //free(line);
                    return FALSE;
                }
                else {
                    if(!write_list(sock, sock, file_path)) {
                        send_repl(sock,REPL_450);
                        return FALSE;
                    }
                    int status = chdir(line);
                    if(status!=0) {
                        send_repl(sock,REPL_450);
                        //free(line);
                        return FALSE;
                    }
                }
            } else {
                send_repl(sock,REPL_450);
                //free(line);
                return FALSE;
                
            }
        } else if(b_mask == S_IFREG){
            if(get_file_info_stat(file_path,line,&s_buff)) {
                if(send_repl_client(sock,line)) {
                    send_repl(sock,REPL_450);
                    //free(line);
                    return FALSE;
                }
            }
        }
        send_repl(sock,REPL_211_END);
    }
    else {
        send_repl(sock,REPL_450);
        return FALSE;
    }
    free(line);
    return TRUE;
}

/**
 * Change current working dir.
 */
bool change_dir(int sock,const char *parent_dir,char *current_dir,char *virtual_dir,char *data_buff) {
    DIR *dir = ensure_dir_exists(sock,data_buff);
    if(dir!=NULL) {
        closedir(dir);
        int status = chdir(current_dir);
        if(status==0) {
            int status = chdir(data_buff);
            if(status == 0) {
                if(getcwd(current_dir,MAXPATHLEN)!=NULL) {
                    send_repl(sock,REPL_250);
                    return TRUE;
                }
            }
        }
    }
    send_repl(sock,REPL_550);
    return FALSE;
}

/**
 * Writes the contet of a file to the given client socket.
 * This is used for file download in ACTIVE mode.
 */
bool retrieve_file(int sock, int client_sock, int type, const char * file_name) {
    char read_buff[SENDBUFSIZE];
    if(client_sock>0) {
        //close(client_sock);
        send_repl(sock,REPL_150);
    }
    else {
        close(client_sock);
        send_repl(sock,REPL_425);
        free(read_buff);
        return FALSE;
    }
    struct stat s_buff;
    int status = stat(file_name,&s_buff);
    if(status!=0) {
        close(client_sock);
        send_repl(sock,REPL_450);
        free(read_buff);
        return FALSE;
    }
    int b_mask = s_buff.st_mode & S_IFMT;
    if(b_mask != S_IFREG){
        close(client_sock);
        send_repl(sock,REPL_451);
        free(read_buff);
        return FALSE;
    }
    char mode[3] ="r ";
    switch(type){
        case 1:
        case 3:
        case 4:
            mode[1]='b';
            break;
        case 2:
        default:
            mode[1]='t';
    }
    
    int fpr = open(file_name,O_RDONLY);
    if(fpr<0) {
        close(client_sock);
        send_repl(sock,REPL_451);
        free(mode);
        free(read_buff);
        return FALSE;
    }
    
    // make transfer unbuffered
    int opt = fcntl(client_sock, F_GETFL, 0);
    if (fcntl(client_sock, F_SETFL, opt | O_ASYNC) == -1)
    {
        send_repl(sock,REPL_426);
        close_connection(client_sock);
        free(read_buff);
        return FALSE;
    }
    while(1){
        int len = read(fpr,read_buff,SENDBUFSIZE);
        if(len>0) {
            send_repl_client_len(client_sock,read_buff,len);
        }
        else {
            break;
        }
    }
    close(fpr);
    send_repl(sock,REPL_226);
    close_connection(client_sock);
    return TRUE;
}

/**
 * Writes a file on the server, given an open client socket descriptor.
 * We are waiting for file contents on this descriptor.
 */
bool stou_file(int sock, int client_sock, int type, int fpr) {
    char read_buff[SENDBUFSIZE];
    if(fpr<0) {
        close_connection(client_sock);
        send_repl(sock,REPL_451);
        free(read_buff);
        return FALSE;
    }
    // make transfer unbuffered
    int opt = fcntl(client_sock, F_GETFL, 0);
    if (fcntl(client_sock, F_SETFL, opt | O_ASYNC) == -1) {
        send_repl(sock,REPL_426);
        close_connection(client_sock);
        free(read_buff);
        return FALSE;
    }
    while(1){
        
        int len = recv(client_sock,read_buff,SENDBUFSIZE,0);
        if(len>0) {
            write(fpr,read_buff,len);
        }
        else {
            break;
        }
    }
    close_connection(client_sock);
    close(fpr);
    send_repl(sock,REPL_226);
    return TRUE;
}

/**
 * Writes a file, given a file path(name and location) and open client socket.
 */
bool store_file(int sock, int client_sock, int type, const char * file_name) {
    char read_buff[SENDBUFSIZE];
    if(client_sock>0) {
        //close(client_sock);
        send_repl(sock,REPL_150);
    }
    else {
        close_connection(client_sock);
        send_repl(sock,REPL_425);
        free(read_buff);
        return FALSE;
    }
    struct stat s_buff;
    int status = stat(file_name,&s_buff);
    if(status==0) {
        int b_mask = s_buff.st_mode & S_IFMT;
        if(b_mask != S_IFREG){
            free(read_buff);
            close_connection(client_sock);
            send_repl(sock,REPL_451);
            
            return FALSE;
        }
    }
    char mode[3] ="w ";
    switch(type){
        case 1:
        case 3:
        case 4:
            mode[1]='b';
            break;
        case 2:
        default:
            mode[1]='t';
    }
    
    int fpr = open(file_name,O_WRONLY|O_CREAT,0644);
    return stou_file(sock, client_sock,type,fpr);
}


int assign_option(int, const char*,struct cmd_opts *,int);
static void print_help_command_line();
int dir_exists(const char *);

/**
 * pars_cmd_args:
 * Parse command line arguments and create the structure #copts with appropriate settings.
 */
int pars_cmd_args(struct cmd_opts *copts,int argc,char *argv[]) {
    int len,i;
    if(argc<2) {
        printf("    USAGE: tinyftp [OPTIONS]\n    Run tinyftp -h for help.\n");
        return 1;
    }
    copts->daemonize    = FALSE;
    copts->listen_any   = TRUE;
    copts->port         = 21;
    copts->userid       = 0;
    copts->chrootdir    = "./";
    copts->max_conn     = 5;
    copts->listen_addr  = NULL;
    
    // remember the current read options. e.g. if the last read argument was "-l"
    // current option is "limit", so we are waiting for a number of concurrent connections.
    int current_option=0;
    for(i=1;i<argc;i++) {
        len = strlen(argv[i]);
        if(len <1)
            continue;
        if(current_option==0) {
            if(argv[i][0]=='-') {
                
                switch(argv[i][1]) {
                        
                    case 'l': // limit
                        if(len>2) {
                            assign_option('l', argv[i]+2, copts,len-2);
                            current_option =0;
                        } else {
                            current_option = 'l';
                        }
                        break;
                    case 'u': //run as user id
                        if(len>2) {
                            assign_option('p', argv[i]+2, copts,len-2);
                        } else {
                            current_option = 'u';
                        }
                        break;
                    case 'p': //port
                        if(len>2) {
                            assign_option('p', argv[i]+2, copts,len-2);
                        } else {
                            current_option =  'p';
                        }
                        break;
                    case 's': //server address
                        if(len>2) {
                            assign_option('s', argv[i]+2, copts,len-2);
                        } else {
                            current_option =  's';
                        }
                        break;
                    case 'c': //chto dir, default ./
                        if(len>2) {
                            assign_option('c', argv[i]+2, copts,len-2);
                        } else {
                            current_option = 'c';
                        }
                        break;
                    case 'd':
                        copts->daemonize = TRUE;
                        break;
                        
                    case 'h':
                    default:
                        print_help_command_line();
                        return -1;
                }
            }
        }
        else {
            if(assign_option(current_option,argv[i],copts,len)!=0) {
                return 1;
            }
            current_option =  0;
        }
    }
    return 0;
}

/**
 * Write a single option in the struct #copts.
 */
int assign_option(int current_option,
                  const char* arg,
                  struct cmd_opts *copts,
                  int len)
{
    int p;
    switch(current_option) {
        case 's': // server address
            if(arg[0]=='0' || arg[0]=='*' || strcmp(arg,"0.0.0.0")==0) {
                copts->listen_any = TRUE;
                copts->listen_addr = NULL;
            } else {
                copts->listen_any = FALSE;
                copts->listen_addr = (char *)arg;
            }
            break;
        case 'p': // server port
            p = toint(arg,TRUE);
            if (p<1 || p > 32768) {
                return 2;
            }
            copts->port = p;
            break;
        case 'l': // limit of the concurrent connections
            p = toint(arg,TRUE);
            if (p<1 || p > 600) {
                printf("Limit should be numeric, in range 1, 600");
                return 3;
            }
            copts->max_conn = p;
            break;
        case 'u': // run as userid
            p = toint(arg,TRUE);
            if (p<0 || p > 99999) {
                printf("User id should be numeric, in range 0, 99999");
                return 4;
            }
            copts->userid = p;
            break;
        case 'c': // current working directory
            if(dir_exists(arg))
                return 5;
            copts->chrootdir = (char*)malloc(sizeof(char *)*len);
            strcpy(copts->chrootdir,arg);
            break;
    }
    return 0;
}

/**
 * dir_exists:
 * Check if directory #path exists. On succes return 0
 */
int dir_exists(const char *path) {
    DIR *dir =opendir(path) ;
    if(dir==NULL) {
        printf("Error openning directory \"%s\", error was:\n  ",path);
        switch(errno) {
            case EACCES:
                printf("Access denied.\n");
                closedir(dir);
                return -1;
            case EMFILE:
                printf("Too many file descriptors in use by process.\n");
                closedir(dir);
                return -1;
            case ENFILE:
                printf("Too many files are currently open in the system.\n");
                closedir(dir);
                break;
            case ENOENT:
                printf("Directory does not exist, or is an empty string.\n");
                closedir(dir);
                return -1;
            case ENOMEM:
                printf("Insufficient memory to complete the operation..\n");
                closedir(dir);
                return -1;
            default:
            case ENOTDIR:
                printf("\"%s\" is not a directory.\n",path);
                closedir(dir);
                return -1;
        }
    }
    closedir(dir);
    return 0;
}

/**
 * Read a string and return its representation as an integer.
 */
int toint(
const char* str,
bool strict)
{
    int len = strlen(str);
    if(len<1) {
        return -1;
    }
    int i;
    int base=1;
    int retval = 0;
    for(i=len-1;i>=0;i--,base *= 10) {
        if(base>=10000) {
            return -1;
        }
        if((int)str[i] >47 && (int)str[i]<58) {
            retval+=base*(str[i]-48);
        } else {
            if(strict)
                return -1;
        }
    }
    return retval;
}

/**
 * Print out to the stdin a help message with a short explanation
 * of the available command line options and usage.
 */
void print_help_command_line() {
    printf("Usage: tinyftp [OPTIONS]\n");
    printf(" -h,\n     Display tinyftp help\n");
    printf(" -d,\n     Daemonize after startup\n");
    printf(" -s [address],\n     Set the server address\n");
    printf(" -p [port],\n     Set the server port \n");
    printf(" -l [limit],\n     Limit to \"[limit]\" concurrent connections\n");
    printf(" -u [userid],\n     Do filesystem operations as \"[userid]\"\n");
    printf(" -c [directory],\n     Default directory \n");
}

int open_connections;
bool max_limit_notify;
int raiseerr(int err_code) {
	printf("Error %d\n",err_code);
	return -1;
}

/** 
 * This is neccessary for future use of glib and gettext based localization.
 */
const char * _(const char* message) {
	return message;
}

/**
 * Guess the transfer type, given the client requested type.
 * Actually in unix there is no difference between binary and 
 * ascii mode when we work with file descriptors.
 * If #type is not recognized as a valid client request, -1 is returned.
 */
int get_type(const char *type) {
	if(type==NULL)
		return -1;
	int len = strlen(type);
	if(len==0)
		return -1;
	switch(type[0]) {
		case 'I':
			return 1;
		case 'A':
			return 2;
		case 'L':
			if(len<3)
				return -1;
			if(type[2]=='7')
				return 3;
			if(type[2]=='8')
				return 4;
	}
	return -1;
}

/**
 * Create a new connection to a (address,port) tuple, retrieved from
 * the PORT command. This connection will be used for data transfers
 * in commands like "LIST","STOR","RETR"
 */
int make_client_connection(int sock_fd,int client_port,const char* client_addr) {
	if(client_port<1) {
		send_repl(sock_fd,REPL_425);
		return -1;
	}
	int sock=-1;
	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(client_addr);
	servaddr.sin_port = htons (client_port);
	if ((sock = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		send_repl(sock,REPL_425);
		raiseerr(15);
		return -1;
	}
	int status = connect (sock, (struct sockaddr *)&servaddr, sizeof (servaddr));
	if(status!=0) {
		send_repl(sock,REPL_425);
		return -1;
	}
	return sock;
}

/**
 * Close the connection to the client and exit the child proccess.
 * Although it is the same as close(sock_fd), in the future it can be used for 
 * logging some stats about active and closed sessions.
 */
void close_conn(int sock_fd) {
	if (close(sock_fd) < 0) { 
		raiseerr (5);
	}
	// exit(0);
}

/**
 * Get the next command from the client socket.
 */
int get_command(int conn_fd,char *read_buff1,char *data_buff) {
	char read_buff[RCVBUFSIZE];
	memset((char *)&read_buff, 0, RCVBUFSIZE);
	read_buff[0]='\0';
	char *rcv=read_buff;
	int cmd_status = -1;
	int recvbuff = recv(conn_fd,read_buff,RCVBUFSIZE,0);
	if(recvbuff<1) {
		return CMD_CLOSE;
	}
	if(recvbuff==RCVBUFSIZE) {
		return CMD_UNKNOWN;
	}
//    printf("Received:%s\n",rcv);
	cmd_status = parse_input(rcv,data_buff);
	return cmd_status;
}

/**
 * A handler, which is called on child proccess exit.
 */
void sig_chld_handler(void) {
	open_connections--;
	while (waitpid(-1, NULL, WNOHANG) > 0);
}

/**
 * Send reply to the client socket, given the reply.
 */
int send_repl(int send_sock,char *msg) {
//    printf("send_repl %s",  msg);
	if (send(send_sock, msg, strlen(msg),0) < 0) {
		raiseerr (4);
		close(send_sock);
//        exit(0);
	}
	return 0;
}

/**
 * Send single reply to the client socket, given the reply and its length.
 */
int send_repl_client_len(int send_sock,char *msg,int len) {
//    printf("send_repl_client_len %.*s", len, msg);
	if (send(send_sock, msg, len,0) < 0) {
		raiseerr (4);
		close(send_sock);
	}
	return 0;
}

/*
Izprashtane na edinishen otgovor do dopulnitelnia socket za transfer
*/
int send_repl_client(int send_sock,char *msg) {
	send_repl_client_len(send_sock,msg,strlen(msg));
	return 0;
}

/**
 * Send single reply to the additional transfer socket, given the raply and its length.
 */
int send_repl_len(int send_sock,char *msg,int len) {
	printf("send_repl_len %.*s", len, msg);
	if (send(send_sock, msg, len,0) < 0) { 
		raiseerr (4);
		close(send_sock);
//        exit(0);
	}
	return 0;
}

/**
 * Parses the results from the PORT command, writes the
 * address in "client_addt" and returnes the port
 */
int parse_port_data(char *data_buff,char *client_addr) {
	client_addr[0]='\0';
	int len=0;
	int port=0;
	int _toint=0;
	char *result;
	result = strtok(data_buff, PORTDELIM);
	_toint=toint(result,FALSE);
	if(_toint<1 || _toint>254)
		return -1;
	len += strlen(result);
	strcpy(client_addr,result);
	client_addr[len]='\0';
	strcat(client_addr,".");
	len++;

	result = strtok(NULL, PORTDELIM);
	_toint=toint(result,FALSE);
	if(_toint<0 || _toint>254)
		return -1;
	len += strlen(result);
	strcat(client_addr,result);
	client_addr[len]='\0';
	strcat(client_addr,".");
	len++;

	result = strtok(NULL, PORTDELIM);
	if(_toint<0 || _toint>254)
		return -1;
	len += strlen(result);
	strcat(client_addr,result);
	client_addr[len]='\0';
	strcat(client_addr,".");
	len++;

	result = strtok(NULL, PORTDELIM);
	if(_toint<0 || _toint>254)
		return -1;
	len += strlen(result);
	strcat(client_addr,result);
	client_addr[len]='\0';
	
	result = strtok(NULL, PORTDELIM);
	len = toint(result,FALSE);
	if(_toint<0 || _toint>255)
		return -1;
	port = 256*len;
	result = strtok(NULL, PORTDELIM);
	len = toint(result,FALSE);
	if(_toint<0 || _toint>255)
		return -1;
	port +=len;
	return port;
}
void print_help(int sock) {
	send_repl(sock,"    Some help message.\r\n    Probably nobody needs help from telnet.\r\n    See rfc959.\r\n");
}
/**
 * Main cycle for client<->server communication. 
 * This is done synchronously. On each client message, it is parsed and recognized,
 * certain action is performed. After that we wait for the next client message
 * 
 */
int interract(int conn_fd,cmd_opts *opts) {
	static int BANNER_LEN = strlen(REPL_220);
	int userid = opts->userid;
	int client_fd=-1;
	int len;
	int _type ;
	int type = 2; // ASCII TYPE by default
	if(userid>0) {
		int status = setreuid(userid,userid);
		if(status != 0) {
			switch(errno) {
				case EPERM:
					break;
				case EAGAIN:
					break;
				default:
					break;
			}
			close_conn(conn_fd);
		}
		
	}
	if(max_limit_notify) {
		send_repl(conn_fd,REPL_120);
		close_conn(conn_fd);
	}
	char current_dir[MAXPATHLEN];
	char parent_dir[MAXPATHLEN];
	char virtual_dir[MAXPATHLEN];
	char reply[SENDBUFSIZE];
	char data_buff[DATABUFSIZE];
	char read_buff[RCVBUFSIZE];
	char *str;
    int  connect_close = 0;
	bool is_loged = FALSE;
	bool state_user = FALSE;
	char rename_from[MAXPATHLEN];
	
	memset((char *)&current_dir, 0, MAXPATHLEN);
	strcpy(current_dir,opts->chrootdir);
	strcpy(parent_dir,opts->chrootdir);
//    free(opts);
	chdir(current_dir);
	if((getcwd(current_dir,MAXPATHLEN)==NULL)) {
		raiseerr(19);
		close_conn(conn_fd);
	}
	memset((char *)&data_buff, 0, DATABUFSIZE);
	memset((char *)&read_buff, 0, RCVBUFSIZE);
	
	reply[0]='\0';
	int client_port = 0;
	char client_addr[ADDRBUFSIZE];

	send_repl_len(conn_fd,REPL_220,BANNER_LEN);
	while(1) {
        if(connect_close) {
            break;
        }
		data_buff[0]='\0';
		int result = get_command(conn_fd,read_buff,data_buff);
		if(result != CMD_RNFR && result != CMD_RNTO && result != CMD_NOOP)
			rename_from[0]='\0';
		switch(result) {
			case CMD_UNKNOWN:
			case -1:
				send_repl(conn_fd,REPL_500);
				break;
			case CMD_EMPTY:
			case CMD_CLOSE:
				close_conn(conn_fd);
                connect_close = 1;
				break;
			case CMD_USER:
				if(data_buff==NULL || strcmp(data_buff,ANON_USER)==0) {
					state_user = TRUE;
					send_repl(conn_fd,REPL_331_ANON);
				}
				else {
					send_repl(conn_fd,REPL_332);
				}
				break;
			case CMD_PASS:
				if(!state_user) {
					send_repl(conn_fd,REPL_503);
				}
				else {
					is_loged = TRUE;
					state_user = FALSE;
					send_repl(conn_fd,REPL_230);
				}
				break;
			case CMD_PORT:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					client_port = parse_port_data(data_buff,client_addr);
					if(client_port<0) {
						send_repl(conn_fd,REPL_501);
						client_port = 0;
					} else {
						send_repl(conn_fd,REPL_200);
					}
				}
				break;
			case CMD_PASV:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					send_repl(conn_fd,REPL_502);
				}
				break;
			case CMD_SYST:
				reply[0]='\0';
				len = sprintf(reply,REPL_215,"UNIX");
				reply[len] = '\0';
				send_repl(conn_fd,reply);
				break;
			case CMD_LIST:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					client_fd = make_client_connection(conn_fd, client_port,client_addr);
					if(client_fd!=-1){
						write_list(conn_fd,client_fd,current_dir);
					}
					client_fd = -1;
				}
				break;
			case CMD_RETR:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					if(data_buff==NULL || strlen(data_buff)==0 || data_buff[0]=='\0') {
						send_repl(conn_fd,REPL_501);
					} else {
						client_fd = make_client_connection(conn_fd, client_port,client_addr);
						if(client_fd!=-1){
							retrieve_file(conn_fd,client_fd, type,data_buff);
						}
						client_fd = -1;
					}
				}
				break;
			case CMD_STOU:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					int fd = mkstemp("XXXXX");
					client_fd = make_client_connection(conn_fd, client_port,client_addr);
					if(client_fd!=-1){
						stou_file(conn_fd,client_fd, type,fd);
					}
					client_fd = -1;
				}
				break;
			case CMD_STOR:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					if(data_buff==NULL || strlen(data_buff)==0 || data_buff[0]=='\0') {
						send_repl(conn_fd,REPL_501);
					} else {
						client_fd = make_client_connection(conn_fd, client_port,client_addr);
						if(client_fd!=-1){
							store_file(conn_fd,client_fd, type,data_buff);
						}
						client_fd = -1;
					}
				}
				break;
			case CMD_SITE:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					if(data_buff==NULL || strlen(data_buff)==0 || data_buff[0]=='\0') {
						send_repl(conn_fd,REPL_501);
					} else {
						send_repl(conn_fd,REPL_202);
					}
				}
				break;
			case CMD_PWD:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					reply[0]='\0';
					len = sprintf(reply,REPL_257_PWD,current_dir);
					reply[len] = '\0';
					send_repl(conn_fd,reply);
				}
				break;
			case CMD_CDUP:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					change_dir(conn_fd,parent_dir,current_dir,virtual_dir,"..");
				}
				break;
			case CMD_CWD:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					if(data_buff==NULL || strlen(data_buff)==0 || data_buff[0]=='\0') {
						send_repl(conn_fd,REPL_501);
					} else {
						change_dir(conn_fd,parent_dir,current_dir,virtual_dir,data_buff);
					}
				}
				break;
			case CMD_QUIT:
				send_repl(conn_fd,REPL_221);
				if(client_fd!=-1){
					close_conn(client_fd);
				}
				close_conn(conn_fd);
				break;
			case CMD_TYPE:
				_type = get_type(data_buff);
				if(_type ==-1) {
					send_repl(conn_fd,REPL_500);
				}
				else {
					type=_type;
					send_repl(conn_fd,REPL_200);
				}
				break;
			case CMD_STAT:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					if(data_buff==NULL || strlen(data_buff)==0 || data_buff[0]=='\0') {
						send_repl(conn_fd,REPL_501);
					}
					else {
						stat_file(conn_fd,data_buff,reply);
					}
				}
				break;
			case CMD_ABOR:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					if(client_fd!=-1){
						close_connection(client_fd);
					} 
					send_repl(conn_fd,REPL_226);
				}
				break;
			case CMD_MKD:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					if(data_buff==NULL || strlen(data_buff)==0 || data_buff[0]=='\0') {
						send_repl(conn_fd,REPL_501);
					} else {
						make_dir(conn_fd,data_buff,reply);
					}
				}
				break;
			case CMD_RMD:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					if(data_buff==NULL || strlen(data_buff)==0 || data_buff[0]=='\0') {
						send_repl(conn_fd,REPL_501);
					} else {
						remove_dir(conn_fd,data_buff);
					}
				}
				break;
			case CMD_DELE:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					if(data_buff==NULL || strlen(data_buff)==0 || data_buff[0]=='\0') {
						send_repl(conn_fd,REPL_501);
					} else {
						delete_file(conn_fd,data_buff);
					}
				}
				break;
			case CMD_RNFR:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					if(data_buff==NULL || strlen(data_buff)==0 || data_buff[0]=='\0') {
						send_repl(conn_fd,REPL_501);
					} else {
						strcpy(rename_from,data_buff);
						send_repl(conn_fd,REPL_350);
					}
				}
				break;
			case CMD_RNTO:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					if(data_buff==NULL || strlen(data_buff)==0 || data_buff[0]=='\0') {
						send_repl(conn_fd,REPL_501);
					} else {
						if(rename_from==NULL || strlen(rename_from)==0 || rename_from[0]=='\0') {
							send_repl(conn_fd,REPL_501);
						} else {
							rename_fr(conn_fd,rename_from,data_buff);
						}
					}
					rename_from[0]='\0';
				}
				break;
			case CMD_NOOP:
				send_repl(conn_fd,REPL_200);
				break;
			case CMD_STRU:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					if(data_buff==NULL || strlen(data_buff)==0 || data_buff[0]=='\0') {
						send_repl(conn_fd,REPL_501);
					} else {
						switch(data_buff[0]) {
							case 'F':
								send_repl(conn_fd,REPL_200);
								break;
							case 'P':
							case 'R':
								send_repl(conn_fd,REPL_504);
								break;
							default:
								send_repl(conn_fd,REPL_501);
							
						}
					}
				}
				break;
			case CMD_HELP:
			//	if(data_buff==NULL || strlen(data_buff)==0 || data_buff[0]=='\0') {
					send_repl(conn_fd,REPL_214);
					print_help(conn_fd);
					send_repl(conn_fd,REPL_214_END);
			//	}
			// XXX separate HELP without arguments from HELP for a single command
				break;
			case CMD_MODE:
				if(!is_loged) send_repl(conn_fd,REPL_530);
				else {
					if(data_buff==NULL || strlen(data_buff)==0 || data_buff[0]=='\0') {
						send_repl(conn_fd,REPL_501);
					} else {
						switch(data_buff[0]) {
							case 'S':
								send_repl(conn_fd,REPL_200);
								break;
							case 'B':
							case 'C':
								send_repl(conn_fd,REPL_504);
								break;
							default:
								send_repl(conn_fd,REPL_501);
							
						}
					}
				}
				break;
			default:
				send_repl(conn_fd,REPL_502);
		}
	}
	
//    free(data_buff);
//    free(read_buff);
//    free(current_dir);
//    free(parent_dir);
//    free(virtual_dir);
//    free(rename_from);
	close_conn(conn_fd);
    open_connections--;
    return 1;
}

/**
 * Close a socket and return a statsu of the close operation.
 * Although it is equivalent to close(connection) in the future it can be used
 * for writing logs about opened and closed sessions.
 */
int close_connection(int connection) {
	return close(connection);
}

/**
 * Creates new server listening socket and make the main loop , which waits
 * for new connections.
 */
int create_socket(struct cmd_opts *opts) {
	if(opts==NULL)
		return 10;
	int status = chdir(opts->chrootdir);
	if(status!=0) {
		raiseerr(15);
	}
	int servaddr_len =  0;
	int connection = 0;
	int sock = 0;
	int pid  = 0;
	open_connections=0;
	
	struct sockaddr_in servaddr;
	pid = getuid();	
	if(pid != 0 && opts->port <= 1024)
	{
		printf(_(" Access denied:\n     Only superuser can listen to ports (1-1024).\n You can use \"-p\" option to specify port, greater than 1024.\n"));
//        exit(1);
        return 0;
	}
	memset((char *)&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = PF_INET;
	if(opts->listen_any==TRUE) {
		servaddr.sin_addr.s_addr =  htonl(INADDR_ANY);
	}
	else if(opts->listen_addr==NULL) {
		return 9;
	} else {
		struct hostent *host = gethostbyname(opts->listen_addr);
		if(host==NULL) {
			printf(_("Cannot create socket on server address: %s\n"),opts->listen_addr);
			return 11;
		}
		bcopy(host->h_addr, &servaddr.sin_addr, host->h_length);
	}
	servaddr.sin_port = htons (opts->port);
	servaddr_len = sizeof(servaddr);
	if ((sock = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		raiseerr(ERR_CONNECT);
		return 1;
	}
	int flag = 1;
	setsockopt(sock, SOL_SOCKET,SO_REUSEADDR,(char *) &flag, sizeof(int));
	
	// remove the Nagle algorhytm, which improves the speed of sending data.
	setsockopt(sock, IPPROTO_TCP,TCP_NODELAY,(char *) &flag, sizeof(int));
	
	if(bind (sock, (struct sockaddr *)&servaddr, sizeof(servaddr))<0) {
		if(opts->listen_any==FALSE) {
			printf(_("Cannot bind address: %s\n"),opts->listen_addr);
		}else {
			printf(_("Cannot bind on default address\n"));
		}
		return raiseerr(8);
	}
	if(listen(sock,opts->max_conn) <0) {
		return raiseerr(2);
	}
	#ifdef __USE_GNU
		signal(SIGCHLD, (sighandler_t )sig_chld_handler);
	#endif
	#ifdef __USE_BSD
		signal(SIGCHLD, (sig_t )sig_chld_handler);
	#endif

	for (;;) {
		max_limit_notify = FALSE;
		
		if ((connection = accept(sock, (struct sockaddr *) &servaddr, (socklen_t*)&servaddr_len)) < 0) {
			raiseerr(3);
			return -1;
		}
#if !defined(ANDROID)
        int set = 1;
        setsockopt(connection, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));
#endif
        if(open_connections >= opts->max_conn) {
//            max_limit_notify=TRUE;

        }
        else {
            open_connections++;
//            auto t = std::thread([opts,connection] {
                interract(connection,opts);
//            });
//            t.detach();
        }
        
        

        
//        interract(connection,opts);
		// pid = fork();
		// if(pid==0) {
		// 	if(open_connections >= opts->max_conn)
		// 		max_limit_notify=TRUE;
		// 	interract(connection,opts);
		// } else if(pid>0) {
		// 	open_connections++;
		// 	assert(close_connection(connection)>=0);
		// }
		// else {
			 
		// 	close(connection);
		// 	close(sock);
		// 	assert(0);
		// }
	}
}

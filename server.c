#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 8096
#define ERROR 42
#define SORRY 43
#define LOG   44

/* valid file extensions */
struct {
    char *ext;
    char *filetype;
} extensions[] = {
    { "gif", "image/gif" },
    { "jpg", "image/jpeg" },
    { "jpeg", "image/jpeg" },
    { "png", "image/png" },
    { "zip", "image/zip" },
    { "gz", "image/gz" },
    { "htm", "text/html" },
    { "html", "text/html"},
    { "txt", "text/plain" },
    {0,0} };

/* logging function */
void log(int type, char *s1, char *s2, int num) {

    int fd;
    char logbuffer[BUFSIZE];
    switch(type) {
        case ERROR: (void)sprintf(logbuffer, "ERROR: %s:%s Errno=%d exiting pid=%d", s1, s2, errno, getpid()); break;
        case SORRY:
            (void)sprintf(logbuffer, "Sorry: %s:%s\r\n",s1,s2);
            (void)write(num, logbuffer, strlen(logbuffer));
            break;
        case LOG:
            (void)sprintf(logbuffer, "INFO: %s:%s:%d",s1,s2,num);
            break;
    }
    /* No checks here, nothing can be done anyway */
    if ((fd=open("nweb.log", O_CREAT | O_WRONLY | O_APPEND, 0644)) >= 0) {
        (void)write(fd,logbuffer,strlen(logbuffer));
        (void)write(fd,"\n",1);
        (void)close(fd);
    }

    if (type==ERROR || type==SORRY) exit(3);
}

/* child web process so we can exit on errors */
void web(int fd, int hit) {
    int j, file_fd, buflen, len;
    long i, ret;
    char *fstr;
    static char buffer[BUFSIZE+1]; /* static so it's initialized zero-filled */

    ret = read(fd,buffer,BUFSIZE); /* read the web request */

    if (ret==0 || ret == -1) {  /* read failure */
        log(SORRY, "failed to read browser request","",fd);
    }

    if (ret>0 && ret<BUFSIZE) { /* successfully read request */ 
        buffer[ret] = 0; /* terminate the buffer */
    } else {
        buffer[0] = 0;
    }

    for (i=0; i<ret; i++) { /* remove CR/LF characters */
        if(buffer[i]=='\r' || buffer[i]=='\n') {
            buffer[i] = '*';
        }
    }
    log(LOG,"request",buffer,hit);

    if (strncmp(buffer,"GET ",4) && strncmp(buffer,"get ",4)) {
        log(SORRY,"Only GET supported",buffer,fd);
    }

    for (i=4;i<BUFSIZE; i++) {
        if (buffer[i]==' ') { /* string is "GET URL ..." */
            buffer[i]=0;
            break;
        }
    }

    /* security protect against parent dir */
    for (j=0; j<i-1;j++) {
        if (buffer[j]=='.' && buffer[j+1]=='.') {
            log(SORRY,"Parent dir not supported",buffer,fd);
        }
    }

    /* root = /index.html */
    if (!strncmp(&buffer[0],"GET /\0",6) || !strncmp(&buffer[0],"get /\0",6)) {
        (void)strcpy(buffer,"GET /index.html");
    }

    /* do we support this file extension? */
    buflen=strlen(buffer);
    fstr = (char *)0;
    for (i=0; extensions[i].ext != 0; i++) {
        len = strlen(extensions[i].ext);
        if (!strncmp(&buffer[buflen-len], extensions[i].ext, len) ) {
            fstr = extensions[i].filetype;
            break;
        }
    }
    if (fstr==0) log(SORRY, "filetype not supported",buffer,fd);

    /* open the file */
    if ((file_fd=open(&buffer[5],O_RDONLY)) == -1) {
        log(SORRY, "failed to open file", &buffer[5],fd);
    }

    log(LOG, "SEND",&buffer[5],hit);
    
    /* send HTTP header */
    (void)sprintf(buffer, "HTTP/1.0 200 OK\r\nContent-Type: %s\r\n\r\n", fstr);
    (void)write(fd,buffer,strlen(buffer));

    /* send file in BUFSIZE blocks */
    while( (ret=read(file_fd,buffer,BUFSIZE))>0) {
        (void)write(fd,buffer,ret);
    }
    log(LOG,"SEND finished","",hit);

#ifdef LINUX
    sleep(1);
#endif
    exit(1);
}

/* main server thread */
main(int argc, char **argv) {

    int i, port, pid, listenfd, socketfd, hit;
    size_t length;
    char *str;

    static struct sockaddr_in cli_addr;
    static struct sockaddr_in serv_addr;

    if (argc<3 || argc>3 || !strcmp(argv[1],"-?")){
        (void)printf("hint: nweb port-number top-directory\n");
        exit(0);
    }

    if( !strncmp(argv[2],"/"   ,2 ) || !strncmp(argv[2],"/etc", 5 ) ||
            !strncmp(argv[2],"/bin",5 ) || !strncmp(argv[2],"/lib", 5 ) ||
            !strncmp(argv[2],"/tmp",5 ) || !strncmp(argv[2],"/usr", 5 ) ||
            !strncmp(argv[2],"/dev",5 ) || !strncmp(argv[2],"/sbin",6) ){
               (void)printf("ERROR: Bad top directory %s, see nweb -?\n",
                  argv[2]);
               exit(3);
    }

    if(chdir(argv[2]) == -1) {
        (void)printf("ERROR: Can't change directory to %s\n",argv[2]);
        exit(4);
    }

    /* become daemon and unstoppable and no zombie children */
    if (fork() != 0) {
        return 0; /* parent returns ok to shell */
    }
    (void)signal(SIGCLD, SIG_IGN); /* ignore child death */
    (void)signal(SIGHUP, SIG_IGN); /* ignore terminal hangup */
    for (i=0; i<32; i++) {
        (void)close(i); /* close open files */
    }
    (void)setpgrp(); /* break from process group */

    log(LOG,"nweb starting",argv[1],getpid());

    /* set up network socket */
    if ((listenfd=socket(AF_INET, SOCK_STREAM,0))<0)
        log(ERROR, "system call","socket",0);
    port=atoi(argv[1]);
    if (port<0||port>60000) {
        log(ERROR, "invalid port number (Try 1->60000)",argv[1],0);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    if (bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        log(ERROR,"system call","bind",0);
    }

    if (listen(listenfd,64)<0) {
        log(ERROR,"system call","listen",0);
    }

    for (hit; ; hit++) {
        length = sizeof(cli_addr);
        if ((socketfd=accept(listenfd, (struct sockaddr *)&cli_addr, &length)) < 0) {
            log(ERROR, "system call", "accept", 0);
        }

        if ((pid=fork())<0) {
            log(ERROR,"system call","fork",0);
        } else {
            if (pid==0) { /* child */
                (void)close(listenfd);
                web(socketfd,hit);
            } else { /* parent */
                (void)close(socketfd);
            }
        }
    }
}





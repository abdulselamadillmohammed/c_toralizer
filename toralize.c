/* toralize.c */
#include "toralize.h"
// Source for shared library function: https://rjordaney.is/lectures/hooking_shared_lib/

/*

function call | ip address | port number
./toralize 1.2.3.4 80

*/

Req *request(struct sockaddr_in *sock2){
    Req *req;

    req = malloc(reqsize);

    req->vn = 4;
    req->cd = 1;
    req->dstport = sock2->sin_port;
    req->dstip = sock2->sin_addr.s_addr;
    strncpy((char *)req->userid, USERNAME, 8);

    return req; 
}

int connect(int s2, const struct sockaddr *sock2, socklen_t address_len){

    int s;
    struct sockaddr_in sock;
    Req *req;
    Res *res;
    char buf[ressize];
    int success;
    char tmp[512];
    int (*p)(int, const struct sockaddr*, socklen_t);

    p = dlsym(RTLD_NEXT, "connect");

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("socket");
    
        return -1;
    }

    sock.sin_family = AF_INET;
    sock.sin_port = htons(PROXYPORT);
    sock.sin_addr.s_addr = inet_addr(PROXY);

    if (p(s, (struct sockaddr *)&sock, sizeof(sock))){
        perror("connect");
        
        return -1;
    }
    printf("Connected to proxy\n");
    req = request((struct sockaddr_in *)sock2);
    write(s, req, reqsize);

    memset(buf, 0, ressize);

    if (read(s, buf, ressize) < 1) {
        perror("read");
        free(req);
        close(s);

        return -1;
    }

    res =(Res *)buf;
    success = (res->cd == 90);

    if (!success){
        fprintf(stderr, "Unable to traverse" 
            "the proxy, error code: %d\n",
        res->cd);

        close(s);
        free(req);

        return -1;
    }

    printf("Connected through the proxy\n");

    // memset(tmp, 0, 512);
    // snprintf(tmp, 511, 
    //     "HEAD / HTTP/1.0\r\n"
    //     "Host: www.networktechnology.org\r\n"
    //     "\r\n"
    // );
    // write(s, tmp, strlen(tmp));
    // memset(tmp, 0, 512);
    // read(s, tmp, 511);
    // printf("'%s'\n", tmp);


    //close(s);

    dup2(s,s2);
    free(req);

    return 0;
}
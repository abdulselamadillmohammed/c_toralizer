/* toralize.c */

#include <stdio.h>

/*

function call | ip address | port number
./toralize 1.2.3.4 80

*/

int main(int argc, char *argv[]){
    char *host;
    int port;

    if (argc < 3){
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        return -1;
    }

    host = argv[1];
    port = argv[2];
    
}
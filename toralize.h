/* toralize.h */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROXY       "127.0.0.1"
#define PROXYPORT   9050

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

/*

		+----+----+----+----+----+----+----+----+----+----+....+----+
		| VN | CD | DSTPORT |      DSTIP        | USERID       |NULL|
		+----+----+----+----+----+----+----+----+----+----+....+----+
    	   1    1      2              4           variable       1

*/
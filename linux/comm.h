#pragma once
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>

#define MAX 128

typedef struct{
    int x;
    int y;
}request_t;


typedef struct{
    int res;
}response_t;



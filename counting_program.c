#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

int main() {
    int i=0;
    while(i< pow(2,32)){
        i++;
    }
    return 0;

}

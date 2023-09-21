#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(){
    pid_t pid1, pid2, pid3;
    struct timespec start1, end1;
    struct timespec start2, end2;
    struct timespec start3, end3;
    double time_taken1, time_taken2, time_taken3;

    struct sched_param param;
    param.sched_priority = 0;
    int scheduler;

    clock_gettime(CLOCK_MONOTONIC, &start1);
    pid1 = fork();
    if (pid1 == 0){
        scheduler = SCHED_FIFO;
        if (sched_setscheduler(0, scheduler, &param) == -1) {
            perror("sched_setscheduler");
            return EXIT_FAILURE;
        }
        execl("./counting_program", "./counting_program", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }
    clock_gettime(CLOCK_MONOTONIC, &end1);
    time_taken1 = (end1.tv_sec - start1.tv_sec) + (end1.tv_nsec - start1.tv_nsec) / 1e9;
    printf("time taken by process 1 using SCHED_FIFO :  %4f seconds\n", time_taken1);
    waitpid(pid1, NULL, 0);
    
    clock_gettime(CLOCK_MONOTONIC, &start2);
    pid2 = fork();
    if (pid2 == 0){
        scheduler = SCHED_RR;
        if (sched_setscheduler(0, scheduler, &param) == -1) {
            perror("sched_setscheduler");
            return EXIT_FAILURE;
        }
        execl("./counting_program", "./counting_program", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }
    clock_gettime(CLOCK_MONOTONIC, &end2);
    time_taken2 = (end2.tv_sec - start2.tv_sec) + (end2.tv_nsec - start2.tv_nsec) / 1e9;
    printf("time taken by process 2 using SCHED_RR :  %4f seconds\n", time_taken2);
    waitpid(pid2, NULL, 0);

    clock_gettime(CLOCK_MONOTONIC, &start3);
    pid3 = fork();
    if (pid3 == 0){
        scheduler = SCHED_OTHER;
        if (sched_setscheduler(0, scheduler, &param) == -1) {
            perror("sched_setscheduler");
            return EXIT_FAILURE;
        }
        execl("./counting_program", "./counting_program", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }
    clock_gettime(CLOCK_MONOTONIC, &end3);
    time_taken3 = (end3.tv_sec - start3.tv_sec) + (end3.tv_nsec - start3.tv_nsec) / 1e9;
    printf("time taken by process 3 using SCHED_OTHER :  %4f seconds\n", time_taken3);
    waitpid(pid3, NULL, 0);

    return 0;
}

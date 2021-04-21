#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

void
Addition(void *arg1, void *arg2)
{   
    // int result = ((*(int*)arg1) + (*(int*)arg2));
    printf(1,"Hello is %d %d.\n",*(int*)arg1, *(int*)arg2);
    // printf(1,"hello %s %s\n", (char*)arg1, (char*)arg2);
    exit();  
}

int
main(int argc, char *argv[])
{
    int ppid = getpid();
    int arg1 = 10;
    int arg2 = 20;
    // char arg1[7] = "Vedant";
    // char arg2[7] = "Kandge";
    printf(1, "Parent PID : %d\n\n", ppid);
    int thread_pid1 = thread_create(Addition, &arg1, &arg2);
    printf(1, "Created thread 1. PID : %d\n\n", thread_pid1);
    // assert(thread_pid1 > 0);
    sleep(100);
    int join_pid = thread_join();
    printf(1, "Joined : %d\n", join_pid);
    exit();
}

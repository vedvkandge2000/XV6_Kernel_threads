#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

void
Hello(void *arg1, void *arg2)
{
    printf(1,"hello %d %d\n", *(int*)arg1, *(int*)arg2);
    // printf(1,"hello %s %s\n", (char*)arg1, (char*)arg2);
    exit();  
}

int
main(int argc, char *argv[])
{
   int arg1 = 1;
   int arg2 = 2;
    // char arg1[7] = "Vedant";
    // char arg2[7] = "Kandge";
    char *stack = sbrk(PGSIZE);
    int r = clone(&Hello,&arg1,&arg2,stack);
    sleep(5);
    int join_pid = thread_join();
    printf(1,"Pid:%d %d\n", r, join_pid);
    exit();
}

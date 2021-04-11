#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

void
Hello(void *arg1, void *arg2)
{
    printf(1,"hello %p %p\n", *(char*)arg1, *(char*)arg2);
    exit();  
}

int
main(int argc, char *argv[])
{
//   int arg1 = 1;
//   int arg2 = 2;
    char arg1[7] = "Vedant";
    char arg2[7] = "Kandge";
    char *stack = sbrk(PGSIZE);
    int r = clone(&Hello,&arg1,&arg2,stack);
    sleep(5);
    printf(1,"Pid:%d\n", r);
    exit();
}

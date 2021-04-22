#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

void
print_result(void *result){
    printf(1,"Addition is %d.\n",*(int*)result);
}

int check_even(int a){
    if(a % 2 == 0){
        return 1;
    }
    else{
        return 0;
    }
}

void
Addition(void *arg1, void *arg2)
{   
    // int result = ((*(int*)arg1) + (*(int*)arg2));
    printf(1,"Hello\n");
    int result = *(int*)arg1 + *(int*)arg2;
    print_result(&result);
    if(check_even(result)){
        printf(1,"Result in Even\n");
    }
    else{
        printf(1,"Result in Odd\n");
    }
    // printf(1,"Addition is %d.\n",);
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
    printf(1, "Parent PID : %d\n", ppid);
    int thread_pid1 = thread_create(&Addition, &arg1, &arg2);
    int join_pid = thread_join();
    printf(1, "Created thread=> PID : %d\n", thread_pid1);
    printf(1, "Joined : %d\n", join_pid);
    exit();
}

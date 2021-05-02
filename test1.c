#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"
typedef struct arg
{
    int a;
    int b;
}arg;

t_lock lock;
int global = 0;
#define NULL (0)

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
Addition(void *arg1)
{   
    arg *ptr = (arg*)arg1;
    int tid = gettid();
    int pid = getpid();
    printf(1,"PID is %d and TID is %d\n",pid,tid);
    int result = ptr->a + ptr->b;
    print_result(&result);
    if(check_even(result)){
        printf(1,"Result in Even\n");
    }
    else{
        printf(1,"Result in Odd\n");
    }
    exit();  
}

void
test_sync()
{   
    t_acquire(&lock);
    global = global + 4;
    t_release(&lock);
    exit();  
}

int
main(int argc, char *argv[])
{
    int pid = getpid();
    arg arg1 = {10,20};
    printf(1, "Parent PID : %d\n", pid);
    //Test1
    
    void *stack = sbrk(PGSIZE);
    int thread_tid1 = clone(Addition, &arg1,stack, CLONE_VM | CLONE_PARENT);
    int join_tid1 = thread_join();
    if(thread_tid1 == join_tid1){
        printf(1,"Test1 Passes\n\n");
    }
    
    //Test4
    void *stack4 = sbrk(PGSIZE);
    lock_init(&lock);
    int t_tid1 = clone(test_sync, NULL,stack4, CLONE_VM | CLONE_FS);
    int join_t_tid1 = thread_join();
    if(t_tid1 == join_t_tid1){
        printf(1,"Global : %d\n", global);
        printf(1,"Test4 Passes\n\n");
    }
    exit();
}

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "mmu.h"
#define NULL (0)
int global = 0;
typedef struct arg
{
    int a;
    int b;
}arg;

t_lock lock;
void
print_result(void *result){
    printf(1,"Addition is %d.\n",*(int*)result);
}

void
print_args(void *arg1){
    
    arg *ptr = (arg*)arg1;
    int tid = gettid();
    int pid = getpid();
    printf(1,"PID is %d and TID is %d\n",pid,tid);
    thread_kill(tid);
    printf(1,"----%d %d----\n", ptr->a, ptr->b);
    exit();
}

void
print_num(){
    t_acquire(&lock);
    int pid = getpid();
    int tid = gettid();
    printf(1, "Pid: %d , Tid: %d\n", pid, tid);
    t_release(&lock);
    exit();
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
    // t_acquire(&lock);
    arg *ptr = (arg*)arg1;
    // char buff[30] = "Hello Sadahhhhhhh!!!";
    // write(ptr->a, buff, 30);
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
    // t_release(&lock);
    exit();  
}

void
test_sync()
{   
    t_acquire(&lock);
    global = global * 4;
    t_release(&lock);
    exit();  
}
void
test_sync2()
{   
    t_acquire(&lock);
    global = global + 2;
    t_release(&lock);
    exit();  
}

int
main(int argc, char *argv[])
{
    int pid = getpid();
    
    printf(1, "Parent PID : %d\n", pid);
    //Test1
    // lock_init(&lock);
    void *stack = malloc(PGSIZE);
  //Checking if stack is page aligned or not
    if((uint)stack % PGSIZE != 0) {
        free(stack);
        stack = malloc(2 * PGSIZE); //guard page
        stack = stack + (PGSIZE - (uint)stack % PGSIZE);
    }
    // int fd = open("new3", O_CREATE | O_RDWR);
    arg arg1 = {10,20};
    int thread_tid1 = clone(Addition, &arg1,stack,CLONE_PARENT);
    int join_tid1 = thread_join();
    printf(1,"Test1 Passed: %d-%d\n\n", thread_tid1,join_tid1);
    // close(fd);
    // char buff[30] = "Hello Sadahhhhhhh!!!";
    // write(fd, buff, 30);
    // int thread_tid2 = thread_create(print_args, &arg1);
    // int join_tid2 = thread_join();
    // if(thread_tid1 == join_tid1 /*&& thread_tid2 == join_tid2*/){
       
    // }
    
    
    //Test2
    // lock_init(&lock);
    // int a = 0;
    // int count = 0;
    // int tid;
    // void *stack3 = malloc(PGSIZE);
    // while (1)
    // {
    //     tid = clone(print_num, NULL,stack3,CLONE_PARENT);
    //     t_acquire(&lock);
    //     if (tid == -1)
    //     {
    //         t_release(&lock);
    //         break;
    //     }
    //     a++;
    //     count++;
    //     t_release(&lock);
    //     // printf(1, "I am Thread: %d\n", tid);
    // }
    // while(a > 0){
    //     thread_join();
    //     a--;
    // }
    // printf(1, "Total thread Created: %d\n",count);
    // printf(1,"Test2 Passes\n\n");

    // // //Test4
    // void *stack1 = malloc(PGSIZE);
    // void *stack2 = malloc(PGSIZE);
    // int t_tid1 = clone(test_sync, NULL, stack1,CLONE_PARENT);
    // int t_tid2 = clone(test_sync2, NULL, stack2, CLONE_PARENT);
    // int join_t_tid1 = thread_join();
    // int join_t_tid2 = thread_join();
    // if(t_tid1 == join_t_tid1 && t_tid2 == join_t_tid2){
    //     printf(1,"Global : %d\n", global);
    //     printf(1,"Test4 Passes\n\n");
    // }
    // printf(1,"ALL TEST PASSED\n");
    exit();
}

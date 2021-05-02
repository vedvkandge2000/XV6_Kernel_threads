#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"
#include "fcntl.h"
typedef struct arg
{
    int a;
    int b;
}arg;

t_lock lock;
int global = 0;
#define NULL (0)
#define MAX_SIZE 100 
int M3[MAX_SIZE][MAX_SIZE]; 
int count = 0;
int r1 = 2;
int c1 = 3;
int M1[2][3] = {
    {1,2,4},
    {4,2,3}
};
int r2 = 3;
int c2 = 1;
int M2[3][1] = {
    {-1},
    {0},
    {1}
};

void Multiply() 
{ 
    int core = count++; 
    for (int i = core * r1 / 3; i < (core + 1) * r1 / 3; i++){
        for (int j = 0; j < c2; j++){
            for (int k = 0; k < r2; k++)  
                M3[i][j] += M1[i][k] * M2[k][j];
        }    
    }
    exit();     
} 

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

void test_exec(){
    char *programName = "echo";
    char *args[] = {programName, "TEST8 PASSED", NULL};
    if(exec(programName, args) < 0){
        printf(1,"Command falied\n");
        exit();
    }
    exit();
}


void
test_9(void *arg1)
{   
    arg *ptr = (arg*)arg1;
    int tid = gettid();
    int pid = getpid();
    char buf[30] = "HopeIsAGoodThing\n";
    char arr[30];
    t_acquire(&lock);
    printf(1,"PID is %d and TID is %d\n",pid,tid);
    write(ptr->a, buf, 19);
    ptr->b = read(ptr->a, arr, 20);
    printf(1, "Bytes Read: %d and content is: %s\n", ptr->b, arr);
    close(ptr->a);
    exit();  
}

int Test1(){
    arg arg1 = {10,20};
    int thread_tid1 = thread_create(Addition, &arg1);
    int join_tid1 = thread_join();
    int thread_tid2 = thread_create(print_args, &arg1);
    int join_tid2 = thread_join();
    if(thread_tid1 == join_tid1 && thread_tid2 == join_tid2){
        printf(1,"TEST1 PASSED\n");
        return 1;
    }
    else{
        printf(1,"TEST1 FAILED\n");
        return 0;
    }
}

int Test2(){
    lock_init(&lock);
    int a = 0;
    int count = 0;
    int tid;
    int pid = getpid();
    printf(1,"PID is %d\n",pid);
    while (1)
    {
        tid = thread_create(print_num, NULL);
        t_acquire(&lock);
        if (tid == -1)
        {
            t_release(&lock);
            break;
        }
        a++;
        count++;
        t_release(&lock);
        // printf(1, "I am Thread: %d\n", tid);
    }
    while(a > 0){
        thread_join();
        a--;
    }
    printf(1, "Total thread Created: %d\n",count);
    printf(1,"TEST2 PASSED\n");
    return 1;
}

int Test3(){
    if (r2 != c1) { 
        printf(1,"Multicantion can not be performed\n"); 
        exit(); 
    }
    
    for (int i = 0; i < 3; i++) { 
        int thread_pid = thread_create(Multiply,NULL); 
        printf(1, "Created thread=> TID : %d\n", thread_pid);
    } 
  
    for (int i = 0; i < 3; i++){
            int join_pid = thread_join();
            printf(1, "Thread Joined : %d\n", join_pid);
    }     
  
    printf(1,"\nResultant matirx ==> %dx%d\n", r1, c2);
    for(int i = 0; i < r1; i++) {
        printf(1,"[ ");
        for(int j = 0; j < c2; j++)  
            printf(1,"%d ",M3[i][j]);
        printf(1,"]\n"); 
    }
    printf(1,"TEST3 PASSED\n");
    return 1;
}

int Test4(){
    int t_tid1 = thread_create(test_sync, NULL);
    int t_tid2 = thread_create(test_sync2, NULL);
    int join_t_tid1 = thread_join();
    int join_t_tid2 = thread_join();
    if(t_tid1 == join_t_tid1 && t_tid2 == join_t_tid2){
        printf(1,"Global : %d\n", global);
        printf(1,"TEST4 PASSED\n");
        return 1;
    }
    else{
        printf(1,"TEST4 FAILED\n");
        return 0;
    }
}

int Test5(){
    arg arg1 = {10,20};
    void *stack = sbrk(PGSIZE);
    int thread_tid1 = clone(Addition, &arg1,stack, CLONE_VM | CLONE_PARENT);
    int join_tid1 = thread_join();
    if(thread_tid1 == join_tid1){
        printf(1,"TEST5 PASSED\n");
        return 1;
    }
    else{
        printf(1,"TEST5 FAILED\n");
        return 0;
    }
}

int Test6(){
    void *stack4 = sbrk(PGSIZE);
    lock_init(&lock);
    int t_tid1 = clone(test_sync, NULL,stack4, CLONE_VM);
    int join_t_tid1 = thread_join();
    if(t_tid1 == join_t_tid1){
        printf(1,"Global : %d\n", global);
        printf(1,"TEST6 PASSED\n");
        return 1;
    }
    else{
        printf(1,"TEST6 FAILED\n");
        return 0;
    }
}

void Test7(){
    int pid;
    pid = fork();
    if(pid == 0){
        arg arg1 = {10,20};
        char *stack = sbrk(PGSIZE);
        int n = clone(&print_args,&arg1,stack,NULL);
        int join_pid = thread_join();
        if(n == join_pid){
            printf(1,"TEST7 PASSED\n");
            exit();
        }
    }
    else
    {
        wait();
    }
}

void Test9(){
    char arr[32];
    int pid = getpid();
    int yes;
    lock_init(&lock);
    printf(1, "Parent PID : %d\n", pid);
    int fd = open("backup", O_CREATE | O_RDWR);
    arg arg1 = {fd, 20};
    void *stack = sbrk(PGSIZE);
    int thread_tid1 = clone(&test_9, &arg1,stack, CLONE_VM);
    int join_tid1 = thread_join();
    yes = read(fd, arr, 20);
    printf(1, "Bytes Read: %d and content is: %s\n", yes, arr);
    if(thread_tid1 == join_tid1){
         printf(1,"TEST9 PASSED\n");
    }
   
}

void Test8(){
    int pid;
    pid = fork();
    if(pid == 0){
        char *stack = sbrk(PGSIZE);
        int n = clone(&test_exec,NULL,stack,NULL);
        int join_pid = thread_join();
        if(n == join_pid){
            exit();
        }
    }
    else
    {
        wait();
    }
}

int
main(int argc, char *argv[])
{
    int ppid = getpid();
    printf(1, "Parent PID : %d\n", ppid);
    //Test1
    int test1 = Test1();
    printf(1,"\n");
    int test2 = Test2();
    printf(1,"\n");
    int test3 = Test3();
    printf(1,"\n");
    int test4 = Test4();
    printf(1,"\n");
    int test5 = Test5();
    printf(1,"\n");
    int test6 = Test6();
    printf(1,"\n");
    Test7();
    printf(1,"\n");
    Test8();
    printf(1,"\n");
    Test9();
    if(test1 && test2 && test3 && test4 && test5 && test6){
        printf(1,"ALL TEST PASSED\n");
    }
    
    exit();
}

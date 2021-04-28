#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"
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

void Multiply(void* arg1, void* arg2) 
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
print_args(void *arg1, void *arg2){
    
    int tid = gettid();
    int pid = getpid();
    printf(1,"PID is %d and TID is %d\n",pid,tid);
    thread_kill(tid);
    printf(1,"----%d %d----\n", *(int*)arg1, *(int*)arg2);
    exit();
}

void
print_num(void *arg1, void *arg2){
    t_acquire(&lock);
    int tid = gettid();
    printf(1, "ppid: %d , Tid: %d\n", *(int*)arg1, tid);
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
Addition(void *arg1, void *arg2)
{   
    int tid = gettid();
    int pid = getpid();
    printf(1,"PID is %d and TID is %d\n",pid,tid);
    int result = *(int*)arg1 + *(int*)arg2;
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
test_sync(void *arg1, void *arg2)
{   
    t_acquire(&lock);
    global = global * 4;
    t_release(&lock);
    exit();  
}
void
test_sync2(void *arg1, void *arg2)
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
    int arg1 = 10;
    int arg2 = 20;
    printf(1, "Parent PID : %d\n", pid);
    //Test1
    int thread_tid1 = thread_create(Addition, &arg1, &arg2);
    int join_tid1 = thread_join();
    int thread_tid2 = thread_create(print_args, &arg1, &arg2);
    int join_tid2 = thread_join();
    if(thread_tid1 == join_tid1 && thread_tid2 == join_tid2){
        printf(1,"Test1 Passes\n\n");
    }
    // printf(1, "Created thread=> PID : %d\n", thread_tid1);
    // printf(1, "Created thread=> PID : %d\n", thread_tid2);
    // printf(1, "Joined1 : %d\n", join_tid1);
    // printf(1, "Joined2 : %d\n", join_tid2);
    
    //Test2
    lock_init(&lock);
    int a = 0;
    int count = 0;
    int tid;
    while (1)
    {
        tid = thread_create(print_num, &pid, &a);
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
    printf(1,"Test2 Passes\n\n");

    //Test3
    if (r2 != c1) { 
        printf(1,"Multicantion can not be performed\n"); 
        exit(); 
    }
    arg1 = 0;
    arg2 = 0;
     
    for (int i = 0; i < 3; i++) { 
        int thread_pid = thread_create(Multiply,&arg1,&arg2); 
        printf(1, "Created thread=> PID : %d\n", thread_pid);
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
    printf(1,"Test3 Passes\n\n");

    //Test4
    
    int t_tid1 = thread_create(test_sync, &arg1, &arg2);
    int t_tid2 = thread_create(test_sync2, &arg1, &arg2);
    int join_t_tid1 = thread_join();
    int join_t_tid2 = thread_join();
    if(t_tid1 == join_t_tid1 && t_tid2 == join_t_tid2){
        printf(1,"Global : %d\n", global);
        printf(1,"Test4 Passes\n\n");
    }
    printf(1,"ALL TEST PASSED\n");
    exit();
}

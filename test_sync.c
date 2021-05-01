#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"


t_lock lock;
volatile int total = 0;


void addition(void *a, void *b){
    
    int old = 0;
    int i = 0;
    t_acquire(&lock);
    printf(1,"%d-%d-%d\n", old, i, *(int*)b);
    while (i < *(int*)b)
    { 
        
         old = total;
         total = old + 1;
         i++;
      
    }
     t_release(&lock);
    //sleep(5555);
    *(int*)a = total;
    
    exit();
}





int main(int argc, char* argv[]){
    
    int a = 0;
    int c = 0;
    int b = 32;
    int d = 28;
    lock_init(&lock);
    thread_create(&addition, &a, &b);
    thread_create(&addition, &c, &d);
    thread_join();
    thread_join();
    printf(1,"%d\n", a);
    printf(1,"%d\n", c);
    printf(1,"%d\n", a+c);
    exit();
}
#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

void print_num(void *a, void *b){
    exit();
}

int main(int argc, char *argv[]){
    int pid = getpid();
    int a = 0;
    int tid;
    while (1)
    {
        tid = thread_create(&print_num, &pid, &a);
        if (tid == -1)
        {
            break;
        }
        
        a++;
        printf(1, "I am Thread: %d\n Count: %d\n", tid, a);
    }
    while(a > 0){
        thread_join();
        a--;
    }
    exit();

}
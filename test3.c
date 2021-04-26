#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"
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

int main() 
{ 

    if (r2 != c1) { 
        printf(1,"Multicantion can not be performed\n"); 
        exit(); 
    }
    int arg1 = 0;
    int arg2 = 0;
     
    for (int i = 0; i < 3; i++) { 
        int thread_pid = thread_create(&Multiply,&arg1,&arg2); 
        printf(1, "Created thread=> PID : %d\n", thread_pid);
    } 
  
    for (int i = 0; i < 3; i++){
            int join_pid = thread_join();
            printf(1, "Thread Joined : %d\n", join_pid);
    }     
  
    printf(1,"\n%d %d\n", r1, c2);
    for(int i = 0; i < r1; i++) { 
        for(int j = 0; j < c2; j++)  
            printf(1,"%d ",M3[i][j]);
        printf(1,"\n"); 
    } 
    exit(); 
} 
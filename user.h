
struct stat;
struct rtcdate;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int clone(void(*fcn)(void *), void *args, void *stack, int flag); //Prototype for clone sys call
int join(void **stack); //Prototype for join sys call
int gettid(void); //Prototype for getttid system call
int kill_thread(int); //Prototype for kill thread system call

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
void lock_init(t_lock *lock);
void t_acquire(t_lock *lock);
void t_release(t_lock *lock);


int thread_create(void (*func)(void *), void* args);
int thread_join();
int thread_kill(int tid);

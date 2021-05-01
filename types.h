typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;
#define CLONE_FS 1
#define CLONE_VM 2
#define CLONE_THREAD 4

typedef struct t_lock {
  uint is_locked;
} t_lock;


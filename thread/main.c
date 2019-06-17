#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

#define STACK_SIZE 1024*1024*8 //8M

void* thread(void* p)
{
    sleep(1);
    printf("pthread pid %d \n", (int)syscall(SYS_getpid));
    printf("pthread tid %d \n", (int)syscall(SYS_gettid));
}

int thread2(void* lparam)
{
    sleep(5);
    printf("clone pid %d \n", (int)syscall(SYS_getpid));
    printf("clone tid %d \n", (int)syscall(SYS_gettid));
}

int main(int argc,char **argv)
{
    // pthread
    pthread_t id;
    int i,ret;
    int pid;
    ret=pthread_create(&id,NULL,thread,NULL);
    if(ret!=0){
        printf("Create pthread error!\n");
        exit(1);
    }

    // mmap
    void *pstack = (void*)mmap(NULL,
                               STACK_SIZE,
                               PROT_READ|PROT_WRITE,
                               MAP_PRIVATE | MAP_ANONYMOUS,
                               -1,
                               0);
    if(MAP_FAILED==pstack)
    {
        printf("mmap failed %s \n", strerror(errno));
        exit(1);
    }

    /*clone
    CLONE_VM  (0x100) - tells the kernel to let the original process and the clone in the same memory space;
    CLONE_FS (0x200) - both get the same file system information;
    CLONE_FILES (0x400) - share file descriptors;
    CLONE_SIGHAND (0x800) - both processes share the same signal handlers;
    CLONE_THREAD (0x10000) - this tells the kernel, that both processes would belong to the same thread group (be threads within the same process);
    */
    pid = clone(thread2,
                (void*)((unsigned char*)pstack+STACK_SIZE),
                CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_THREAD|SIGCHLD,
                (void*)NULL);
    if(-1==pid)
    {
        printf("clone failed %s \n", strerror(errno));
    }

    printf("This is the main process.\n");
    printf("main pid %d \n", (int)syscall(SYS_getpid));
    printf("main tid %d \n", (int)syscall(SYS_gettid));
    pthread_join(id,NULL);
    //clone时的CLONE_THREAD flag会让新线程detached，这个时候就不能使用waitpid了。
    // if(-1 == waitpid(pid, NULL, 0)) 
    // {
    //     printf("waitpid failed %s \n", strerror(errno));
    //     exit(1);
    // }
    pause();
    return 0;
}
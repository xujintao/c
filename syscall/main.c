#include <sys/types.h> // pid_t
#include <sys/syscall.h> // SYS_gettid
#include <unistd.h>

// 1, ctrl + shift + B
// 2, F5

int main(){
    pid_t tid;
    tid = syscall(SYS_gettid);
    return 0;
}
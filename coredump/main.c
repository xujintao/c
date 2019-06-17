#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sighandle(int s) 
{
    
    switch(s)
    {
    case SIGINT:
    case SIGTERM:
        printf("%s\n", "program exit");
        exit(0);
        break;
    case SIGSEGV:
        signal(s, SIG_DFL); // 重新注册默认处理，下一次收到SIGSEGV信号会直接生成coredump文件并退出
        printf("%s\n", "received sigsegv");
        if (!fork()) { //child process
                  // Crash the app
            abort();
        }
        *((int*)NULL) = 42; // Crash for real now.
        return;
    }
}

int main()
{
    signal(SIGKILL, sighandle); // 其实无效, SIGKILL信号直接发给了init进程，由init进程来终止当前进程
    signal(SIGINT, sighandle);
    signal(SIGTERM, sighandle);
    signal(SIGSEGV, sighandle); // 自定义sigsegv信号handle

    *((int*)NULL) = 42; // Crash, and capture
    printf("%s\n", "program go on");
    pause(); // 等待信号
}

// gcc -g main.c
// gdb ./a.out ./core.a.out.xxx.xxx
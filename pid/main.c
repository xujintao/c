#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

pid_t pid;

int main()
{
    pid = getpid();
    printf("%d\n", pid);
}
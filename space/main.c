#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int bss_var;
int data_var0 = 1;
extern char _start;
int main()
{
    printf("_____________________________________\n");
    printf("stack section:\n");
    int stack_var = 3;
    printf("\t%p\n",&stack_var);
    printf("_____________________________________\n");

    printf("heap section:\n");
    char *p = (char*)malloc(10);
    printf("\t%p\n",p);
    printf("_____________________________________\n");

    printf(".bss section:\n");
    printf("\t%p\n",&bss_var);
    printf("_____________________________________\n");

    printf(".data section:\n");
    static int data_var1 = 4;
    printf("\t%p\n",&data_var1);
    printf("\t%p\n",&data_var0);
    printf("_____________________________________\n");

    printf(".text section(main):\n");
    printf("\t%p\n",main);
    printf("_____________________________________\n");

    printf(".text section(_start):\n");
    printf("\t%p\n",&_start);
    printf("_____________________________________\n");

    // pause();
    return 0;
}
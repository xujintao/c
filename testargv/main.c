#include <stdio.h>

int main(){
    // 方式一
    // char* p[] = {"ab", "cd"};
    // printf("%s\n", p[0]);

    // 方式二
    char* a[] = {"ab", "cd"};
    char** p = a;
    printf("%s\n", *(p+0));
    return 0;
}
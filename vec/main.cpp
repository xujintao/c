#include <stdio.h>
#include <vector>

void foo(std::vector<int> s) {
    s.push_back(10);
}

int main() {
    std::vector<int> s;
    s.push_back(7);
    s.push_back(8);
    s.push_back(9);
    foo(s);
    for (int v: s) {
        printf("%d", v);
    }
}
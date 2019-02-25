#include "testlib.h"
#include <bits/stdc++.h>

const int MIN = 1;
const int MAX = 10000000;

int main(int argc, char **argv){
    registerGen(argc, argv, 1);
    int test;
    sscanf(argv[1], "%d", &test);
    printf("%d\n", test);
    for (int i = 0; i < test; ++ i){
        printf("%d\n", rnd.next(MIN, MAX));
    }
    return 0;
}

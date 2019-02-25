#include "testlib.h"
#include <bits/stdc++.h>

const int MIN = 1;
const int MAX = 10000000;

int main(int argc, char **argv){
    registerGen(argc, argv, 1);
    int l, r;
    sscanf(argv[1], "%d", &l);
    sscanf(argv[2], "%d", &r);
    int test = r - l + 1;
    printf("%d\n", test);
    for (int i = l; i <= r; ++ i){
        printf("%d\n", i);
    }
    return 0;
}

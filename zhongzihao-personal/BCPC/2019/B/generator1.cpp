#include "testlib.h"
#include <bits/stdc++.h>

typedef long long ll;

int main(int argc, char **argv){
    registerGen(argc, argv, 1);
    int n, sigma;
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &sigma);
    printf("%d\n", (1 << n) - 1);
    std::vector <int> vec;
    for (int i = 0; i < n; ++ i){
        vec.push_back(rnd.next(1, sigma));
    }
    for (int i = 1; i < 1 << n; ++ i){
        printf("%d %d %d\n", n, sigma, i);
        for (int j = 0; j < n; ++ j){
            printf("%d%c", vec[j], " \n"[j == n - 1]);
        }
    }
    return 0;
}
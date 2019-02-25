#include "testlib.h"
#include <bits/stdc++.h>

typedef long long ll;
const int MAXSIGMA = 5000;

int main(int argc, char **argv){
    registerGen(argc, argv, 1);
    //------- part1 --------
    int test = 1000;
    printf("%d\n", test);
    int testcnt = 0;
    for (int i = 0; i < 500; ++ i){
        int n = rnd.next(1, 100);
        int type = rnd.next(1, 3);
        int sigma;
        switch (type) {
            case 1 :
                sigma = rnd.next(1, MAXSIGMA);
                break;
            case 2 :
                sigma = n;
                break;
            case 3 :
                sigma = rnd.next(1, (n + 9) / 10);
                break;
        }
        ll k = rnd.next(1ll, std::min(1'000'000'000'000'000'000, (1ll << std::min(60, n)) - 1));
        printf("%d %d %lld\n", n, sigma, k);
        ++ testcnt;
        for (int i = 0; i < n; ++ i){
            printf("%d%c", rnd.next(1, sigma), " \n"[i == n - 1]);
        }
    }

    //------- part2 -------
    for (int _ = 0; _ < 2; ++ _) {
        int n = 6, sigma = _ == 1 ? 5 : 4;
        std::vector<int> vec;
        for (int i = 0; i < n; ++i) {
            vec.push_back(rnd.next(1, sigma));
        }
        for (int i = 1; i < 1 << n; ++i) {
            printf("%d %d %d\n", n, sigma, i);
            ++ testcnt;
            for (int j = 0; j < n; ++j) {
                printf("%d%c", vec[j], " \n"[j == n - 1]);
            }
        }
    }

    //------- part3 -------
    for (int i = 0; i < 3; ++ i) {
        int n = 5000 - i, sigma = 5000 - i, k = 5000 - i;
        printf("%d %d %d\n", n, sigma, k);
        ++ testcnt;
        for (int j = 0; j < n; ++j) {
            printf("%d%c", j + 1, " \n"[j == n - 1]);
        }
    }
    for (int i = 0; i < 3; ++ i) {
        int n = 100, sigma = 5000;
        ll k = 1'000'000'000'000'000'000;
        printf("%d %d %lld\n", n, sigma, k);
        ++ testcnt;
        for (int j = 0; j < n; ++j) {
            printf("%d%c", rnd.next(1, sigma), " \n"[j == n - 1]);
        }
    }

    //------- part4 -------
    while (testcnt < 1000){
        int n = 100, sigma = rnd.next(4500, 5000), k = n;
        printf("%d %d %d\n", n, sigma, k);
        ++ testcnt;
        for (int j = 0; j < n; ++ j){
            printf("%d%c", sigma + j - (n - 1), " \n"[j == n - 1]);
        }
    }
    return 0;
}
#include <bits/stdc++.h>

#define MAXN (1000010)

char a[MAXN];

struct KMP{
    int m;
    char p[MAXN];
    int fail[MAXN];

    void makeFail(){
        scanf("%s", p);
        m = strlen(p);

        fail[0] = -1;
        for(int i = 1, j = -1; i <= m; ++ i){
            while(j >= 0 && p[j] != p[i - 1]) j = fail[j];
            fail[i] = ++ j;
        }
    }

    std::pair<int, int> searchForm(char *t){
        int n = strlen(t);
        std::pair<int, int> ret = {-1, -1};
        for(int i = 0, j = 0; i < n; ++ i){
            while(j >= 0 && p[j] != t[i]) j = fail[j];
            if(++ j == m){
                if (ret.first == -1) ret = {i - m + 1, i - m + 1};
                else {
                    ret.second = i - m + 1;
                }
                j = fail[j];
            }
        }
        return ret;
    }
}kmp1, kmp2;

int main() {
    int test;
    scanf("%d", &test);
    while (test --) {
        scanf("%s", a);
        kmp1.makeFail();
        kmp2.makeFail();
        auto u = kmp1.searchForm(a);
        auto v = kmp2.searchForm(a);
        if (u.first == -1 || v.first == -1) {
            puts("NO");
            continue;
        }
        if (u.first + kmp1.m <= v.second || v.first + kmp2.m <= u.second) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}

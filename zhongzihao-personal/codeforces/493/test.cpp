#include<bits/stdc++.h>

const int MAX = 100010;

std::bitset <MAX> set;
int a[MAX];

int main(){
    int n, K;
    scanf("%d%d", &n, &K);
    for (int i = 0; i < K; ++ i){
        scanf("%d", &a[i]);
    }
    set.reset();
    set[0] = 1;
    for (int i = 1; i <= n; ++ i){
        std::bitset <MAX> tmp;
        for (int j = 0; j < K; ++ j){
            tmp |= set << a[j];
        }
        set = tmp;
        printf("%d\n", (int) set.count());
    }
    return 0;
}

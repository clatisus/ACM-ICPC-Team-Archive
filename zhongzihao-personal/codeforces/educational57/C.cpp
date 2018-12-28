#include<bits/stdc++.h>

const int N = 200;

int ans[N];

void init(){
    memset(ans, -1, sizeof(ans));
    for (int i = 3; i < 2000; ++ i){
        for (int j = 1; j < i - 1; ++ j){
            int num = 360 * j, den = 2 * i;
            if (num % den == 0){
                int x = num / den;
                if (x < N && ans[x] == -1){
                    ans[x] = i;
                }
            }
        }
    }
}

int main(){
    init();
    int test;
    scanf("%d", &test);
    while (test --){
        int angle;
        scanf("%d", &angle);
        printf("%d\n", ans[angle]);
    }
    return 0;
}

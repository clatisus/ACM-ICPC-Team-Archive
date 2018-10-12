#include<bits/stdc++.h>

const int N = 110;

char s[N];

void solve(){
    scanf("%s", s);
    int n = strlen(s);
    int sum = 0;
    for (int i = 0; i < n; ++ i){
        sum += s[i] == 'H' ? 1 : s[i] == 'O' ? 16 : 12;
    }
    printf("%d\n", sum);
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}

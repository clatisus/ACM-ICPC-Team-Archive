#include<bits/stdc++.h>

const int N = 300010;

char s[N], t[N];
int pre[N];

int solve(){
    scanf("%s", s);
    int n = strlen(s);
    int cnta = 0, cntp = 0;
    for (int i = 0; i < n; ++ i){
        cnta += s[i] == 'a';
        cntp += s[i] == '+';
/**<  */    }
    if (cnta - 1 < cntp){
        for (int i = 0; i < cntp + 1 - cnta; ++ i){
            t[i] = 'a';
        }
        t[cntp + 1 - cnta] = 0;
    }
    else{
        t[0] = 0;
    }
    strcat(t, s);
    n = strlen(t);
    for (int i = 0; i < cnta - cntp - 1; ++ i){
        t[n ++] = '+';
    }
    int ans = std::abs(cnta - cntp - 1);
    int min = INT_MAX;
    for (int i = 0; i < n; ++ i){
        pre[i] = (i ? pre[i - 1] : 0) + (t[i] == 'a' ? 1 : -1);
        min = std::min(min, pre[i]);
    }
    if (min < -1){
        ans += (-1 - min) * 2;
        for (int i = 0; i < n; ++ i){
            pre[i] -= min + 1;
        }
    }
    int cnt0 = 0, cnt1 = 0;
    for (int i = 0; i < n; ++ i){
        cnt0 += !pre[i];
        cnt1 += pre[i] == -1;
    }
    int ans1 = (cnt1 ? std::min(4, cnt0 + cnt1) : std::min(2, cnt0)) + ans;

    min = INT_MAX;
    for (int i = 0; i < n; ++ i){
        min = std::min(min, pre[i]);
    }
    if (min < 0){
        ans += (0 - min) * 2;
        for (int i = 0; i < n; ++ i){
            pre[i] -= min;
        }
    }
    cnt0 = 0;
    for (int i = 0; i < n; ++ i){
        cnt0 += !pre[i];
    }
    int ans2 = std::min(2, cnt0) + ans;
    return std::min(ans1, ans2);
}

int main(){
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        printf("Case %d: %d\n", i, solve());
    }
    return 0;
}


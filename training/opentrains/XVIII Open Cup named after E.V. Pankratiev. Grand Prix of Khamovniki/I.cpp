#include<bits/stdc++.h>

const int N = 10010;

int n, k;
int sz[N], top[N];

int ask(int x){
    printf("%d\n", x);
    fflush(stdout);
    char s[6];
    scanf("%s", s);
    if (!strcmp(s, "End")){
        return 0;
    }
    if (!strcmp(s, "<=")) {
        for (int i = 0; i < n; ++i) {
            if (sz[i] && top[i] <= x) {
                -- sz[i];
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            if (sz[i] && top[i] >= x) {
                -- sz[i];
            }
        }
    }
    for (int i = 0; i < n; ++i) scanf("%d", top + i);
    return 1;
}

int getans() {
    std::vector<std::pair<int, int> > vec;
    long long tot = 0;
    for (int i = 0; i < n; ++i) {
     //   printf("sz[%d] = %d\n", i, sz[i]);
        if (!sz[i]) continue;
        vec.push_back({top[i], 1 << (sz[i] - 1)});
        tot += 1 << (sz[i] - 1);
    }
    std::sort(vec.begin(), vec.end());
    long long now = 0;
    for (auto p : vec) {
       // printf("tot = %lld, now = %lld, (%d, %d)\n", tot, now, p.first, p.second);
        now += p.second;
        if (now >= (tot >> 1)) {
            return p.first;
        }
    }
}

int main(){
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) sz[i] = k;
    for (int i = 0; i < n; ++i){
        scanf("%d", top + i);
    }
    while (true){
        int ret = ask(getans());
        if (!ret){
            return 0;
        }
    }
    return 0;
}

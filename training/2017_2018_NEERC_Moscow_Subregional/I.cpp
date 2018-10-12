#include<bits/stdc++.h>

#define MAXN (1510)

std::pair<std::bitset<MAXN>, int> a[MAXN];
int n, m;

void read(int &x){
    x = 0;
    char ch;
    while (!isdigit(ch = getchar()));
    x = ch - '0';
    while (isdigit(ch = getchar())){
        x = x * 10 + ch - '0';
    }
}

int main(){
    read(n); read(m);
    for (int i = 0; i < n; ++i) {
        a[i].second = 1;
        for (int j = 0; j < m; ++j) {
            int x;
            read(x);
            x &= 1;
            if (x) {
                a[i].first.set(j);
            }
        }
    }
    for (int i = 0, j; i < m; ++i) {
        for (int k = i; k < n; ++k) {
            if (a[k].first[i]) {
                j = k;
                break;
            }
        }
        std::swap(a[i], a[j]);
        for (int k = i + 1; k < n; ++k) {
            if (a[k].first[i]) {
                a[k].first ^= a[i].first;
                a[k].second ^= a[i].second;
            }
        }
    }
    for (int i = m; i < n; ++i) {
        if (a[i].second) {
            printf("No\n");
            return 0;
        }
    }
    printf("Yes\n");
    return 0;
}


//
// Created by zzh on 2019/4/27.
//

#include <bits/stdc++.h>

const int max_A = (int) 1e7 + 21;
const int max_N = (int) 1e6 + 21;

int n, min[max_A], tmp[max_A], a[max_N], L[max_N], R[max_N], LL[max_N];

int st[max_N], top, ch[2][max_N];

std::multiset<int> set;

std::vector<int> prime;

void init(int n) {
    for (int i = 2; i <= n; ++i){
        if (!min[i]) {
            min[i] = i;
            prime.push_back(i);
        }
        for (auto &p : prime) {
            long long j = p * i;
            if (j > n) break;
            min[j] = p;
            if (i % p == 0) break;
        }
    }
}

int p[max_N];

int main() {
    init(1e7);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        int x = a[i];
        int pre = 0;
        while (x > 1) {
            int y = min[x];
            pre = std::max(pre, tmp[y]);
            while (x % y == 0) {
                x /= y;
            }
            tmp[y] = i;
        }
        L[i] = pre + 1;
    }
    for (int i = 1; i <= 1e7; ++i) {
        tmp[i] = n + 1;
    }
    for (int i = n; i; --i) {
        int x = a[i];
        int nxt = n + 1;
        while (x > 1) {
            int y = min[x];
            nxt = std::min(nxt, tmp[y]);
            while (x % y == 0) {
                x /= y;
            }
            tmp[y] = i;
        }
        R[i] = nxt - 1;
    }
    for (int i = 1; i <= n; ++i) {
        LL[i] = i;
    }
    for (int i = 1; i <= n; ++i) {
        while (top && *set.begin() < R[i]) {
            if (L[i] <= LL[st[top]]) {
                int x = st[top--];
                set.erase(set.find(R[x]));
                LL[i] = std::min(L[i], LL[i]);
                ch[0][i] = x;
            } else break;
        }
        if (top) {
            if (*set.begin() >= i) {
                ch[1][st[top]] = i;
            } else {
                puts("impossible");
                return 0;
            }
        }
        st[++top] = i;
        set.insert(R[i]);
    }
    for (int i = 1; i <= n; ++i) {
        for (int d = 0; d < 2; ++d) {
            if (ch[d][i]) {
                p[ch[d][i]] = i;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d%c", p[i], " \n"[i == n]);
    }
}
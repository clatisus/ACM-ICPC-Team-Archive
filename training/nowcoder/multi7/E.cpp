#include <bits/stdc++.h>
 
inline int Cn4(int n) {
    return n * (n - 1) / 2 * (n - 2) / 3 * (n - 3) / 4;
}
 
inline int Cn3(int n) {
    return n * (n - 1) / 2 * (n - 2) / 3;
}
 
inline int Cn2(int n) {
    return n * (n - 1) / 2;
}
 
int calc(int k, int n1) {
    int sum = n1;
    k -= Cn4(n1);
    while (k) {
        int lo = 1, hi = n1 + 1;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (Cn3(mid) > k) hi = mid;
            else lo = mid + 1;
        }
        ++sum;
        k -= Cn3(lo - 1);
    }
    return sum;
}
 
int _calc(int k, int n1) {
    int sum = n1;
    k -= Cn4(n1);
    int flag = 0;
    while (k) {
        int lo = 1, hi = n1 + 1;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (Cn3(mid) > k) hi = mid;
            else lo = mid + 1;
        }
        ++sum;
        k -= Cn3(--lo);
        if (flag) {
            int sec = lo;
            if (Cn2(sec) <= k) {
                k -= Cn2(sec);
                flag = 0;
            }
        } else flag = 1;
    }
    return sum;
}
 
int n, m, k;
 
int n1, m1[233], tot;
 
int solve(int k) {
    int sum = 0x3f3f3f3f;
    int n1, lo = 1, hi = 75, res;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (Cn4(mid) > k) hi = mid;
        else lo = mid + 1;
    }
    n1 = --lo;
    if (k == Cn4(n1)) return n1;
    for (int n = 4; n <= n1; ++n) {
        int tmp = calc(k, n);
        if (sum > tmp) {
            sum = tmp;
            res = n;
        }
        tmp = _calc(k, n);
        if (sum > tmp) {
            sum = tmp;
            res = -n;
        }
    }
    return res;
}
 
void getAns() {
    m = n1 * (n1 - 1) / 2;
    k -= Cn4(n1);
    while (k) {
        int lo = 1, hi = n1 + 1;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (Cn3(mid) > k) hi = mid;
            else lo = mid + 1;
        }
        m1[++tot] = --lo;
        m += m1[tot];
        k -= Cn3(lo);
    }
    n = n1 + tot;
    assert(n <= 75);
    printf("%d %d\n", n, m);
    for (int i = 1; i <= n1; ++i)
        for (int j = i + 1; j <= n1; ++j) {
            printf("%d %d\n", i, j);
        }
    int id = n1;
    for (int i = 1; i <= tot; ++i) {
        ++id;
        for (int j = 1; j <= m1[i]; ++j) {
            printf("%d %d\n", j, id);
        }
    }
}
 
std::vector<std::pair<int, int>> vec;
 
void _getAns() {
    m = n1 * (n1 - 1) / 2;
    k -= Cn4(n1);
    int flag = 0;
    while (k) {
        int lo = 1, hi = n1 + 1;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (Cn3(mid) > k) hi = mid;
            else lo = mid + 1;
        }
        m1[++tot] = --lo;
        m += m1[tot];
        k -= Cn3(lo);
        if (flag) {
            int sec = lo;
            if (Cn2(sec) <= k) {
                k -= Cn2(sec);
                flag = 0;
                ++m;
                vec.push_back({n1 + tot - 1, n1 + tot});
            }
        } else flag = 1;
    }
    n = n1 + tot;
    assert(n <= 75);
    printf("%d %d\n", n, m);
    for (int i = 1; i <= n1; ++i)
        for (int j = i + 1; j <= n1; ++j) {
            printf("%d %d\n", i, j);
        }
    int id = n1;
    for (int i = 1; i <= tot; ++i) {
        ++id;
        for (int j = 1; j <= m1[i]; ++j) {
            printf("%d %d\n", j, id);
        }
    }
    for (auto e : vec) printf("%d %d\n", e.first, e.second);
}
 
int main() {
    scanf("%d", &k);
    n1 = solve(k);
    //k = 6, n1 = -4;
    if (n1 > 0) getAns();
    else n1 *= -1, _getAns();
    return 0;
}


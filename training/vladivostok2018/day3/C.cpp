#include <bits/stdc++.h>

#define MAXN (100010)
#define BLOCK_SIZE (333)

int n;
int a[MAXN], b[MAXN];
int l[MAXN], r[MAXN];

void update(std::priority_queue<int> &pq, int &cnt, int k, int ai) {
    if (cnt == k) {
        if (pq.top() > ai) {
            pq.pop();
            pq.push(ai);
        }
    } else {
        ++ cnt;
        pq.push(ai);
    }
}

void solve(int ql, int qr, int k) {
    int bl = ql / BLOCK_SIZE;
    int br = qr / BLOCK_SIZE;
    int cnt = 0;
    std::priority_queue<int> pq;
    if (bl == br) {
        for (int i = ql; i <= qr; ++ i) update(pq, cnt, k, a[i]);
    } else {
        if (ql != l[bl]) {
            for (int i = ql; i <= r[bl]; ++ i) update(pq, cnt, k, a[i]);
            ++ bl;
        }
        if (qr != r[br]) {
            for (int i = l[br]; i <= qr; ++ i) update(pq, cnt, k, a[i]);
            -- br;
        }
        for (int i = bl; i <= br; ++ i) {
            for (int j = l[i]; j <= l[i] + k - 1 && j <= r[i]; ++ j) {
                update(pq, cnt, k, b[j]);
            }
        }
    }
    std::vector<int> vec;
    while (!pq.empty()) vec.push_back(pq.top()), pq.pop();
    std::reverse(vec.begin(), vec.end());
    for (int i = 0, sz = (int)vec.size(); i < sz; ++ i) {
        printf("%d%c", vec[i], " \n"[i + 1 == sz]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
        b[i] = a[i];
    }
    int block_num = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;
    for (int i = 0; i < block_num; ++ i) {
        l[i] = i * BLOCK_SIZE;
        r[i] = (i + 1) * BLOCK_SIZE - 1;
        r[i] = std::min(r[i], n - 1);
        std::sort(b + l[i], 1 + b + r[i]);
    }
    int q;
    scanf("%d", &q);
    while (q --) {
        int ql, qr, k;
        scanf("%d%d%d", &ql, &qr, &k);
        -- ql; -- qr;
        solve(ql, qr, k);
    }
    return 0;
}
/*
7
6 1 5 2 4 3 1
4
1 7 7
2 4 2
3 5 1
5 7 2
*/

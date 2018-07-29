#include <bits/stdc++.h>

const int max_N = (int) 2e5 + 21;
const int mod = 998244353;

int n, q, lenS[max_N], lenP[max_N], len[max_N], tot;

char s[max_N << 1], p[max_N << 1];

char *S[max_N], *P[max_N];

int qx[max_N << 1], ans[max_N], Q[max_N << 1];

int hash[max_N], sumS[max_N], pw[max_N], _pw[max_N], inv2;

int hashP[max_N];

int getHash(int i, int l, int r) {
    int x = sumS[i - 1] + 1;
    int res = hash[x + r] ;
    if (l) res -= hash[x + l - 1];
    res = int(1ll * res * _pw[l] % mod);
    return res;
}

std::unordered_map<int, int> cnt;

void getString(int i, int len) {
    std::unordered_set<int> set;
    for (int st = 0; st + len <= lenS[i]; ++st) {
        int Hash = getHash(i, st, st + len - 1);
        if (set.count(Hash)) continue;
        //printf("getString(%d, %d) : ++cnt[%d]\n", i, len, Hash);
        ++cnt[Hash];
        set.insert(Hash);
    }
}

void solve(int len) {
    cnt.clear();
    int cur = 0;
    for (int i = 1; i <= q * 2; ++i) {
        int id = Q[i] <= q ? Q[i] : Q[i] - q, x = qx[Q[i]];
        if (lenP[id] != len) continue;
        while (cur < x) getString(++cur, len);
        int res = cnt[hashP[id]];
        if (Q[i] <= q) ans[id] += res;
        else ans[id] -= res;
    }
}

int main() {
    scanf("%d%d", &n, &q);
    S[1] = s;
    for (int i = 1; i <= n; ++i) {
        scanf("%s", S[i]);
        lenS[i] = strlen(S[i]);
        S[i + 1] = S[i] + lenS[i] + 1;
        sumS[i] = sumS[i - 1] + lenS[i];
    }

    inv2 = mod - mod / 2;
    assert(2 * inv2 % mod == 1);
    pw[0] = _pw[0] = 1;
    for (int i = 1; i <= sumS[n]; ++i) {
        pw[i] = (pw[i - 1] << 1) % mod;
        _pw[i] = int(1ll * _pw[i - 1] * inv2 % mod);
        //printf("pw %d : %d\n", i, pw[i]);
    }

    for (int i = 1; i <= n; ++i) {
        int x = sumS[i - 1] + 1;
        hash[x] = (S[i][0] - 'a');
        for (int j = 1; j < lenS[i]; ++j) {
            ++x;
            hash[x] = (hash[x - 1] + (S[i][j] - 'a') * pw[j]) % mod;
        }
    }

    //getHash(3, 0 ,0);
/*
    for (int i = 1; i <= sumS[n]; ++i) {
        printf("Hash %d : %d\n", i, hash[i]);
    }
*/
    P[1] = p;
    for (int i = 1; i <= q; ++i) {
        scanf("%d%d%s", qx + i + q, qx + i, P[i]);

        --qx[i + q];

        lenP[i] = strlen(P[i]);
        P[i + 1] = P[i] + lenP[i] + 1;

        Q[i] = i;
        Q[i + q] = i + q;

        len[++tot] = lenP[i];

        int Hash = P[i][0] - 'a';
        for (int j = 1; j < lenP[i]; ++j) {
            Hash = (Hash + (P[i][j] - 'a') * pw[j]) % mod;
        }
        hashP[i] = Hash;
        //printf("HashP %d : %d\n", i, hashP[i]);
    }

    std::sort(len + 1, len + 1 + tot);
    tot = std::unique(len + 1, len + 1 + tot) - (len + 1);

    std::sort(Q + 1, Q + 1 + 2 * q, [&](int x, int y) { return qx[x] < qx[y]; });

    for (int i = 1; i <= tot; ++i) solve(len[i]);

    for (int i = 1; i <= q; ++i) {
        printf("%d\n", ans[i]);
    }

    return 0;
}
/*
4 2
a
b
ab
bab
1 3 a
1 4 ab
*/


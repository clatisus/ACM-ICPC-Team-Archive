#include <bits/stdc++.h>
#define MAXN (100010)
#define ll long long
struct SAM {
    int tot, root, last;
    int go[MAXN << 1][26], par[MAXN << 1], maxlen[MAXN << 1];
    //optional
    int minlen[MAXN << 1];
    int first_endpos[MAXN << 1];
    bool accept[MAXN << 1];
    ll same[MAXN << 1];
    void init() {
        tot = 0;
        root = last = newnode(0);
    }
    int newnode(int ml) {
        maxlen[++tot] = ml;
        memset(go[tot], 0, sizeof go[tot]);
        par[tot] = 0;
        accept[tot] = false;//
        same[tot] = 1;//
        return tot;
    }
    void extend(int w, int pos) { //w = ch - 'a'
        int p = last, np = newnode(maxlen[p] + 1);
        first_endpos[np] = pos;//
        for (; p && !go[p][w]; p = par[p]) go[p][w] = np;
        if (!p) {
            par[np] = root;
            minlen[np] = 1;//
        } else {
            int q = go[p][w];
            if (maxlen[p] + 1 == maxlen[q]) {
                par[np] = q;
                minlen[np] = maxlen[q] + 1;//
            } else {
                int nq = newnode(maxlen[p] + 1);

                memcpy(go[nq], go[q], sizeof go[q]);
                same[nq] = 0;//
                first_endpos[nq] = first_endpos[q];//dfs parent-tree, sum of subtree is all endpos.(this may be not need).

                par[nq] = par[q];
                par[np] = par[q] = nq;
                minlen[nq] = maxlen[par[nq]] + 1;//
                minlen[np] = minlen[q] = maxlen[nq] + 1;//

                for (; p && go[p][w] == q; p = par[p]) go[p][w] = nq;
            }
        }
        last = np;
    }
    void get_accept() {
        for (int p = last; p; p = par[p]) {
            accept[p] = true;
        }
    }
    void build(char *s) {
        for (int i = 0; s[i]; ++i) {
            extend(s[i] - 'a', i + 1);
        }
        get_accept();//
    }
	int cnt[MAXN], ord[MAXN << 1];
	void sort() {
		int n = maxlen[last];
		for (int i = 0; i <= n; ++i) cnt[i] = 0;
		for (int i = 1; i <= tot; ++i) cnt[maxlen[i]]++;
		for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
		for (int i = tot; i; --i) ord[cnt[maxlen[i]]--] = i;
	}
} sam;
int n;
char str[MAXN];
int main() {
    sam.init();
    scanf("%d%s", &n, str);
    sam.build(str);
    return 0;
}

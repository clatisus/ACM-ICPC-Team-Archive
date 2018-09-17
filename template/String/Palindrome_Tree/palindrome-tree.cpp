const int max_N = (int) 1e5 + 21;
const int sigma = 26;

char a[max_N];

struct palindrome_tree {
    int tot, last;
    int ch[max_N][sigma];
    int len[max_N], cnt[max_N], p[max_N];

    inline int new_node(int l) {
        len[tot] = l;
        return tot++;
    }

    inline int get_node(int n, int x) {
        while (a[n - len[x] - 1] != a[n]) x = p[x];
        return x;
    }

    inline void Add(int n, int c) {
        int cur = get_node(n, last);
        if (!ch[cur][c]) {
            int now = new_node(len[cur] + 2);
            int tmp = get_node(n, p[cur]);
            p[now] = ch[tmp][c];
            ch[cur][c] = now;
        }
        ++cnt[last = ch[cur][c]];
    }

    inline void get_cnt() {
        for (int i = tot - 1; i >= 0; --i) cnt[p[i]] += cnt[i];
    }

    inline void build() {
        last = tot = 0;
        scanf("%s", a + 1);
        int n = strlen(a + 1);
        a[0] = '@';
        p[new_node(0)] = new_node(-1);
        for (int i = 1; i <= n; ++i) Add(i, a[i] - 'A');
        get_cnt();
    }
};
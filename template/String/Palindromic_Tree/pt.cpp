char a[max_N];

struct PalindromicTree {
    int tot, last;

    int ch[max_N][sigma], len[max_N], cnt[max_N], link[max_N];

    int diff[max_N], slink[max_N]; // palindrome series
    // Approval 1: path within serial links to the root contain only O(logn) vertices

    // Approval 2: link[v] != slink[v] ->
    // the previous occurrence of link[v] in the string was in position i - diff[v],
    // while in this position there is no suffix-palindrome with length len[v],
    // i.e. link[v] was the beginning of the series in that position

    inline int new_node(int l) {
        int x = tot++;
        len[x] = l;
        memset(ch[x], 0, sigma);
        cnt[x] = diff[x] = slink[x] = 0;
        return x;
    }

    inline int get_node(int n, int x) {
        while (a[n - len[x] - 1] != a[n]) x = link[x];
        return x;
    }

    // Ensure that s[0] is the unique character in str.
    inline void append(int n, int c) {
        int u = get_node(n, last);
        int v = ch[u][c];
        if (!v) {
            v = new_node(len[u] + 2);
            link[v] = ch[get_node(n, link[u])][c];
            ch[u][c] = v;

            diff[v] = len[v] - len[link[v]];
            if (diff[v] == diff[link[v]]) {
                slink[v] = slink[link[v]];
            } else {
                slink[v] = link[v];
            }
        }
        ++cnt[last = v];
    }

    inline void get_cnt() {
        for (int i = tot - 1; ~i; --i) cnt[link[i]] += cnt[i];
    }


    inline void init() {
        last = tot = 0;
        link[new_node(0)] = new_node(-1);
    }
};
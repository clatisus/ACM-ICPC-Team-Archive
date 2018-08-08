#include <bits/stdc++.h>

std::vector<std::pair<int, int>> vec0, vec1;

#define SZ(x) int((x).size())
#define lbt(x) ((x) & -(x))
#define MAXN (max_N - 1)

void init(){
	int nowodd = 1, noweven = 0;
	for (int i = 0; i < 1500; ++ i){
		if (i % 4 == 1 || i % 4 == 2){
			vec1.push_back({nowodd, i});
			nowodd = i * (i + 1) / 2 + 1;
		}
		else{
			vec0.push_back({noweven, i});
			noweven = i * (i + 1) / 2 + 1;
		}
	}
}

void read(int &x) {
    int f = 1, c;
    while (!isdigit(c = getchar())) if (c == '-') f = - 1;
    for (x = c - '0'; isdigit(c = getchar()); (x *= 10) += (c - '0'));
    x *= f;
}

void readc(char &c) {
    while (isspace(c = getchar()));
}

const int max_N = (int) 1e6 + 21;

int n, c, t, bit[2][max_N];

char opt;

void bit_add(int t, int x, int a) {
    for (; x <= MAXN; x += lbt(x)) bit[t][x] += a;
}

void bit_modify(int t, int l, int r, int a) {
    if (l <= r) bit_add(t, l, a), bit_add(t, r + 1, -a);
}

int bit_query(int t, int x) {
    int ret = 0;
    for (; x; x -= lbt(x)) ret += bit[t][x];
    return ret;
}

void update(std::vector<std::pair<int, int>> &vec, int x, int a, int t) {
    int i, sz, l, r;
    for (i = 0, sz = SZ(vec); i < sz; ++i) {
        int lo = vec[i].first;
        int hi = (i + 1 < sz) ? vec[i + 1].first - 1 : MAXN;

        l = x + lo, r = std::min(MAXN, x + hi);
        bit_modify(t, l, r, a * vec[i].second);

        l = std::max(1, x - hi), r = x - lo;
        if (!lo) --r;
        bit_modify(t, l, r, a * vec[i].second);
    }
}

void modify(int x, int a) {
    update(vec0, x, a, x & 1);
    update(vec1, x, a, ~x & 1);
}

int main() {
	init();
    read(n), read(t), ++t;
    for (int i = 1, x; i <= n; ++i) {
        read(x);
        modify(x + 1, 1);
    }
    read(c);
    for (int i = 1, x; i <= c; ++i) {
        readc(opt), read(x), ++x;
        if (opt == 't') t = x;
        else modify(x, opt == '+' ? 1 : -1);
        printf("%d\n", bit_query(t & 1, t));
    }
    return 0;
}


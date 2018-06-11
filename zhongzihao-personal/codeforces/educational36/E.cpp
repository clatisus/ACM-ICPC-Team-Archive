#include<bits/stdc++.h>

const int N = 600010;
const int MAX = 1 << 20;

int n, q;
int l[N], r[N], k[N], c[N];
int seg[MAX << 1], lazy[MAX << 1], sz[MAX << 1];

void pull(int sit){
	seg[sit] = seg[sit << 1] + seg[sit << 1 | 1];
}

void push(int sit){
	if (lazy[sit] < 2){
		seg[sit << 1] = lazy[sit] ? sz[sit << 1] : 0;
		seg[sit << 1 | 1] = lazy[sit] ? sz[sit << 1 | 1] : 0;
		lazy[sit << 1] = lazy[sit << 1 | 1] = lazy[sit];
		lazy[sit] = 2;
	}
}

void add(int sit, int l, int r, int ql, int qr, int value){
	if (l >= ql && r <= qr){
		seg[sit] = value ? sz[sit] : 0;
		lazy[sit] = value;
		return;
	}
	push(sit);
	int mid = l + r >> 1;
	if (ql <= mid){
		add(sit << 1, l, mid, ql, qr, value);
	}
	if (qr > mid){
		add(sit << 1 | 1, mid + 1, r, ql, qr, value);
	}
	pull(sit);
}

int query(int sit, int l, int r, int ql, int qr){
	if (l >= ql && r <= qr){
		return seg[sit];
	}
	push(sit);
	int mid = l + r >> 1;
	int ret = 0;
	if (ql <= mid){
		ret += query(sit << 1, l, mid, ql, qr);
	}
	if (qr > mid){
		ret += query(sit << 1 | 1, mid + 1, r, ql, qr);
	}
	return ret;
}

int main(){
	scanf("%d%d", &n, &q);
	int cnt = 0;
	for (int i = 0; i < q; ++ i){
		scanf("%d%d%d", &l[i], &r[i], &k[i]);
		++ r[i];
		c[cnt ++] = l[i];
		c[cnt ++] = r[i];
	}
	c[cnt ++] = 1;
	c[cnt ++] = n + 1;
	std::sort(c, c + cnt);
	cnt = std::unique(c, c + cnt) - c;
	for (int i = 0; i < cnt - 1; ++ i){
		sz[i + MAX] = c[i + 1] - c[i];
	}
	for (int i = MAX - 1; i; -- i){
		sz[i] = sz[i << 1] + sz[i << 1 | 1];
	}
	for (int i = 0; i < MAX << 1; ++ i){
		lazy[i] = 2;
	}
	add(1, 0, MAX - 1, 0, cnt - 1, 1);
	for (int i = 0; i < q; ++ i){
		int sit1 = std::lower_bound(c, c + cnt, l[i]) - c;
		int sit2 = std::lower_bound(c, c + cnt, r[i]) - c;
		add(1, 0, MAX - 1, sit1, sit2 - 1, k[i] - 1);
		printf("%d\n", query(1, 0, MAX - 1, 0, cnt - 1));
	}
	return 0;
}

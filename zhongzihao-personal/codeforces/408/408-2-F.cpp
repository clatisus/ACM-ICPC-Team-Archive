#include<bits/stdc++.h>

const int N = 300010;
const int MAX = 1 << 19;
const int INF = 1e9;

int seg[MAX << 1];
int n, m;
int min[N], t[N], l[N], r[N], x[N], a[N];

void build(){
	for (int i = 0; i < MAX << 1; ++ i){
		seg[i] = INF;
	}
}

void add(int left, int right, int value){
	for (int l = left + MAX, r = right + MAX + 1; l < r; l >>= 1, r >>= 1){
		if (l & 1){
			seg[l] = std::min(seg[l], value);
			++ l;
		}
		if (r & 1){
			-- r;
			seg[r] = std::min(seg[r], value);
		}
	}
}

int query(int sit){
	int ret = INF;
	sit += MAX;
	while (sit){
		ret = std::min(ret, seg[sit]);
		sit >>= 1;
	}
	return ret;
}

void build(int arg){
	memset(seg, -1, sizeof(seg));
	for (int i = 0; i < n; ++ i){
		seg[i + MAX] = a[i];
	}
	for (int i = MAX - 1; i; -- i){
		seg[i] = std::max(seg[i << 1], seg[(i << 1) + 1]);
	}
}

void add(int sit, int value){
	sit += MAX;
	seg[sit] = value;
	while (sit){
		value = std::max(value, seg[sit]);
		sit >>= 1;
	}
}

int query(int left, int right){
	int ret = 0;
	for (int l = left + MAX, r = right + MAX + 1; l < r; l >>= 1, r >>= 1){
		if (l & 1){
			ret = std::max(seg[l ++], ret);
		}
		if (r & 1){
			ret = std::max(seg[-- r], ret);
		}
	}
	return ret;
}

int main(){
	memset(min, -1, sizeof(min));
	build();
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++ i){
		scanf("%d", &t[i]);
		if (t[i] == 1){
			scanf("%d%d%d", &l[i], &r[i], &x[i]);
			-- l[i], -- r[i];
			add(l[i], r[i], x[i]);
		}
		else if (t[i] == 2){
			scanf("%d%d", &l[i], &r[i]);
			-- l[i];
			if (~min[l[i]]){
				continue;
			}
			min[l[i]] = query(l[i]);
		}
	}
	for (int i = 0; i < n; ++ i){
		if (!~min[i]){
			min[i] = query(i);
		}
	}
	memcpy(a, min, sizeof(min));
	build(1);
	for (int i = 0; i < m; ++ i){
		if (t[i] == 1){
			if (query(l[i], r[i]) != x[i]){
				return printf("NO\n"), 0;
			}
		}
		else{
			add(l[i], r[i]);
		}
	}
	printf("YES\n");
}

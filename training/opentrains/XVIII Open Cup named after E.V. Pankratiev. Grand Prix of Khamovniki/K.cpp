#include <bits/stdc++.h>

#define MAXN (500010)

int n;
int du[MAXN];
int can[MAXN];
int x[MAXN], y[MAXN];
int v[MAXN];
bool vis[MAXN], visodd[MAXN];

void print(int t = 0) {
    if (t == -1) printf("-1\n");
    else {
        printf("%d\n", n);
        for (int i = 1; i < n; ++i) {
            printf("%d %d\n", v[x[i]], v[y[i]]);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", can + i), v[i] = i;
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        x[i] = u; y[i] = v;
        ++ du[u];
        ++ du[v];
    }
    int ans = n;
    int cnt = 0;
    std::vector<int> vec;
    for (int i = 1; i <= n; ++ i) {
        if (du[i] & 1) {
            ans ^= i;
            if (can[i]) {
                ++ cnt;
                vec.push_back(i);
            }
            visodd[i] = true;
        } else {
            vis[i] = true;
        }
    }
    if (ans == 0) print();
    else if (cnt == 0) print(-1);
    else if (cnt == 1) {
        int tmp = ans ^ vec[0];
        if (!vis[tmp] && tmp != 0 && !visodd[tmp]) {
            v[vec[0]] = tmp;
            print();
        } else if (can[tmp] && (du[tmp] % 2 == 0)) {
            v[tmp] = 1 << 17;
            v[vec[0]] = tmp;
            print();
        } else {
            print(-1);
        }
    } else {
    	int tmp = ans ^ vec[1] ^ vec[0];
    	if (tmp == 0){
    		if (vec.size() == 2) print(-1);
    		else{
		        v[vec[0]] = 1 << 17;
		        v[vec[2]] = (ans ^ vec[2] ^ vec[0] ^ (1 << 17));
		        print();
			}
		}
		else{
	        v[vec[0]] = 1 << 17;
	        v[vec[1]] = (ans ^ vec[1] ^ vec[0] ^ (1 << 17));
	        print();
	    }
    }
    return 0;
}

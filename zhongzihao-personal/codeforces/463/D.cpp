#include<bits/stdc++.h>

const int N = 400010;
const int M = 20;
typedef long long ll;

int pre[N][M], pre1[N][M];
ll value[N][M], max[N][M];

int main(){
	int q;
	scanf("%d", &q);
	ll last = 0;
	int cnt = 2;
	while (q --){
		int type;
		ll p, q;
		scanf("%d%I64d%I64d", &type, &p, &q);
		p ^= last;
		q ^= last;
		if (type == 1){
			pre[cnt][0] = p;
			for (int j = 1; j < M; ++ j){
				pre[cnt][j] = pre[pre[cnt][j - 1]][j - 1];
			}
			max[cnt][0] = q;
			for (int j = 1; j < M; ++ j){
				max[cnt][j] = std::max(max[cnt][j - 1], max[pre[cnt][j - 1]][j - 1]);
			}
			int u = p;
			for (int j = M - 1; j >= 1; -- j){
				if (max[u][j - 1] < q){
					u = pre[u][j - 1];
				}
			}
			pre1[cnt][0] = u;
			for (int j = 1; j < M; ++ j){
				pre1[cnt][j] = pre1[pre1[cnt][j - 1]][j - 1];
			}
			value[cnt][0] = q;
			for (int j = 1; j < M; ++ j){
				value[cnt][j] = value[cnt][j - 1] + value[pre1[cnt][j - 1]][j - 1];
			}
			++ cnt;
		}
		else{
			int ans = 0;
			if (max[p][0] > q){
				ans = 0;
			}
			else{
				int u = p;
				ans = 1;
				q -= max[p][0];
				for (int j = M - 1; j >= 1; -- j){
					if (pre1[u][j - 1] && value[u][j - 1] <= q){
						q -= value[u][j - 1];
						ans += 1 << j - 1;
						u = pre1[u][j - 1];
					}
				}
			}
			printf("%d\n", ans);
			last = ans;
		}
	}
	return 0;
}

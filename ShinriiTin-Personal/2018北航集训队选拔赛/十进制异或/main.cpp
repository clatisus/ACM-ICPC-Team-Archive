#include <bits/stdc++.h>

using ll = long long;

ll cnt[30][3], pw[30];

int L[30], R[30], K[30], flag[30];

ll dfs(int bit, int sta, bool flag){
	if(sta==3 || bit==-1) return pw[bit+1];
	int lb = sta & 1, rb = sta >> 1;
	for(int a=0,b;a<10;++a){
		if((b = K[bit]-a) < 0) b += 10;
		if(!flag){
					
		}
		else{
			
		}
	}
}

void ll2Array(ll x, int* s){
	for(int i=0;i<20;++i) s[i] = x%10, x /= 10;
}

void testCase(){
	ll l, r, k;
	scanf("%lld%lld%lld", &l, &r, &k);
	ll2Array(l, L), ll2Array(r, R);
	for(int i=19;~i;--i) flag[i] = flag[i+1] | (L[i] < R[i]);
	ll2Array(k, K);
	memset(cnt, -1, sizeof(cnt));
	int pos = 19;
	for(;~pos;--pos){
		if(flag[pos]) break;
		if((L[pos]+R[pos])%10 != K[pos]){
			puts("0");
			return;
		}
	}
	printf("%lld\n", dfs(pos, 0, 0));
}

int main(){
	pw[0] = 1;
	for(int i=1;i<20;++i) pw[i] = pw[i-1]*10;
	int T; scanf("%d", &T); while(T --) testCase();
	return 0;
}

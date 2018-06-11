#include<bits/stdc++.h>

typedef long long ll;

int main(){
	int I, O, T, J, L, S, Z;
	scanf("%d%d%d%d%d%d%d", &I, &O, &T, &J, &L, &S, &Z);
	ll ans = O;
	if (!I || !J || !L){
		ans += I >> 1 << 1;
		ans += J >> 1 << 1;
		ans += L >> 1 << 1;
	}
	else{
		if (J % 2 != L % 2){
			ans += I;
			ans += J >> 1 << 1;
			ans += L >> 1 << 1;
		}
		else{
			if (J % 2 == 1){
				ans += I;
				ans += J;
				ans += L;
				if (I % 2 == 0) -- ans;
			}
			else{
				ans += I >> 1 << 1;
				ans += J;
				ans += L;
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}

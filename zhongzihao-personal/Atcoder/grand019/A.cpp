#include<bits/stdc++.h>

typedef long long ll;

int q, h, s, d, n;

int main(){
	scanf("%d%d%d%d%d", &q, &h, &s, &d, &n);
	h = std::min(h, q << 1);
	s = std::min(s, h << 1);
	d = std::min(d, s << 1);
	printf("%lld\n", 1ll * (n >> 1) * d + (n & 1) * s);
	return 0;
}

<TeX>special case for $t1 = 0, t2 = 1$</TeX>
int calc(int a, int b, int c, int n){ 
	ll m = (1ll * a * n + b) / c;
	if (!m) return 0;
	if (!a) return 1ll * (b / c) * (n + 1) % moder;
	if (a >= c || b >= c){
		int ret = (1ll * n * (n + 1) >> 1) % moder * (a / c) % moder;
		ret = (ret + 1ll * (n + 1) * (b / c)) % moder;
		ret += calc(a % c, b % c, c, n);
		ret -= ret >= moder ? moder : 0;
		return ret;
	}
	int ret = (1ll * n * m - calc(c, c - b - 1, a, m - 1)) % moder;
	ret += ret < 0 ? moder : 0;
	return ret;
}

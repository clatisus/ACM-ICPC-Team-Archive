int solve(int n){
	int c = random(n - 1) + 1, x = random(n), y = x, i = 0, k = 1;
	for ( ; ; ){
		++ i;
		x = (1ll * x * x + c) % n;
		int d = std::__gcd(std::abs(y - x), n);
		if (d != 1 && d != n) return d;
		if (x == y) return n;
		if (i == k){ y = x; k <<= 1; }
	}
}

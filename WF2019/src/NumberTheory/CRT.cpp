// 中国剩余定理模板
// 求方程组 x = first1(mod second1), x = first2(mod second2) 的解
// p.crt(q) 返回方程 p, q 的解 
// 如果没有 __int128 就只能这么写啦 
ll multmod(ll a, ll b, ll second){
	ll ret = a * b - (ll)((long double) a * b / second + 0.5) * second;
	return ret < 0 ? ret + second : ret;
}
pii crt(pii p1, pii p2){
	if (p1.second < p2.second) std::swap(p1, p2);
	int x, y;
	int gcd = ex_euc(p1.second, p2.second, x, y);
	if ((p2.first - p1.first) % gcd) return {0, 0};
	int lcm = p1.second / gcd * p2.second;
	int ans = (p2.first - p1.first) / gcd;
	ans = 1ll * ans * x % (p2.second / gcd) * p1.second;
	ans += p1.first;
	ans += ans < 0 ? lcm : ans >= lcm ? -lcm : 0;
	return {ans, lcm};
}

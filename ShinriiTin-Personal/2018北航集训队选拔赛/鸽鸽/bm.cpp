#include <stdio.h>
#include <assert.h>
#include <vector>

#define ll long long
#define SZ(x) ((int)(x).size())
#define rep(i, a, n) for(int i = (a); i < (n); ++ i)
#define mod (1000000007)

ll powmod(ll a, ll b){
    ll res = 1; a %= mod; assert(b >= 0);
    for(; b; b >>= 1){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

namespace linear_seq {
    const int N = 10010;
    ll res[N], base[N], _c[N], _md[N];
    
    std::vector<int> Md;
    
    void mul(ll *a, ll *b, int k){
        rep(i, 0, k + k) _c[i] = 0;
        rep(i, 0, k) if(a[i]) rep(j, 0, k) _c[i + j] = (_c[i + j] + a[i] * b[j]) % mod;
        for(int i = k + k - 1; i >= k; -- i) if(_c[i])
            rep(j, 0, SZ(Md)) _c[i - k + Md[j]] = (_c[i - k + Md[j]] - _c[i] * _md[Md[j]]) % mod;
        rep(i, 0, k) a[i] = _c[i];
    }
    
    int solve(ll n, std::vector<int> a, std::vector<int> b){
        ll ans = 0, pnt = 0;
        int k = SZ(a);
        assert(SZ(a) == SZ(b));
        rep(i, 0, k) _md[k - 1 - i] = - a[i]; 
		_md[k] = 1;
        Md.clear();
        rep(i, 0, k) if(_md[i]) Md.push_back(i);
        rep(i, 0, k) res[i] = base[i] = 0;
        res[0] = 1;
        while((1ll << pnt) <= n) ++ pnt;
        for(int p = pnt; p >= 0; -- p){
            mul(res, res, k);
            if((n >> p) & 1){
                for(int i = k - 1; i >= 0; -- i) res[i + 1] = res[i]; 
				res[0] = 0;
                rep(j, 0, SZ(Md)) res[Md[j]] = (res[Md[j]] - res[k] * _md[Md[j]]) % mod;
            }
        }
        rep(i, 0, k) ans = (ans + res[i] * b[i]) % mod;
        if(ans < 0) ans += mod;
        return ans;
    }
    
    std::vector<int> BM(std::vector<int> s){
        std::vector<int> C(1, 1), B(1, 1);
        int L = 0, m = 1, b = 1;
        rep(n, 0, SZ(s)){
            ll d = 0;
            rep(i, 0, L + 1) d = (d + 1ll * C[i] * s[n - i]) % mod;
            if(d == 0) ++ m;
            else if(2 * L <= n){
                std::vector<int> T = C;
                ll c = mod - d * powmod(b, mod - 2) % mod;
                while(SZ(C) < SZ(B) + m) C.push_back(0);
                rep(i, 0, SZ(B)) C[i + m] = (C[i + m] + c * B[i]) % mod;
                L = n + 1 - L; B = T; b = d; m = 1;
            }
            else{
                ll c = mod - d * powmod(b, mod - 2) % mod;
                while(SZ(C) < SZ(B) + m) C.push_back(0);
                rep(i, 0, SZ(B)) C[i + m] = (C[i + m] + c * B[i]) % mod;
                ++ m;
            }
        }
        return C;
    }
    
    int gao(std::vector<int> a, ll n){
        std::vector<int> c = BM(a);
        c.erase(c.begin());
        rep(i, 0, SZ(c)) c[i] = (mod - c[i]) % mod;
        return solve(n, c, std::vector<int>(a.begin(), a.begin() + SZ(c)));
    }
};

int main(){
	auto testCase = [](){
		static int Case = 0;
		static std::vector<int> a = {
			1,
			78,
			4056,
			175760,
			6854634,
			249508272,
			649601112,
			143055193,
			121875205,
			708114138,
			554596968,
			92516053,
			400069577,
			868180033,
			768616061,
			231503880,
			571279724,
			164892962,
			876461381,
			634036912,
			533872344,
			509136563,
			141524119,
			986103852,
			351598732,
			208771810,
			398547564,
			573244152,
			207690248,
			481007758,
			463627910,
			421925824,
			136475191,
			659084461,
			528185504,
			995109455,
			421064390,
			801126692,
			857333896,
			394298429,
			653792512,
			83648977,
			380024765,
			288617036,
			117989816,
			895928065,
			805990070,
			65605708,
			168178345,
			527932355,
			5393830,
			817474990,
			529874555,
			892695506,
			353626164,
			128584062,
			394300388,
			575550460,
			675518246,
			832909607,
			683757083,
			517510351,
			396204265,
			687492700,
			894944470,
			175949926,
			552139946,
			991270931,
			707081230,
			480806569,
			113372285,
			796616758,
			716078278,
			47424229,
			339421911,
			403790405,
			718234028,
			301176162,
			513664674,
			968585651,
			582692572,
			837545748,
			33417807,
			30973081,
			262385432,
			290968649,
			761089733,
			531916607,
			71668740,
			608093489,
			837622549,
			176393648,
			312742663,
			652037513,
			304368324,
			855577022,
			447497538,
			318874002,
			679044037,
			637132805,
		};
		int n; scanf("%d", &n);
		printf("Case #%d: ", ++ Case);
		if(n<8) puts("0");
		else printf("%d\n", linear_seq::gao(a, n-8));
	};
	
	int T; scanf("%d", &T); while(T --) testCase();
	return 0;
} 

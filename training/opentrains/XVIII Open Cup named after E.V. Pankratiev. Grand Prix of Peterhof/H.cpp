#include<bits/stdc++.h>

typedef long long ll;
const int MAX = 20;
const int moder = 998244353;
const int root = 3;
const int invroot = (moder + 1) / root;
const int N = 1000010;

int invn[N];

int w[2][1 << MAX];

int powermod(int a, int exp){
	int ret = 1;
	for ( ; exp > 0; exp >>= 1){
		if (exp & 1){
			ret = 1ll * a * ret % moder;
		}
		a = 1ll * a * a % moder;
	}
	return ret;
}

void init(){
    w[0][0] = w[1][0] = 1;
    w[0][1] = powermod(root, (moder - 1) >> MAX);
    for (int i = 2; i < (1 << MAX); ++i){
        w[0][i] = 1ll * w[0][i - 1] * w[0][1] % moder;
    }
    for (int i = 1; i < (1 << MAX); ++i){
        w[1][(1 << MAX) - i] = w[0][i];
    }
    invn[0] = 0, invn[1] = 1;
    for (int i = 2; i < N; ++i) {
        invn[i] = (moder - 1ll * (moder / i) * invn[moder % i] % moder) % moder;
    }
}

void NTT(std::vector <int> &a, int len, int type){
    for(int i = 1, j = 0; i < len - 1; ++i){
		for(int s = len; j ^= (s >>= 1), ~j & s; )
			;
		if(i < j){
			std::swap(a[i], a[j]);
		}
	}
	for (int i = 2, d = 1; i <= len; i <<= 1, ++d){
		for (int j = 0; j < len; j += i){
            auto u = a.begin() + j;
			for (int k = 0; k < i / 2; ++k){
				int t = 1ll * w[type][k << (MAX - d)] * u[k + i / 2] % moder;
			    u[k + i / 2] = u[k] - t + (u[k] - t < 0 ? moder : 0);
                u[k] += t; u[k] -= u[k] >= moder ? moder : 0;
			}
		}
	}
	if (type == 0) return;
	int inv = powermod(len, moder - 2);
	for (int i = 0; i < len; ++i){
		a[i] = 1ll * a[i] * inv % moder;
	}
}

class poly{
private:
    std::vector<int> a;
    int len;
    
public:
    poly() : len(-1) {}
    poly(int len) : len(len) { a.resize(len + 1); }
    poly(const poly &p, int len) : len(len) { 
        a.resize(len + 1); 
        for (int i = 0; i <= len; ++i) {
            a[i] = i > p.len ? 0 : p.a[i];
        }
    }
    
    int &operator [] (int n) { return a[n]; }
    int getlen() { return len; }
    
    void setlen(int len) {
        a.resize(len + 1);
        this->len = len;
    }
    
    poly operator + (const poly &p) const {
        poly ret(*this, std::max(len, p.len));
        for (int i = 0; i <= p.len; ++i) {
            ret.a[i] += p.a[i];
            ret.a[i] -= ret.a[i] >= moder ? moder : 0;
        }
        for ( ; ~ret.len && !ret.a[ret.len]; --ret.len)
            ;
        return ret;
    }
    
    poly operator - (const poly &p) const {
        poly ret(*this, std::max(len, p.len));
        for (int i = 0; i <= p.len; ++i) {
            ret.a[i] -= p.a[i];
            ret.a[i] += ret.a[i] < 0 ? moder : 0;
        }
        for ( ; ~ret.len && !ret.a[ret.len]; --ret.len)
            ;
        return ret;
    }
    
    poly operator * (const poly &p) const {
        if (!~len || !~p.len) return poly(-1);
        int n = len + p.len;
        int lenret = 1;
        for ( ; lenret <= n; lenret <<= 1)
            ;
        poly ret(*this, lenret);
        std::vector<int> aux(lenret);
        std::copy(p.a.begin(), p.a.begin() + p.len + 1, aux.begin());
        NTT(ret.a, lenret, 0);
        NTT(aux, lenret, 0);
        for (int i = 0; i < lenret; ++i) {
            ret.a[i] = 1ll * ret.a[i] * aux[i] % moder;
        }
        NTT(ret.a, lenret, 1);
        ret.len = n;
        return ret;
    }
    
    friend poly operator * (const int &q, const poly &p) { return p * q; }
    poly &operator += (const poly &p) { return *this = *this + p; }
    poly &operator -= (const poly &p) { return *this = *this - p; }
    poly &operator *= (const poly &p) { return *this = *this * p; }
    poly &operator *= (const int &p) { return *this = *this * p; }
    
    //表示求最高次为n的inv，log和exp同理
    poly inv(int n) const {
        assert(~len && a[0]);
        poly ret(1);
        ret.a[0] = powermod(a[0], moder - 2);
        for (int nowprecision = 0; nowprecision < n; ) {
            nowprecision = nowprecision << 1 | 1;
            poly aux(*this, nowprecision), aux1 = ret;
            ret *= ret;
            ret.setlen(nowprecision);
            aux *= ret, aux.setlen(nowprecision);
            ret = aux1 + aux1 - aux;
        }
        ret.setlen(n);
        return ret;
    }
    
    poly der() const {
        if (!~len) return poly(-1);
        poly ret(len - 1);
        for (int i = 0; i < len; ++i){
            ret.a[i] = 1ll * a[i + 1] * (i + 1) % moder;
        }
        return ret;
    }

    poly integral() const {
        poly ret(len + 1);
        for (int i = len + 1; i; --i){
            ret.a[i] = 1ll * a[i - 1] * invn[i] % moder;
        }
        return ret;
    }

    poly log(int n) const {
        assert(~len && a[0] == 1);
        poly aux(*this, n);
        poly ret = aux.der() * aux.inv(n - 1);
        ret.setlen(n - 1);
        return ret.integral();
    }

    poly exp(int n) const {
        assert(!~len || !a[0]);
        poly ret(0);
        ret.a[0] = 1;
        poly unit = ret;
        for (int nowprecision = 0; nowprecision < n; ){
            nowprecision = nowprecision << 1 | 1;
            poly aux(*this, nowprecision);
            ret *= unit - ret.log(nowprecision) + aux;
            ret.setlen(nowprecision);
        }
        ret.setlen(n);
        return ret;
    }
};

int main(){
    init();
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    poly p1(n), p2(m);
    for (int i = 0; i <= n; ++ i){
        scanf("%d", &p1[i]);
    }
    for (int i = 0; i <= m; ++ i){
        scanf("%d", &p2[i]);
    }
    p1 = p1.log(k - 1);
    p2 = p2.log(k - 1);
    for (int i = 1; i < k; ++ i){
        p1[i] = (i & 1 ? 1ll : -1ll) * p1[i] * p2[i] % moder * i % moder;
        p1[i] += p1[i] < 0 ? moder : 0;
    }
    p1 = p1.exp(k - 1);
    for (int i = 0; i < k; ++ i){
        printf("%d%c", p1[i], " \n"[i == k - 1]);
    }
    return 0;
}

#include<bits/stdc++.h>
#define ll long long

int power_mod(int a, int exp, int moder){
	int ret = 1;
	for ( ; exp; exp >>= 1){
		if (exp & 1){
			ret = 1ll * ret * a % moder;
		}
		a = 1ll * a * a % moder;
	}
	return ret;
}

struct BigInteger{
	// 除法和开根需要四倍空间 
	const static int MAX = 19;
	const static int moder = (479 << 21) + 1;
	static int aux[1 << MAX], aux1[1 << MAX], aux2[1 << MAX];
	
	int a[1 << MAX];
	int length, sig;
	
	BigInteger(ll n){
		memset(a, 0, sizeof(a));
		if (n == 0){
			sig = length = 0;
			return;
		}
		if (n < 0){
			sig = -1;
			n = - n;
		}
		else{
			sig = 1;
		}
		length = 0;
		for ( ; n; n /= 10){
			a[length ++] = n % 10;
		}
	}
	
	BigInteger(){
		memset(a, 0, sizeof(a));
		length = sig = 0;
	}
	
	void read(){
		length = 0;
		memset(a, 0, sizeof(a));
		char ch = getchar();
		for ( ; (ch < '0' || ch > '9') && ch != '-'; ch = getchar())
			;
		if (ch == '-'){
			sig = -1;
			ch = getchar();
		}
		else{
			sig = 1;
		}
		for ( ; ch >= '0' && ch <= '9'; ch = getchar()){
			a[length ++] = ch - '0';
		}
		for (int i = 0; i < length >> 1; ++ i){
			std::swap(a[i], a[length - i - 1]);
		}
		for ( ; length && !a[length - 1]; -- length)
			;
		if (!length){
			sig = 0;
		}
	}
	
	void write(){
		if (!sig){
			printf("0");
			return;
		}
		if (sig < 0){
			putchar('-');
		}
		for (int i = length - 1; i >= 0; i--){
			putchar(a[i] + '0');
		}
	}
	
	bool equal(const BigInteger &p) const &{
		if (sig != p.sig || p.length != length){
			return false;
		}
		for (int i = 0; i < length; ++ i){
			if (a[i] != p.a[i]){
				return false;
			}
		}
		return true;
	}
	
	bool greater(const BigInteger &p) const &{
		if (sig != p.sig){
			return sig > p.sig;
		}
		if (length != p.length){
			return length > p.length ^ sig == -1;
		}
		for (int i = length - 1; i >= 0; -- i){
			if (a[i] > p.a[i]){
				return sig > 0;
			}
			else if (a[i] < p.a[i]){
				return sig < 0;
			}
		}
		return false;
	}
};

int BigInteger::aux[1 << BigInteger::MAX] = {};
int BigInteger::aux1[1 << BigInteger::MAX] = {};
int BigInteger::aux2[1 << BigInteger::MAX] = {};

bool absgreaterequal(int *a, int *b, int lengtha, int lengthb){
	if (lengtha != lengthb){
		return lengtha > lengthb;
	}
	for (int i = lengtha - 1; i >= 0; -- i){
		if (a[i] > b[i]){
			return true;
		}
		else if (a[i] < b[i]){
			return false;
		}
	}
	return true;
}

void abs(BigInteger &ret){
	ret.sig = ret.sig ? 1 : 0;
}

void neg(BigInteger &ret){
	ret.sig = -ret.sig;
}

void add(int *a, int *b, int &lengtha, int &lengthb){
	int length = std::max(lengtha, lengthb);
	for (int i = 0; i < length; ++ i){
		a[i] += b[i];
		if (a[i] >= 10){
			a[i] -= 10;
			++ a[i + 1];
		}
	}
	lengtha = a[length] ? length + 1 : length;
}

bool minus(int *a, int *b, int &lengtha, int &lengthb){
	bool flag = true;
	if (lengtha != lengthb){
		flag = lengtha > lengthb;
	}
	else{
		for (int i = lengtha - 1; ~i; -- i){
			if (a[i] > b[i]){
				flag = true;
				break;
			}
			else if (a[i] < b[i]){
				flag = false;
				break;
			}
		}
	}
	if (!flag){
		std::swap(a, b);
		std::swap(lengtha, lengthb);
	}
	memset(BigInteger::aux, 0, sizeof(BigInteger::aux));
	for (int i = 0; i < lengtha; ++ i){
		BigInteger::aux[i] += a[i] - b[i];
		if (BigInteger::aux[i] < 0){
			BigInteger::aux[i] += 10;
			-- BigInteger::aux[i + 1];
		}
	}
	int lengthaux = lengtha;
	for ( ; lengthaux && !BigInteger::aux[lengthaux - 1]; -- lengthaux);
	if (!flag){
		std::swap(a, b);
		std::swap(lengtha, lengthb);
	}
	memset(a, 0, sizeof(int) * lengtha);
	lengtha = lengthaux;
	memcpy(a, BigInteger::aux, sizeof(int) * lengtha);
	return flag;
}

void posminus(int *a, int *b, int &lengtha){
	for (int i = 0; i < lengtha; ++ i){
		a[i] -= b[i];
		if (a[i] < 0){
			a[i] += 10;
			-- a[i + 1];
		}
	}
	for ( ; lengtha && !a[lengtha - 1]; -- lengtha);
}

void add(BigInteger &p, BigInteger &q){
	if (!q.sig){
		return;
	}
	if (!p.sig){
		p = q;
		return;
	}
	if (p.sig == q.sig){
		add(p.a, q.a, p.length, q.length);
		return;
	}
	bool flag = minus(p.a, q.a, p.length, q.length);
	if (!p.length){
		p.sig = 0;
		return;
	}
	if (!flag){
		p.sig = -p.sig;
	}
}

void minus(BigInteger &p, BigInteger &q){
	if (!q.sig){
		return;
	}
	if (!p.sig){
		p = q;
		p.sig = -p.sig;
		return;
	}
	if (p.sig != q.sig){
		add(p.a, q.a, p.length, q.length);
		return;
	}
	bool flag = minus(p.a, q.a, p.length, q.length);
	if (!p.length){
		p.sig = 0;
		return;
	}
	if (!flag){
		p.sig = -p.sig;
	}
}

void NTT(int *a, int length, int type){
	int len = -1, moder = BigInteger::moder;
	for (int x = length; x; ++ len, x >>= 1);
	for(int i = 1, j = 0; i < length - 1; ++ i){
		for(int s = length; j ^= s >>= 1, ~j & s; );
		if(i < j){
			std::swap(a[i], a[j]);
		}
	}
	for (int i = 1; i <= len; ++ i){
		int unit = power_mod(3, moder - 1 >> i, moder);
		if (type == -1)
			unit = power_mod(unit, moder - 2, moder);
		for (int j = 0; j < length; j += 1 << i){
			int w = 1;
			for (int k = j, szk = 1 << i - 1; k < j + szk; ++ k){
				int s = a[k], t = 1ll * w * a[k + szk] % moder;
				a[k] = (s + t) % moder;
				a[k + szk] = (s - t + moder) % moder;
				w = 1ll * w * unit % moder;
			}
		}
	}
	if (type == 1){
		return;
	}
	int inv = power_mod(length, moder - 2, moder);
	for (int i = 0; i < length; ++ i){
		a[i] = 1ll * a[i] * inv % moder;
	}
}

void mult(int *a, int *b, int &lengtha, int &lengthb){
	int n = lengtha + lengthb;
	int length = 1;
	for ( ; length < n; length <<= 1);
	NTT(a, length, 1);
	NTT(b, length, 1);
	for (int i = 0; i < length; i++){
		a[i] = 1ll * a[i] * b[i] % BigInteger::moder;
	}
	NTT(a, length, -1);
	NTT(b, length, -1);
	for (int i = 0; i < length - 1; i++){
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
	}
	lengtha = length;
	for ( ; lengtha && !a[lengtha - 1]; -- lengtha);
}

void mult(BigInteger &p, BigInteger &q){
	if (!q.sig){
		p = q;
		return;
	}
	if (!p.sig){
		return;
	}
	mult(p.a, q.a, p.length, q.length);
	p.sig = p.sig == q.sig ? 1 : -1;
}

void mult(int *a, int &lengtha, ll b){
	ll remain = 0;
	for (int i = 0; i < lengtha; ++ i){
		remain += a[i] * b;
		a[i] = remain % 10;
		remain /= 10;
	}
	a[lengtha] = remain;
	for ( ; a[lengtha]; ++ lengtha){
		a[lengtha + 1] = a[lengtha] / 10;
		a[lengtha] %= 10;
	}
	for ( ; lengtha && !a[lengtha - 1]; -- lengtha);
}

void mult(BigInteger &p, int q){
	if (!q){
		p.sig = p.length = 0;
		memset(p.a, 0, sizeof(p.a));
		return;
	}
	if (!p.sig){
		return;
	}
	mult(p.a, p.length, std::abs(q));
	if (q < 0){
		p.sig = -p.sig;
	}
}

void power(int *a, int &lengtha, int exp){
	memset(BigInteger::aux1, 0, sizeof(BigInteger::aux1));
	BigInteger::aux1[0] = 1;
	int lengthaux = 1;
	for ( ; exp; exp >>= 1){
		if (exp & 1){
			mult(BigInteger::aux1, a, lengthaux, lengtha);
		}
		int n = lengtha << 1;
		int length = 1;
		for ( ; length < n; length <<= 1);
		NTT(a, length, 1);
		for (int i = 0; i < length; i++){
			a[i] = 1ll * a[i] * a[i] % BigInteger::moder;
		}
		NTT(a, length, -1);
		for (int i = 0; i < length - 1; i++){
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
		}
		lengtha = length;
		for ( ; lengtha && !a[lengtha - 1]; -- lengtha);
	}
	memset(a, 0, sizeof(int) * lengtha);
	memcpy(a, BigInteger::aux1, sizeof(int) * lengthaux);
	lengtha = lengthaux;
}

void power(BigInteger &a, int exp){
	power(a.a, a.length, exp);
}

void leftshift(int *a, int &lengtha, int dis){
	for (int i = lengtha + dis - 1; i >= dis; -- i){
		a[i] = a[i - dis];
	}
	for (int i = dis - 1; i >= 0; -- i){
		a[i] = 0;
	}
	lengtha += dis;
}

void rightshift(int *a, int &lengtha, int dis){
	for (int i = 0; i < lengtha - dis; ++ i){
		a[i] = a[i + dis];
	}
	for (int i = lengtha - dis; i < lengtha; ++ i){
		if (i >= 0){
			a[i] = 0;
		}
	}
	lengtha -= dis;
	if (lengtha < 0){
		lengtha = 0;
	}
}

void divide(BigInteger &p, BigInteger &q){
	if (!q.sig || !p.sig){
		return;
	}
	if (p.length < q.length){
		p.sig = p.length = 0;
		memset(p.a, 0, sizeof(p.a));
		return;
	}
	int num = 0;
	for (int i = q.length - 1; i >= q.length - 3; -- i){
		num *= 10;
		if (i >= 0){
			num += q.a[i];
		}
	}
	num = 100000 / num;
	memset(BigInteger::aux, 0, sizeof(BigInteger::aux));
	int nowprecision = 1, lengthaux = 0;
	while (num){
		BigInteger::aux[lengthaux ++] = num % 10;
		num /= 10;
	}
	for (; nowprecision <= p.length - q.length; nowprecision <<= 1){
		memset(BigInteger::aux2, 0, sizeof(BigInteger::aux2));
		memcpy(BigInteger::aux2, BigInteger::aux, sizeof(int) * lengthaux);
		int lengthaux1 = 2 * nowprecision + 3, lengthaux2 = lengthaux;
		power(BigInteger::aux2, lengthaux2, 2);
		memset(BigInteger::aux1, 0, sizeof(BigInteger::aux1));
		for (int i = q.length - lengthaux1; i < q.length; ++ i){
			BigInteger::aux1[i - q.length + lengthaux1] = i >= 0 ? q.a[i] : 0;
		}
		mult(BigInteger::aux1, BigInteger::aux2, lengthaux1, lengthaux2);
		rightshift(BigInteger::aux1, lengthaux1, nowprecision * 2 + 4);
		mult(BigInteger::aux, lengthaux, 2);
		leftshift(BigInteger::aux, lengthaux, nowprecision);
		posminus(BigInteger::aux, BigInteger::aux1, lengthaux);
	}
	mult(BigInteger::aux, p.a, lengthaux, p.length);
	rightshift(BigInteger::aux, lengthaux, q.length + nowprecision + 1);
	memset(BigInteger::aux1, 0, sizeof(BigInteger::aux1));
	memcpy(BigInteger::aux1, q.a, sizeof(int) * q.length);
	int lengthaux1 = q.length;
	mult(BigInteger::aux1, BigInteger::aux, lengthaux1, lengthaux);
	int flag = 0;
	if (!absgreaterequal(p.a, BigInteger::aux1, p.length, lengthaux1)){
		flag = -1;
	}
	else{
		posminus(p.a, BigInteger::aux1, p.length);
		if (absgreaterequal(p.a, q.a, p.length, q.length)){
			flag = 1;
		}
	}
	memset(p.a, 0, sizeof(int) * p.length);
	p.length = 0;
	if (flag == -1){
		p.a[0] = 1;
		p.length = 1;
		posminus(BigInteger::aux, p.a, lengthaux);
		memcpy(p.a, BigInteger::aux, sizeof(int) * lengthaux);
		p.length = lengthaux;
	}
	else{
		if (flag){
			p.a[0] = 1;
			p.length = 1;
		}
		add(p.a, BigInteger::aux, p.length, lengthaux);
	}
	if (!p.length){
		p.sig = 0;
	}
	p.sig *= q.sig;
}

void divide(int *a, int &lengtha, ll b){
	ll remain = 0;
	for (int i = lengtha - 1; i >= 0; -- i){
		remain = remain * 10 + a[i];
		a[i] = remain / b;
		remain %= b;
	}
	for ( ; lengtha && !a[lengtha - 1]; -- lengtha);
}

void divide(BigInteger &p, int q){
	if (!q || !p.sig){
		return;
	}
	divide(p.a, p.length, std::abs(q));
	if (!p.length){
		p.sig = 0;
		return;
	}
	if (q < 0){
		p.sig = -p.sig;
	}
}

int sqrt(int n){
	int ret = (int) sqrt(1.0 * n) + 1;
	while (ret * ret > n){
		-- ret;
	}
	return ret;
}

void sqrt(BigInteger &p){
	if (p.sig <= 0){
		return;
	}
	int num = 0;
	for (int i = p.length - 1; i >= p.length - 8; -- i){
		num *= 10;
		if (i >= 0){
			num += p.a[i];
		}
	}
	ll x = 1;
	for (int i = 0; i < 14; ++ i){
		x *= 10;
	}
	if (p.length & 1){
		x /= 10;
	}
	num = sqrt((int) (x / num));
	memset(BigInteger::aux, 0, sizeof(BigInteger::aux));
	int nowprecision = 2, lengthaux = 0;
	while (num){
		BigInteger::aux[lengthaux ++] = num % 10;
		num /= 10;
	}
	for (; nowprecision <= p.length / 2 + 1; nowprecision = 2 * nowprecision - 1){
		memset(BigInteger::aux2, 0, sizeof(BigInteger::aux2));
		memcpy(BigInteger::aux2, BigInteger::aux, sizeof(int) * lengthaux);
		int lengthaux1 = 2 * nowprecision + 1 + (p.length & 1), lengthaux2 = lengthaux;
		power(BigInteger::aux2, lengthaux2, 2);
		memset(BigInteger::aux1, 0, sizeof(BigInteger::aux1));
		for (int i = p.length - lengthaux1; i < p.length; ++ i){
			BigInteger::aux1[i - p.length + lengthaux1] = i >= 0 ? p.a[i] : 0;
		}
		mult(BigInteger::aux2, BigInteger::aux1, lengthaux2, lengthaux1);
		rightshift(BigInteger::aux2, lengthaux2, nowprecision * 2 + 2);
		divide(BigInteger::aux2, lengthaux2, 2);
		memset(BigInteger::aux1, 0, sizeof(int) * lengthaux1);
		BigInteger::aux1[nowprecision * 2] = 5;
		BigInteger::aux1[nowprecision * 2 + 1] = 1;
		lengthaux1 = nowprecision * 2 + 2;
		posminus(BigInteger::aux1, BigInteger::aux2, lengthaux1);
		mult(BigInteger::aux, BigInteger::aux1, lengthaux, lengthaux1);
		rightshift(BigInteger::aux, lengthaux, nowprecision + 2);
	}
	mult(BigInteger::aux, p.a, lengthaux, p.length);
	rightshift(BigInteger::aux, lengthaux, p.length / 2 + nowprecision + 1);
	memset(BigInteger::aux2, 0, sizeof(BigInteger::aux2));
	int lengthaux2 = lengthaux;
	memcpy(BigInteger::aux2, BigInteger::aux, sizeof(int) * lengthaux);
	power(BigInteger::aux2, lengthaux2, 2);
	int flag = 0;
	if (!absgreaterequal(p.a, BigInteger::aux2, p.length, lengthaux2)){
		flag = -1;
	}
	else{
		memset(BigInteger::aux1, 0, sizeof(BigInteger::aux1));
		memset(BigInteger::aux2, 0, sizeof(BigInteger::aux2));
		lengthaux2 = lengthaux;
		memcpy(BigInteger::aux2, BigInteger::aux, sizeof(int) * lengthaux);
		int lengthaux1 = 1;
		BigInteger::aux1[0] = 1;
		add(BigInteger::aux2, BigInteger::aux1, lengthaux2, lengthaux1);
		power(BigInteger::aux2, lengthaux2, 2);
		if (absgreaterequal(p.a, BigInteger::aux2, p.length, lengthaux2)){
			flag = 1;
		}
	}
	memset(p.a, 0, sizeof(int) * p.length);
	p.length = 0;
	if (flag == -1){
		p.a[0] = 1;
		p.length = 1;
		posminus(BigInteger::aux, p.a, lengthaux);
		memcpy(p.a, BigInteger::aux, sizeof(int) * lengthaux);
		p.length = lengthaux;
	}
	else{
		if (flag){
			p.a[0] = 1;
			p.length = 1;
		}
		add(p.a, BigInteger::aux, p.length, lengthaux);
	}
}

BigInteger a, b;

int main(){
	a.read();
	b.read();
	return printf(a.greater(b) ? "GREATER\n" : a.equal(b) ? "EQUAL\n" : "LESS\n"), 0;
}

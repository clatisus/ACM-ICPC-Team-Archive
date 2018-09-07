// 拓欧求逆元模板
// inv(a, moder) 表示 a 在 (mod moder) 下的逆元，如无逆元返回 -1 

#include<bits/stdc++.h>

typedef long long ll;

// x, y 满足 |x|+|y| 最小 
template <typename T>
T ex_euc(T a, T b, T &x, T &y){
	if (!b){
		x = 1, y = 0;
		return a;
	}
	T ret = ex_euc(b, a % b, x, y), tmp = y;
	y = x - a / b * y;
	x = tmp;
	return ret;
}

template <typename T>
T inv(T a, T moder){
    T b = moder, s = 1, t = 0;
    while (b){
        T tmp = a, q = a / b;
        a = b, b = tmp % a;
        tmp = s;
        s = t;
        t = tmp - s * q;
    }
    if (a > 1) return -1;
	return s < 0 ? s + moder : s;
}

int main(){
}

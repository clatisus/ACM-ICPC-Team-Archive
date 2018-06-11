#include<bits/stdc++.h>
#define ll long long

int h, w;

int main(){
	scanf("%d%d", &h, &w);
	if (!(h % 3) || !(w % 3)){
		return printf("0\n"), 0;
	}
	ll min = INT_MAX;
	for (int i = 1; i < h; ++ i){
		ll s1 = 1ll * i * w;
		h -= i;
		int dif;
		if ((h & 1) && (w & 1)){
			dif = std::min(h, w);
		}
		else{
			dif = 0;
		}
		ll s2 = 1ll * h * w + dif >> 1, s3 = 1ll * h * w - dif >> 1;
		ll ans = std::max(std::max(s1, s2), s3) - std::min(std::min(s1, s2), s3);
		min = std::min(min, ans);
		h += i;
	}
	for (int i = 1; i < w; ++ i){
		ll s1 = 1ll * i * h;
		w -= i;
		int dif;
		if ((w & 1) && (h & 1)){
			dif = std::min(w, h);
		}
		else{
			dif = 0;
		}
		ll s2 = 1ll * w * h + dif >> 1, s3 = 1ll * w * h - dif >> 1;
		ll ans = std::max(std::max(s1, s2), s3) - std::min(std::min(s1, s2), s3);
		w += i;
		min = std::min(min, ans);
	}
	return printf("%d\n", min), 0;
}

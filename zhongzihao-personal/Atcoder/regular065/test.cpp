#include<bits/stdc++.h>

int main(){
	std::set <int> vec = {1, 2, 3, 4, 5, 6, 7, 8};
	auto it = vec.begin();
	++ it;
	for (; *it < 2; ++ it){
		vec.erase(it);
	}
	for (auto it = vec.begin(); it != vec.end(); ++ it){
		printf("%d\n", *it);
	}
	return 0;
}

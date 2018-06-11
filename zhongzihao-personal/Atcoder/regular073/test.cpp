#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = (1e5)+1;
 int n;
vector<pair<ll, ll> > a;
multiset<ll> r, b;
long long ans = LLONG_MAX;
int main() {	
	freopen("data.txt", "r", stdin);
	freopen("_E.txt", "w", stdout);
ios::sync_with_stdio(false);
cin.tie(0);	
cin >> n;
a.resize(n);	
for(int i = 0; i < n; i++) {	
	cin >> a[i].first >> a[i].second;		if(a[i].first > a[i].second) 
swap(a[i].first, a[i].second);
	}	
sort(a.begin(), a.end());
	for(auto p: a) {	
	r.insert(p.first);	
	b.insert(p.second);	}	
ans = min((*r.rbegin() - *r.begin()) * (*b.rbegin() - *b.begin()), ans);	
for(auto p: a) {	
	r.erase(r.find(p.first));		b.erase(b.find(p.second));		r.insert(p.second);	
	b.insert(p.first);	
	ans = min((*r.rbegin() - *r.begin()) * (*b.rbegin() - *b.begin()), ans);	}
	cout << ans;}

#include<bits/stdc++.h>

const int N = 100010;

std::vector <int> e[N];
int dfn[N], low[N], cnt;
int sccno[N], scc_cnt;
std::stack <int> st;

void dfs(int x){
	st.push(x);
	dfn[x] = low[x] = ++ cnt;
	for (auto &y : e[x]){
		if (!dfn[y]){
			dfs(y);
			low[x] = std::min(low[x], low[y]);
		}
		else if(!sccno[y]){
			low[x] = std::min(low[x], dfn[y]);	
		}
	}
	if (dfn[x] == low[x]){
		sccno[x] = ++ scc_cnt;
		while(st.top()!=x){
			sccno[st.top()]=scc_cnt;
			st.pop();
		}
		st.pop();
	}
}

int main(){
}

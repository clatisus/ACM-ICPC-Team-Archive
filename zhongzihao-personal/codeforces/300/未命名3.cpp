#include<bits/stdc++.h>
int main()
{
for(int k = 1; k <= n; ++ k)
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= n; ++ j){
        	if(g[i][k] == -1 || g[k][j] == -1) continue;
        	if(g[i][j] == -1 || g[i][j] > g[i][k] + g[k][j]){
        		g[i][j] = g[i][k] + g[k][j];
        	}
        }

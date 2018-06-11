## C - Painting Machines

### 题意

有$n-1$($1\le n\le10^6$)个喷漆机器，第$i$个喷漆机器可以喷涂第$i$个位置和第$i+1$个位置。

对于一个$1$到$n-1$的排列$\{P_n\}$，其分数为$k$当且仅当$P_1,\cdots,P_k$可以将$[1,n]$全部喷涂。

求所有排列的分数之和。

### 题解

假设用$a_1<a_2<\cdots<a_k$这$k$个机器可以完成喷涂，那么一定有$a_1=1,a_k=n-1,a_{i+1}-a_i\in[1,2]$.

那么合法的选取方案数为$\displaystyle \binom{k-1}{n-k-1}$，分数不大于$k$的排列数有$\displaystyle \binom{k-1}{n-k-1}\times k!\times(n-k-1)!$.


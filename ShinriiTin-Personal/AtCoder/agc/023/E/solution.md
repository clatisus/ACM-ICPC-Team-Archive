## E - Inversions

### 题意

求所有满足$P_i\le A_i$对于$i\in[n]$都成立的$1$到$n$的排列$\{P_n\}$的逆序对数之和。

### 题解

令$\displaystyle cnt[k] = \sum\limits_{i\in[n]}[A_i\ge k] - (n-k)$，则存在$P_i\le A_i$对于$i\in[n]$都成立的$1$到$n$的排列$\{P_n\}$的充分必要条件为$cnt[k]>0$对$k\in[n]$都成立。

在上述条件成立的前提下，不同的排列有$\displaystyle S = \prod\limits_{k\in[n]}cnt[k]$种。

对于每一对$i<j$，考虑有多少合法的排列满足$P_i>P_j$。

- 假如$A_i\le A_j$，则如果我们用$A_i$去替换$A_j$，求出这种情况下的合法排列数$x$，那么$\displaystyle\frac{x}{2}$就是$P_i>P_j$的合法排列数
- 假如$A_i>A_j$，则如果我们用$A_j$去替换$A_i$，求出这种情况下的合法排列数$x$，那么$\displaystyle S-\frac{x}{2}$就是$P_i>P_j$的合法排列数

那么问题就在于如何求$\sum x$，上面两种情况分开来做，先考虑如何求$A_i\le A_j$的情况，另一种处理方法类似。

令$\displaystyle D[i] = \prod\limits_{j=1}^{i}\frac{cnt[j]-1}{cnt[j]}$，则$\displaystyle x(i,j) =S\times\frac{D[A_j]}{D[A_i]}$，则对于每个$j$，我们可以用树状数组求$\displaystyle\sum\frac{1}{D[A_i]}$，但是问题在于$D[A_i]$可能为零。

令$D[i] = D^{'}[i]\times0^{x_i}$，则只有$x_i=x_j$的情况是合法的，我们可以处理出$0$因子个数相同的段，用$D^{'}$替换$D$，只在树状数组种询问与$A_j$在同一段中的$i$即可。

$A_i> A_j$的情况要注意不要统计$A_i=A_j$的情况，并且计算一下逆序对数来计算$\sum S$即可。

时间复杂度$O(n\log{n})$.
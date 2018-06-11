##[C. Party Lemonade](http://codeforces.com/contest/913/problem/C)

**题目大意：**

有$n\le30$种不同的物品，第$i$种物品的价值为$2^{i-1}$，花费为$1\le c_i\le10^9$。每种物品的数量可以认为是无穷的。
问要得到价值和至少为$1\le L\le10^9$的物品，最小的花费是多少？

**题解：**

令$f[i]$表示得到少价值和至为$2^i$的物品所需要的最小花费，则有$f[i] = \min(2\times f[i-1],c[i+1])$。

做完之后再用$f[i] = \min(f[i], f[i-1])$更新一次。

之后就递归计算最小花费$G(L)$:

- 如果$L\ge 2^{n-1}$，则$G(L) = f[n-1]\times \lfloor \frac{L}{2^{n-1}} \rfloor + G(L \mod{2^{n-1}})$

- 如果 $L = 2^{k}, 0\le k \le n-2$，则 $G(L) = f[k]$

- 如果以上两条都不满足， $2^k< L < 2^{k+1}$，则 $G(L) = \min(f[k+1],f[k] + G(L - 2^k))$

时间复杂度 $O(n)$
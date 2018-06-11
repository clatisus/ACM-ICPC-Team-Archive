## 154. Factorial

## 题意

求最小的`natural number`$N$，满足$N!$末尾的零的个数恰好等于$0\le Q\le10^8$，无解输出`No solution`。

## 题解

等价于求最小的$N$，满足$N!$中$5$的因子个数恰好为$Q$.

二分答案，然后数一下因子个数进行判断，时间复杂度$O(\log^2{ans})$.

~~`sgu`有毒吧，`0`不是`natural number`的？~~


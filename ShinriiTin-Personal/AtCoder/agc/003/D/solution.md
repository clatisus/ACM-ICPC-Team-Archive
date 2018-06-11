## [D - Anticube](https://agc003.contest.atcoder.jp/tasks/agc003_d)

**题目大意：**

给出一个长度为$n\le10^5$的整数数列$a$，$1\le a_i\le10^{10}$。

要从数列中选出尽可能多的数，满足被选出的数中，任意两个数的乘积不是立方数。

输出最多可以选出的数的数量。

**题解：**

定义$Norm(t)$为$t$去掉所有立方因子后剩余的部分，$Pair(t)$为令$t\times Pair(t)$为立方数的最小的数。

那么$a\times b$为立方数当且仅当$Norm(a)=Pair(b)$，并且显然此时$Pair(a)=Norm(b)$也成立。

如果知道每个数的$Norm$与$Pair$，则$\displaystyle ans=[|\{t|Norm(t)=x\}|>0]+\frac{\sum\limits_{x=2}\max(|\{t|Norm(t)=x\}|,|\{t|Pair(t)=x\}|)}{2}$.

利用线性筛求出$10^{\frac{10}{3}}$以内的质数。

$Norm(t)$直接枚举$t^{\frac{1}{3}}$以内的质数试除即可。

$Pair(t)$同样枚举$t^{\frac{1}{3}}$以内的质数，这一部分需要补上的因子就计算完毕了，剩余的部分$s$至多只有两个质因子。

当$s=1$或$s$为质数或$s=p\times q$时，这一部分需要补上的因子都是$s^2$，只有当$s=p^2$时，只需要补上$p$即可。

因此直接对$s$开方判断其是否为平方数即可。

时间复杂度为$\displaystyle O(maxA_i^{1/3}+\frac{n\times maxA_i^{1/3}}{\log{maxA_i}}+n\log{n})$.

需要注意的是$Pair(t)$可能会很大，超出`long long int`的范围。

但是因为$Norm(t)\le t\le10^{10}$，这样大的$Pair(t)$是找不到与其匹配的$Norm(t)$的。

因此计算过程中简单判断一下是否会超出一个足够大的上限，会的话直接令其等于上限即可，不影响计算结果。
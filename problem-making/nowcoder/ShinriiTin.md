### 未命名1（最值反演 + 树`dfs`）

**题目大意**：

我有一棵树，节点数为$n\le20$。 

一开始每个节点都是白色的。 

现在我在树上随机选择一条路径（即使这条路径上的所有点都已经被染黑），将路径上所有点都染黑（路径长度可以为1）。 

不断重复这个操作，直到所有点都变成黑色。

 问期望的操作次数是多少，取模。  

**题解**：

考虑[容斥](https://en.wikipedia.org/wiki/Maximum-minimums_identity)，枚举集合$S$，计算集合$S$中任意点被染色的最早时间的期望值。

就将集合$S$中的点当做关键点，进行`dfs`，计算有多少条路径不会经过关键点，记为$x$。

则这个期望值就是$\displaystyle \frac{n(n+1)}{2x}$.

时间复杂度$O(n\times2^n)$，空间复杂度$O(n)$.



### 未命名2（`fwt`）

**题目大意**：

我有俩数组$a$和$b$，长度都为$n$（$n$是不大于$2^{18}$的$2$的整次幂），下标从0开始。

求长度同样是$n$的数组$c$，满足$c_k = \sum\limits_{i=0}^{n-1} \sum\limits_{j=0}^{n-1} [i\text{ and }j=0][i\text{ or }j=k] a_i\times b_j$，取模。

**题解**：

构造生成函数$\displaystyle A(x) = \sum\limits_{i=0}^{n-1} a_ix^iy^{bitcnt(i)}$和$\displaystyle B(x) = \sum\limits_{i=0}^{n-1} b_ix^iy^{bitcnt(i)}$.

令$x^i \cdot x^j = x^{i\text{ or }j}$，则$C(x) = A(x) \otimes B(x)$，$c_k$就是$C(x)$中$x^ky^{bitcnt(k)}$项的系数。

这个乘法可以暴力卷积$y$，然后每次通过`fwt`计算$x$这边的运算。

$y$这边的次数界为$\log{n}$，因此一共需要进行$\log^2{n}$次或运算卷积。

但是注意到参与卷积的两边分别只有$\log{n}$种，我们可以先对它们分别进行`fwt`，之后进行$\log^2{n}$次点积运算，最后使用$\log{n}$次`fwt`逆运算即可。

时间复杂度$O(n\log^2{n})$，空间复杂度$O(n\log{n})$.
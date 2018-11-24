# 其它

## 拉格朗日插值法

对某个多项式函数，已知有给定的 $k+1$ 个取值点： $(x_{0},y_{0}),\cdots,(x_{k},y_{k})$ ，则有 $L(x)=\sum\limits_{i=0}^{k}y_{i}l_{i}(x)$ ，其中每个 $l_{i}(x)$ 为拉格朗日基本多项式，其表达式为 $l_{i}(x)=\prod\limits_{j=0,j\neq i}^{k}\frac{x-x_{j}}{x_{i}-x_{j}}$

## 牛顿迭代法

$x_{n+1}=x_{n}-\frac{f(x_{n})}{f'(x_{n})}$

## Stern-Brocut tree

设有一棵无限的区间树，根结点所表示的区间为$[\frac{0}{1}, \frac{1}{0}]$ ，设父结点所表示的区间为 $[\frac{a}{b},\frac{c}{d}]$ ，则它的左右孩子分别表示 $[\frac{a}{b},\frac{a+c}{b+d}]$ 和 $[\frac{a+c}{b+d},\frac{c}{d}]$ ，这棵树不重不漏地表示了所有正的既约的有理数。

## Tree of primitive Pythagorean triples

设有一棵无限的满三叉树，根结点表示列向量 $(3,4,5)^{T}$ ，设有三个矩阵
$$
A=\begin{pmatrix}
1&-2&2\\
2&-1&2\\
2&-2&3\\
\end{pmatrix}
$$

$$
B=\begin{pmatrix}
1&2&2\\
2&1&2\\
2&2&3\\
\end{pmatrix}
$$

$$
C=\begin{pmatrix}
-1&2&2\\
-2&1&2\\
-2&2&3\\
\end{pmatrix}
$$

设父结点的向量为 $\alpha$ ，则它从左到右的三个孩子的向量分别为 $A\alpha, B\alpha, C\alpha$ ，这棵树不重不漏地枚举完了所有基本毕达哥拉斯三元组（$a^{2}+b^{2}=c^{2}$）。

## 最大反链

给定一个非负整数数列 $\{t_{i}\}$，那么偏序集 $\prod_{i=1}^{n}\{x|0\le x\le t_{i},x\in\mathbb{Z}\}$ 的最大反链的大小等于关于 $x_{i}$ 的不定方程 $\displaystyle{\sum_{i=1}^{n}x_{i}=\lfloor\frac{\sum_{i=1}^{n}t_{i}}{2}\rfloor}$ 的非负整数解的个数。

## 矩阵乘法

设 $\oplus,\otimes$ 为二元运算，且 $\oplus$ 满足交换律和结合律，$\otimes$ 满足结合律，$\otimes$ 对 $\oplus$ 满足分配律。定义新的矩阵乘法 $A_{n,m}\times B_{m,p}=C_{n,p}$，其中 $c_{i,j}=\bigoplus_{k=1}^{m}a_{i,k}\otimes b_{k,j}$，那么这种矩阵乘法满足结合律。除了通常的 $\oplus$ 代表加法和 $\otimes$ 代表乘法外，$\oplus$ 代表取最大/最小值，$\otimes$ 代表加法；在 $[0,+\infty)$ 上定义 $\oplus$ 代表取最大/最小值，$\otimes$ 代表乘法，都满足条件。其中后两者对一些求最优值的 `dp` 优化有一定的作用。[证明](matrix_multiplication)

## gcc内建二进制函数

- `__builtin_popcount(x)` 表示 $x$ 二进制中 $1$ 的个数。
- `__builtin_parity(x)` 表示 $x$ 二进制中 $1$ 的个数的奇偶性。
- `__builtin_clz(x)` 表示 $x$ 二进制中前导 $0$ 的个数。
- `__builtin_ctz(x)` 表示 $x$ 二进制中结尾 $0$ 的个数。
- `__builtin_ffs(x)` 表示 $x$ 二进制中右起第一个 $1$ 的位置。

以上函数传入的参数为 `unsigned int`，如需对 `unsigned long long` 使用，需要在函数名的最后加上 `ll`，如 `__builtin_popcountll`。`__builtin_clz(x)` 和 `__builtin_ctz(x)` 两者在 $x=0$ 时未定义

## 一类关于集合的计数问题

设有两个集合 $A,B\subset\mathbb{N}$，且 $0\in A,1\in B,|A|=n,|B|=m$。定义 $A+B=\{x+y|x\in A,y\in B\}$，若 $A+B=[1,nm]\cap\mathbb{N}^{+}$，则称 $(A,B)$ 是好的。问这样的集合对有多少个。

这一问题的答案为：

$$
\begin{cases}
&1&(n=1\lor m=1)\\
&f(n,m)+f(m,n)&(n>1\land m>1)
\end{cases}
$$

其中 $f(n,m)=\sum_{i=1}^{+\infty}g_{i}(n)(g_{i}(m)+g_{i+1}(m))$，$g_{i}(n)$ 表示将 $n$ 分解成 $i$ 个大于 $1$ 的数的乘积的方案数（有序）。[证明](set_counting)

## 加法链

对于一个正整数 $n$，它的一个加法链是一个序列 $v_{0},\cdots,v_{s}$，其中 $v_{0}=1,v_{s}=n$，对于所有的 $v_{1},\cdots,v_{s}$，它们都是前面某两个数的和。一种常见的较短的加法链即为快速幂对指数的拆分方法。设 $n$ 的二进制表示下 $1$ 的个数为 $v(n)$，那么使用快速幂的加法链的长度为 $\lfloor\log_{2}n\rfloor+v(n)-1$。另外，设 $n$ 最短的加法链长度为 $l(n)$，$Knuth$ 猜想 $l(n)\ge\lfloor\log_{2}n\rfloor+\lceil\log_{2}v(n)\rceil$，且这一猜想对 $v(n)\le8$ 已经得到证明。

## 高斯数值积分

求一个 $[-1,1]$ 上的积分，可以使用高斯积分。它近似等于 $\sum_{i=1}^{n}w_{i}f(x_{i})$，当 $f(x)$ 可以用不超过 $2n-1$ 次的多项式近似时，此方法精度较高。下面对 $n=1\sim5$ 列出 $w$ 和 $f$ 的表。

| $n$  |                        $x_{i}$                        |            $w_{i}$            |
| :--: | :---------------------------------------------------: | :---------------------------: |
| $1$  |                          $0$                          |              $2$              |
| $2$  |                 $\pm\frac{1}{\sqrt{3}}$               |              $1$              |
| $3$  |                          $0$                          |         $\frac{8}{9}$         |
|      |                $\pm\sqrt{\frac{3}{5}}$                |         $\frac{5}{9}$         |
| $4$  | $\pm\sqrt{\frac{3}{7}-\frac{2}{7}\sqrt{\frac{6}{5}}}$ |   $\frac{18+\sqrt{30}}{36}$   |
|      | $\pm\sqrt{\frac{3}{7}+\frac{2}{7}\sqrt{\frac{6}{5}}}$ |   $\frac{18-\sqrt{30}}{36}$   |
| $5$  |                          $0$                          |       $\frac{128}{225}$       |
|      |     $\pm\frac{1}{3}\sqrt{5-2\sqrt{\frac{10}{7}}}$     | $\frac{322+13\sqrt{70}}{900}$ |
|      |     $\pm\frac{1}{3}\sqrt{5+2\sqrt{\frac{10}{7}}}$     | $\frac{322-13\sqrt{70}}{900}$ |

若积分区间不是 $[-1,1]$，那么需要变换积分区间：$\int_{a}^{b}f(x)\mathbb{d}x=\frac{b-a}{2}\int_{-1}^{1}f(\frac{b-a}{2}x+\frac{a+b}{2})\mathbb{d}x$


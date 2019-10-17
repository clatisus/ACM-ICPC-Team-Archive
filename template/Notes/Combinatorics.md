# 组合数学

## 划分数

设 $p(n)$ 为将 $n$ 写成若干个正整数和的方案数，若 $i$ 为自然数，称 $\frac{3i^{2}-i}{2}$ 和 $\frac{3i^{2}+i}{2}$ 为广义五边形数，并定义 $f(\frac{3i^{2}-i}{2}) = f(\frac{3i^{2}+i}{2}) = i$，则 $p(n) = \sum_{u,1 \le u \le n}(-1)^{f(u) - 1}p(n-u)$，其中 $u$ 为广义五边形数。$\displaystyle{\phi(x)=\prod_{i=1}^{\infty}(1-x^{i})}$ 称为欧拉函数，它是划分数生成函数的逆。$\phi(x) = \sum_{u}(-1)^{f(u)}x^{u}$，其中 $u$ 为广义五边形数。从 $0$ 开始，$p(n)$ 的前若干项为 $1,1,2,3,5,7,11,15,22,30,42,56,77$ 。

## 模2意义下的组合数

${n\choose m}\% 2=!(m\And\sim n)$。由此易知，${n\choose m}\% 2=1$，当且仅当 $n$ 在 $m$ 为 $1$ 的二进制位上也都为 $1$。易知，${n+m\choose m}\% 2=1$，当且仅当 $n$ 在 $m$ 为 $1$ 的二进制位上都为 $0$。

## 默慈金数

设 $M_{n}$ 表示在一个圆上的 $n$ 个不同点间，画出彼此不相交的弦的全部方法的总数。$M_{0} = M_{1} = 1, M_{n + 1} = M_{n}+\sum_{i=0}^{n-1}M_{i}M_{n-i-1} = \frac{2n+3}{n+3}M_{n}+\frac{3n}{n+3}M_{n-1}$。它也可以表示数列 $\{a_{i}\}(0 \le i \le n)$ 的数量，满足：$a_{0} = a_{n} = 0, a_{i} \ge 0, |a_{i}-a_{i + 1}| \le 1$。从 $0$ 开始，$M_{n}$ 的前若干项为
$$
\begin{aligned}
&1,1,2,4,9,21,51,127,323,835,2188,\\
&5798,15511,41835,113634,310572,853467,\\
&2356779,6536382,18199284,50852019,142547559,\\
&400763223,1129760415,3192727797,9043402501,\\
&25669818476,73007772802,208023278209,593742784829
\end{aligned}
$$

## 卡特兰数

设 $C_{0}=1,C_{n}=\sum_{i=0}^{n-1}C_{i}C_{n-i-1}$，它满足 $\displaystyle{C_{n} = \frac{C_{2n}^{n}}{n+1}}$，它可以表示：

- $n$ 对括号组成的合法的表达式种数
- $n$ 个结点不同构二叉树的方案数
- $n \times n$ 格点中不越过对角线的单调路径的个数。单调路径是指从左下角走到右上角，每步向右或向上。
- 通过连接顶点将 $n+2$ 条边的凸多边形分成三角形的方案数
- 以 $\{1, 2, \cdots, n\}$ 为进栈序列的合法出栈序列个数
- 集合 $\{1, 2, \cdots, n\}$ 的不交叉划分的个数
- 用 $n$ 个长方形填充一个高度为 $n$ 的阶梯状图形的方法个数

从 $0$ 开始， $C_{n}$ 的前若干项为
$$
\begin{aligned}
&1,1,2,5,14,42,132,429,1430,\\
&4862,16796,58786,208012,742900,\\
&2674440,9694845,35357670,129644790,\\
&477638700,1767263190
\end{aligned}
$$

## 伯努利数

$B_{0} = 1, B_{i}=1-\sum_{j = 0}^{i-1}C_{i}^{j}\frac{B_{j}}{i-j+1}.$ 伯努利数的指数型母函数是 $\frac{x}{e^{x}-1}.$ 伯努利数可用于计算等幂和：$\sum_{k = 1}^{n}k^{m} = \frac{1}{m+1}\sum_{k=0}^{m}C_{m+1}^{k}B_{k}n^{m+1-k}.$ 从 $0$ 开始，$B_{n}$ 的前若干项为 $1,\frac{1}{2},\frac{1}{6},0,-\frac{1}{30},0,\frac{1}{42},0,-\frac{1}{30}$

## 上升阶乘幂和下降阶乘幂
$(x)^{(n)}=x(x+1)(x+2)\cdots(x+n-1)$ 称为上升阶乘幂， $(x)_{n}=x(x-1)(x-2)\cdots(x-n+1)$ 称为下降阶乘幂。 满足：

- $(a+b)^{(n)}=\sum_{i=0}^{n}{n\choose i}(a)^{(n-j)}(b)^{(j)}$
- $(a+b)_{n}=\sum_{i=0}^{n}{n\choose i}(a)_{n-j}(b)_{j}$
- $(x)_{m}(x)_{n}=\sum_{k=0}^{m}{m\choose k}{n\choose k}k!(x)_{m+n-k}$

## 斯特林数

### 第一类斯特林数

$\begin{bmatrix}n\\k\end{bmatrix}$ 表示 $n$ 个元素的置换中能被分解为 $k$ 个循环的置换个数，并定义 $s(n,k)=(-1)^{n-k}\begin{bmatrix}n\\k\end{bmatrix}$。 $\begin{bmatrix}n+1\\k\end{bmatrix}=n\begin{bmatrix}n\\k\end{bmatrix}+\begin{bmatrix}n\\k-1\end{bmatrix}(k>0)$，$\begin{bmatrix}0\\0\end{bmatrix}=1$，$\begin{bmatrix}n\\0\end{bmatrix}=\begin{bmatrix}0\\n\end{bmatrix}=0(n>0)$。
该数列满足：

- $(x)^{(n)}=\sum_{k=0}^{n}\begin{bmatrix}n\\k\end{bmatrix}x^{k}$
- $(x)_{n}=\sum_{k=0}^{n}s(n,k)x^{k}$

也就是说，对于一个固定的 $n$，$(x)^{(n)}$ 和 $(x)_{n}$ 分别是 $\{\begin{bmatrix}n\\k\end{bmatrix}\}$ 和 $\{s(n,k)\}$ 的生成函数。

对于一个固定的 $k$，$\{\begin{bmatrix}n\\k\end{bmatrix}\}$ 的指数型生成函数为：$\displaystyle{\frac{\ln^{k}\frac{1}{1-x}}{k!}=\sum_{n=k}^{+\infty}\begin{bmatrix}n\\k\end{bmatrix}\frac{x^{n}}{n!}}$。

另外还有：

- $\begin{bmatrix}n\\m\end{bmatrix}=\sum_{k}\begin{bmatrix}n+1\\k+1\end{bmatrix}{k\choose m}(-1)^{m-k}$
- $\begin{bmatrix}n+1\\m+1\end{bmatrix}=\sum_{k=0}^{n}\begin{bmatrix}k\\m\end{bmatrix}\frac{n!}{k!}$
- $\begin{bmatrix}m+n+1\\m\end{bmatrix}=\sum_{k=0}^{m}(n+k)\begin{bmatrix}n+k\\k\end{bmatrix}$
- $\begin{bmatrix}n\\l+m\end{bmatrix}{l+m\choose l}=\sum_{k}\begin{bmatrix}k\\l\end{bmatrix}\begin{bmatrix}n-k\\m\end{bmatrix}{n\choose k}$

### 第二类斯特林数

$\begin{Bmatrix}n\\k\end{Bmatrix}$ 表示有 $n$ 个元素的集合划分为 $k$ 个集合的方案数。$\begin{Bmatrix}n+1\\k\end{Bmatrix}=k\begin{Bmatrix}n\\k\end{Bmatrix}+\begin{Bmatrix}n\\k-1\end{Bmatrix}(k>0)$，$\begin{Bmatrix}0\\0\end{Bmatrix}=1$，$\begin{Bmatrix}n\\0\end{Bmatrix}=\begin{Bmatrix}0\\n\end{Bmatrix}=0(n>0)$。
该数列满足：

- $\begin{Bmatrix}n\\k\end{Bmatrix}=\frac{1}{k!}\sum_{i=0}^{k}(-1)^{i}{k\choose i}(k-i)^{n}$

容易注意到这是一个卷积形式，可以 $\mathcal{O}(n\log n)$ 地求出一个 $n$ 对应的所有第二类斯特林数

- $\sum_{k=0}^{n}\begin{Bmatrix}n\\k\end{Bmatrix}(x)_{k}=x^{n}$
- $B_{n}=\sum_{k=0}^{n}\begin{Bmatrix}n\\k\end{Bmatrix}$（其中 $B_{n}$ 是贝尔数）

对于一个固定的 $k$，$\{\begin{Bmatrix}n\\k\end{Bmatrix}\}$ 的生成函数为 $\displaystyle{\sum_{n=k}^{+\infty}\begin{Bmatrix}n\\k\end{Bmatrix}x^{n}=\frac{x^{k}}{\prod_{i=1}^{k}1-kx}}$，其指数型生成函数为 $\displaystyle{\sum_{n=k}^{+\infty}\begin{Bmatrix}n\\k\end{Bmatrix}\frac{x^{n}}{n!}=\frac{(e^{x}-1)^{k}}{k!}}$。

## 贝尔数

设 $B_{n}$ 表示基数为 $n$ 的集合的划分方法数，则 $B_{n}$ 满足 $B_{n+1}=\sum_{k=0}^{n}{n\choose k}B_{k}$，$B_{n}=\sum_{k=0}^{n}S(n, k)$，其中 $S$ 是第二类斯特林数，对任意质数 $p$ 有 $B_{n+p^{m}}\equiv mB_{n}+B_{n+1}\pmod{p}$，其指数型母函数是 $\sum_{n=0}^{\infty}\frac{B_{n}}{n!}x^{n}=e^{e^{x}-1}$。从 $0$ 开始，$B_{n}$ 的前若干项为 
$$
\begin{aligned}
&1,1,2,5,15,52,203,877,\\
&4140,21147,115975,678570,\\
&4213597,27644437,190899322,\\
&1382958545,10480142147,82864869804,\\
&682076806159,5832742205057,51724158235372,\\
&474869816156751,4506715738447323,44152005855084346,\\
&445958869294805289,4638590332229999353,49631246523618756274
\end{aligned}
$$

## Burnside 引理

设 $G$ 是一个有限群，作用于集合 $X$ 上，对 $\forall g\in G$，$X^{g}$ 表示 $X$ 中在 $g$ 作用下的不动元素的集合，$|X/G|$ 表示 $X$ 在 $G$ 作用下的轨道数，则有 $|X/G|=\frac{1}{|G|}\sum_{g\in G}|X^{g}|$。

## Polya 定理

设 $\bar{G}$ 是 $n$ 个对象的一个置换群，用 $m$ 种颜色涂染这 $n$ 个对象，则不同染色的方案数为 $l=\frac{1}{|\bar{G}|}(m^{c(\bar{a_{1}})}+m^{c(\bar{a_{2}})}+\cdots+m^{c(\bar{a_{g}})})$ ，其中 $c(\bar{a_{i}})$ 表示置换 $\bar{a_{i}}$ 的循环节数。

## 切比雪夫多项式

第一类切比雪夫多项式为 $T_{n}(\cos x)=\cos nx$ ，满足 $\displaystyle{[x^{m}]T_{n}=(-1)^{\frac{n-m}{2}}\frac{n}{m}{\frac{n+m}{2}-1\choose m-1}2^{m-1}}$ 。第二类切比雪夫多项式为 $U_{n}(\cos x)=\frac{\sin(n+1)x}{\sin x}$ ，满足 $\displaystyle{[x^{m}]U_{n}=(-1)^{\frac{n-m}{2}}{\frac{n+m}{2}\choose \frac{n-m}{2}}2^{m}}$ 。

## 杨式矩阵和钩子公式

杨式矩阵是指满足以下两个条件的矩阵：

- 如果格子 $(i,j)$ 没有元素，则它右边和上边的相邻格子也一定没有元素。
- 如果格子 $(i,j)$ 有元素 $a_{i,j}$ ，则它右边和上边的相邻格子要么没有元素，要么有元素且比 $a_{i,j}$ 大。

$1\sim n$所组成杨氏矩阵的个数可以通过下面的递推式得到：

$F_{1}=1,F_{2}=2,F_{n}=F(n-1)+(n-1)F(n-2)$

钩子公式是指：对于给定形状，不同的杨氏矩阵的个数为：$n!$  除以每个格子的钩子长度加 $1$ 的积。其中钩子长度定义为该格子右边的格子数和它上边的格子数之和。

## 全错排

$1\sim n$ 的全错排数量为 $n!\sum_{i=0}^{n}(-1)^{i}\frac{1}{i!}$

## 可拆分排列

排列的直和是指将两个排列拼起来，将右边的排列平移；排列的斜和是指将两个排列拼起来，将左边的排列平移。例如 $1,2$ 和 $1,2,3$ 的直和为 $1,2,3,4,5$，斜和为 $4,5,1,2,3$。定义可拆分排列为可以由 $1$ 这一种排列经过若干次斜和和直和的运算得到的排列。

## 大 $Schr\ddot{o}der$ 数

设 $S_{n}$ 表示从 $(0,0)$ 走到 $(n,n)$，每次只能向右、向上、向右上走一步，且不能跨过 $(0,0)$ 到 $(n,n)$ 的对角线的不同走法数量。那么有 $S_{0}=1,S_{1}=2,S_{n}=3S_{n-1}+\sum_{k=1}^{n-2}S_{k}S_{n-k-1}$。$S_{n}$ 的生成函数是 $\frac{1-x-\sqrt{x^{2}-6x+1}}{2x}$。$S_{n}=\sum_{i=0}^{n}\frac{1}{n-i+1}\frac{(2n-i)!}{i!((n-i)!)^{2}}$。

$S_{n}$ 还可以表示长度为 $n+1$ 的可拆分排列的数量。

从 $0$ 开始，$S_{n}$ 的前若干项为
$$
\begin{aligned}
&1,2,6,22,90,394,\\
&1806,8558,41586,206098,\\
&1037718,5293446,27297738,\\
&142078746,745387038,3937603038,\\
&20927156706,111818026018,600318853926,\\
&3236724317174,17518619320890,95149655201962,\\
&518431875418926,2832923350929742,15521467648875090
\end{aligned}
$$

## 小 $Schr\ddot{o}der$ 数

设 $s_{0}=1,s_{i+1}=\frac{S_{i}}{2}$，那么 $s_{n}=\frac{1}{n}((6n-9)s_{n-1}-(n-3)s_{n-2})$。$s_{n}$ 可以表示：

- 将 $n+1$ 边形剖分的方案数
- 给 $n$ 个数加括号的方案数

## 库默尔定理

设 $p$ 为质数，$a,b$ 在 $p$ 进制下的表示分别为 $\overline{\cdots a_{n}\cdots a_{0}}$ 和 $\overline{\cdots b_{n}\cdots b_{0}}$，那么 ${a\choose b}$ 中含有质因子 $p$ 的个数为满足 $\overline{\cdots a_{i}\cdots a_{0}}<\overline{\cdots b_{i}\cdots b_{0}}$ 的下标 $i$ 的个数。特别的，当 $a<b$ 时，${a\choose b}=0$，而满足条件的 $i$ 也有无穷多个。从另一种角度来说，也可以理解成 $b$ 和 $a-b$ 在做 $p$ 进制加法时产生进位的次数。这可以得到一个显然的推论：${a\choose b}$ 中 $p$ 的个数不超过 $\log_{p}a$。

## 不动函数的数量

设 $f:\{1,2,\cdots,n\}\to\{1,2,\cdots,n\}$，且 $\overbrace{f\circ\cdots\circ f}^{k个}(i)=f(i)$ 对 $\{1,2,\cdots,n\}$ 成立，那么满足条件的 $f$ 指数型生成函数为 $\exp(\sum_{i\mid k-1}(x\cdot \exp(x))^{i}/i)$

## 其它

$\sum{n\choose2k}{k\choose m}=\frac{n}{n-m}{n-m\choose n-2m}2^{n-2m-1}$

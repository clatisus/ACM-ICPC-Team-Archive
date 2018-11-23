# Best Theorem
边编号，则有向图中本质不同的欧拉回路数量为：

$$
ec(G) = t_w(G) \prod_{v \in V}{(\deg(v) - 1)!}
$$

其中，$t_w(G)$ 表示以 $w$ 为根的树形图个数，deg 是入度，这里 $w$ 可以任选。通过 Matrix-Tree theorem 可知，有向图中以 $w$ 为根的树形图个数，等于该图对应的基尔霍夫矩阵对于 $w$ 所在行列的余子式。其中基尔霍夫矩阵等于入度矩阵减去反图的邻接矩阵。

# 2-Sat

判断变量 $x_i$ 是否可以取 $1$，如果 $x_i$ 和 $\lnot x_i$ 不在一个连通块，那么 $x_i$ 可以取任意值；否则在一个连通块，那么 $x_i$ 在 $\lnot x_i$ 拓扑序后面的时候可以取 $1$。模板中只需要判断 `bel[i] < bel[i + n]` 即可。

# Matrix Tree

无向图关联矩阵 $B$，行是点，列是边。若 $e_k=(v_i,v_j)$ 那么 $B_{ik},B_{jk}$ 中一个为 $1$ 一个为 $-1$。它的 Kirchhoff 矩阵为 $BB^T$，也即度数矩阵 $-$ 邻接矩阵。

性质：

1. 任意图 $G$ 的 Kirchhoff 矩阵 $C$ 的行列式为 $0$（行/列向量和为 $0$ 向量）

2. 不连通图 $G$ 的 Kirchhoff 矩阵 $C$ 的任一个 $n-1$ 阶主子式行列式为 $0$

3. 若 $G$ 是一棵树，任一个 $n-1$ 阶主子式行列式为 $1$

根据 Cauchy–Binet formula，把 $C_r=B_rB_r^T$ 展开，得到：

$$
\begin{aligned}
|C\_r|=|B\_rB\_r^T|&=\sum\_{S\subset \{1,2,\dots,m\},|S|=n-1}|(B\_r)\_S||(B\_r)\_S^T|\\\\
&=\sum\_{S\subset \{1,2,\dots,m\},|S|=n-1}|(B\_r)\_S|^2
\end{aligned}
$$

若 $S$ 中 $n-1$ 条边形成了树，那么贡献 $1$；否则贡献 $0$

推广：

1. 自环删掉，重边 $(i,j)$ 有 $m$ 条边，则 $C_{ij}=C_{ji}=-m$，度数同样要计算在内。

2. 有向图，入度矩阵 $-$ 邻接矩阵，行向量之和为 $0$ 向量。

3. 边带权，令 $C_{ij}=C_{ji}=-w_{ij},C_{ii}=-\sum_{i\neq j}C_{ij}$。则 $n-1$ 阶主子式的值为：

$$
\sum_{T\text{ form a tree }}\left(\prod_{e\in T}w_e\right)
$$

4. 求恰有 $k$ 条特殊边的生成树个数，把 $k$ 条边边权设为 $x$，那么 $n-1$ 阶主子式的值是一个多项式，对应阶的系数即为答案。可以用插值而不是多项式高消求解。

# 上下界网络流

## 1.无源无汇有容量下界网络的可行流
$step1.$ 建立附加源 $s$ 和汇 $t$。

$step2.$ 添加弧 $t\to s$ 并设容量为无穷大。

$step3.$ 将原图中上界为 $c$，下界为 $b$ 的弧 $u\to v$ 拆成三条弧：$s\to v$ 和 $u \to t$，容量都为 $b$，以及 $u\to v$，流量为 $c-b$。

$step4.$ 对附加弧进行合并：对于原图中每个点 $i$ 记录 $d[i]=\sum\limits_{e:s\to i} cap(e) - \sum\limits_{e:i\to t} cap(e)$。
如果 $d[i]>0$，则连一条容量为 $d[i]$ 的弧 $s\to i$；如果 $d[i]<0$，则连一条容量为 $-d[i]$ 的弧 $i\to t$。

$step5.$ 求改造后的网络的s-t最大流，当且仅当所有的附加弧满载时原网络有可行流。

## 2.有源汇有容量下界网络的s-t可行流

$step1.$ 建立超级源 $ss$ 和 $tt$。

$step2.$ 添加弧 $t\to s$ 并设容量为无穷大。

$step3.$ 将原图中上界为 $c$，下界为 $b$ 的弧 $u\to v$ 拆成三条弧：$ss\to v$ 和 $u \to tt$，容量都为 $b$，以及 $u\to v$，流量为 $c-b$。

$step4.$ 对附加弧进行合并：对于原图中每个点 $i$ 记录 $d[i]=\sum\limits_{e:ss\to i} cap(e) - \sum\limits_{e:i\to tt} cap(e)$。
如果 $d[i]>0$，则连一条容量为 $d[i]$ 的弧 $ss\to i$，如果 $d[i]<0$，则连一条容量为 $-d[i]$ 的弧 $i\to tt$。

$step5.$ 求改造后的网络的ss-tt最大流，当且仅当所有的附加弧满载时原网络有s-t可行流。

# 霍尔婚配定理

左部为 $X$，右部为 $Y$ 的二分图 $G=(X+Y,E)$ 中（不妨假设$|X|\le|Y|$），存在一个匹配覆盖 $X$ 的充分必要条件是：$\displaystyle\forall S(S\subseteq X \to\left|S\right|\le\left|\bigcup\limits_{x\in S}T(x)\right|)$，其中 $T(x)=\{y|y\in Y\land\left[(x,y)\in E\right]\}$。

# 广义霍尔定理

二分图 $A+B$ 中存在一个匹配能覆盖顶点集合 $X+Y$ 的充要条件是存在一个匹配能覆盖 $X$，且存在一个匹配能覆盖 $Y$（$X\in A\land Y\in B$）。
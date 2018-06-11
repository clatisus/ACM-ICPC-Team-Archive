## [B - Mysterious Light](https://agc001.contest.atcoder.jp/tasks/agc001_b)

**题目大意：**

有一边长为$N$的正三角形$ABC$，在$AB$边上有一点$P$,$AP=X$，从点$P$沿$BC$方向出射一条光线，光线遇到三角形边界或者它自己的轨迹，都会发生反射，当光线再次回到$P$时将被吸收。求光线轨迹的长度。

$2\le N\le 10^{12},1\le X<N$，$N,X$均为整数。

**题解：**

光线的方向始终平行于正三角形某一条边，并会不断重复一个过程：从边长为$a,b$的平行四边形某边经过邻边的反射射向内部。

令$f(a,b)$表示这一过程的轨迹长度，则答案为$N+f(N-X,X)$。

不妨令$a\le b$，则$f(a,a)=a$，$f(a,b)=2a+f(b,b-a)$，这样就得到了$O(N)$的递推。

考虑用类欧几里得算法来加速计算，令$f(0,a)=-a$，则当$0<a\le b$时，有$\displaystyle f(a,b)=2a\times\lfloor\frac{b}{a}\rfloor+f(b\mod{a},a)$。

时间复杂度$O(\log{N})$.
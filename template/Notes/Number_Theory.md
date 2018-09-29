# 数论

## 连分数与佩尔方程

记 $<x_{0},x_{1},x_{2},x_{3},\cdots> = x_{0}+\frac{1}{x_{1}+\frac{1}{x_{2}+\frac{1}{x_{3}+\cdots}}}$ ，其中 $x_{i}>0(i\ge1)$ 。称 $\frac{p_{n}}{q_n}=<x_{0},x_{1},\cdots,x_{n}>$ 为它的第 $n$ 个渐近分数。补充定义 $p_{-1}=1,q_{-1}=0$ ，则有递推式 $p_{n}=x_{n}p_{n-1}+p_{n-2},q_{n}=x_{n}q_{n-1}+q_{n-2}(n\ge1)$ 。对无限简单连分数，我们称 $\xi_{n}=<x_{n},x_{n+1},\cdots>$ 为它的第 $n$ 个完全商，满足 $\xi_{0}=\frac{p_{n}\xi_{n+1}+p_{n-1}}{q_{n}\xi_{n+1}+q_{n-1}}$。一个实数是二次根式当且仅当它是循环简单连分数，我们用 $<x_{0},\cdots,x_{m_{0}-1},<\overline{x_{m_{0}},\cdots,x_{m_{0}+l-1}}>>$ ，其中 $l$ 是 $\xi_{0}$ 的周期。设 $\xi_{0}=\frac{\sqrt{d}+c_{0}}{r_{0}},q_{0}|d-c^{2}_{0}$ ，我们有 $\xi_{n}=\frac{\sqrt{d}+c_{n}}{r_{n}}$ ，其中 $r_{n+1}=r_{n-1}+\frac{c_{n}^{2}-c_{n+1}^{2}}{r_{n}}=r_{n-1}+(c_{n}-c_{n+1})x_{n}$,$c_{n+1}=x_{n}r_{n}-c_{n}$,$a_{n}=\lfloor\xi_{n}\rfloor(n\ge1)$ 。

我们给出两个不定方程： $x-dy^{2}=1$ 和 $x-dy^{2}=-1$ ，若 $d$ 为完全平方数，则第一个方程只有解 $(\pm1,0)$ ，第二个方程无解。若 $d$ 不为完全平方数，设 $\xi_{0}=\sqrt{d}$ ，设它的循环连分数周期为 $l$ ，渐近分数为 $\frac{p_{n}}{q_{n}}$ ，则：

- 当 $l$ 为偶数时，第一个方程的全体正解为 $x=p_{jl-1},y=q_{jl-1},j=1,2,3,\cdots$ ，第二个方程无解
- 当 $l$ 为奇数时，第一个方程的全体正解为 $x=p_{jl-1},y=q_{jl-1},j=2,4,6,\cdots$ ，第二个方程的全体正解为 $x=p_{jl-1},y=q_{jl-1},j=1,3,5,\cdots$

还有另一种更加简单的表示方法：

- 当 $l$ 为偶数时，第一个方程的全体解为 $x+y\sqrt{d}=\pm(p_{l-1}\pm q_{l-1}\sqrt{d})^{j},j=0,1,2,\cdots$ ，第二个方程无解
- 当 $l$ 为奇数时，第一个方程的全体正解为 $x+y\sqrt{d}=\pm(p_{l-1}\pm q_{l-1}\sqrt{d})^{j},j=0,2,4,\cdots$ ，第二个方程的全体正解为 $x+y\sqrt{d}=\pm(p_{l-1}\pm q_{l-1}\sqrt{d})^{j},j=1,3,5,\cdots$

## 指数循环节

对 $\forall a, b, n \in N^{+}, b \ge \phi(n)$ ，有 $a ^ {b} \equiv a ^ {b \% \phi(n) + \phi(n)}\pmod{n}$ ，注意 $b \ge \phi(n)$ 是必要条件，以及式子中取模后指数必须加上 $\phi(n)$ ，否则结果可能会出错。

## 威尔逊定理

$$
\prod_{i=1,\text{gcd}(i,m)=1}^{m}i\equiv\begin{cases}
&-1&(m=1,2,4,p^{l},2p^{l},\text{ p is odd prime})\\
&1&(\text{otherwise})
\end{cases}\pmod{m}
$$

## 类欧几里得算法

设 $f(a,b,c,n,t_{1},t_{2})=\sum_{i=0}^{n}i^{t_{1}}\lfloor\frac{ai+b}{c}\rfloor^{t_{2}}$，求解这一函数值的算法称为类欧几里得算法。这里仅讨论 $6$ 个参数均为非负整数的情况，且定义 $0^{0}=1$：

定义 $m=\lfloor\frac{an+b}{c}\rfloor$，$g_{t}(x)=(x+1)^{t}-x^{t}=\sum_{i=0}^{t-1}g_{ti}x^{i}$，$h_{t}(x)=\sum_{i=1}^{x}i^{t}=\sum_{i=0}^{t+1}h_{ti}x_{i}$。

- 若 $t_{2}=0$，有：

$$
原式=h_{t_{1}}(n)+[t_{1}=0]
$$

- 若 $m=0$，有：

$$
原式=0
$$

- 若 $a=0$，有：

$$
原式=\lfloor\frac{b}{c}\rfloor^{t_{2}}(h_{t_{1}}(n)+[t_{1}=0])
$$

- 若 $a\ge c$ 或 $b\ge c$，有：

$$
原式=\sum_{u_{1}+u_{2}+u_{3}=t_{2}}{t_{2}\choose u_{1},u_{2},u_{3}}(\lfloor\frac{a}{c}\rfloor)^{u_{2}}(\lfloor\frac{b}{c}\rfloor)^{u_{3}}f(a\%c,b\%c,c,n,t_{1}+u_{2},u_{1})
$$

- 若 $0\le a,b<c$，有：

$$
原式=m^{t_{2}}h_{t_{1}}(n)-\sum_{u=0}^{t_{2}-1}\sum_{v=0}^{t_{1}+1}g_{t_{2}u}h_{t_{1}v}f(c,c-b-1,a,m-1,u,v)
$$

特别地，若 $t_{1}=0,t_{2}=1$，则有：

- 若 $m=0$，有：

$$
原式=0
$$

- 若 $a=0$，有：

$$
原式=\lfloor\frac{b}{c}\rfloor(n+1)
$$

- 若 $a\ge c$ 或 $b\ge c$，有：

$$
原式=\frac{n(n+1)}{2}\lfloor\frac{a}{c}\rfloor+(n+1)\lfloor\frac{b}{c}\rfloor+f(a\%c,b\%c,c,n,t_{1},t_{2})
$$

- 若 $0\le a,b<c$，有：

$$
原式=nm-f(c,c-b-1,a,m-1,t_{1},t_{2})
$$

[证明](similar_euclid)

## 其他

$x^{2}+y^{2}=t$ 的整数解的个数为 $4(\sigma_{1}(t)-\sigma_{3}(t))$，其中 $\sigma_{1}(t)$ 表示 $t$ 的约数中模 $4$ 余 $1$ 的个数，$\sigma_{3}(t)$ 表示 $t$ 的约数中模 $4$ 余 $3$ 的个数。


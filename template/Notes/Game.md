# 博弈论

## 威佐夫游戏

有两堆石子，两人轮流取，每次可以从一堆中取若干颗石子，也可以从两堆中取一样多的石子。负态为$\{\lfloor k\cdot\frac{1+\sqrt{5}}{2}\rfloor, k+\lfloor k\cdot\frac{1+\sqrt{5}}{2}\rfloor\}(k = 0,1,2,\cdots)$

## 翻硬币游戏

翻硬币游戏是指这样的一种组合游戏：有 $n$ 枚硬币排成一排，开始时它们有的正面朝上，有的反面朝上，两名玩家轮流按照一定的规则，翻转一些硬币，最后不能操作者输。这里的规则必须满足以下两点：

- 最右边的硬币必须是从正面翻转到反面（为了保证游戏结束）
- 规则允许的翻转位置集合唯一取决于最右侧硬币的位置，而与之前的操作、玩家等无关（为保证这是一个平等博弈）

翻硬币游戏有这样一个结论：一个局面的 $sg$ 值等于所有正面硬币的 $sg$ 值的异或，以 `H` 表示正，`T` 表示反，例如：$sg(THHTTH)=sg(TH)\oplus sg(TTH)\oplus sg(TTTTTH)$。

## Nim 积

$a\otimes b=\text{mex}\{a'\otimes b\oplus a\otimes b'\oplus a'\otimes b'|0\le a'<a,0\le b'<b\}$ 满足交换律，结合律，对 nim 和（异或）满足分配律。全体非负整数在 nim 和和 nim 积下成一域。Tartan Games（即二维硬币游戏）的 $sg$ 值是对应行列的 nim 积。

nim积还具有如下的性质：

- 对全体自然数 $n$ ， $[0,2^{2^{n}}-1]$ 中的自然数在 nim 和和 nim 积下成一域
- 对全体自然数 $n$ ， $2^{2^{n}}\otimes x=2^{2^{n}}\times x(0\le x<2^{2^{n}})$
- 对全体自然数 $n$ ， $2^{2^{n}}\otimes 2^{2^{n}}=\frac{3}{2}\cdot2^{2^{n}}=2^{2^{n}}\oplus2^{2^{n}-1}$

## surreal number

$surreal\;number$ 是一个包含无穷小、无穷大和实数的域，用它可以十分方便地研究一些不平等博弈问题。 $surreal\;number$ 定义为一个集合对 $\{L|R\}$ ，其中 $L$ 中的每个元素小于 $R$ 中的每个元素。我们称 $x\le y$ 当且仅当不存在 $x_{L}\in X_{L}$ 使得 $y\le x_{L}$ ，且不存在 $y_{R}\in Y_{R}$ 使得 $y_{R}\le x$ 。 $surreal\;number$ 有如下的一些性质：

- 对于一个 $surreal\;number$ $x=\{L|R\}$  ， $x$ 大于 $L$ 中的任意一个元素，小于 $R$ 中的任意一个元素。
- 对于一个 $surreal\;number$ $x=\{L|R\}$ ，若 $L$ 有最大值 $l_{max}$，则 $x=\{l_{max}|R\}$ ，对于 $R$ 同理。
- 设 $a$ 到 $b$ 之间最早出生的 $surreal\;number$ 在第 $i$ 天出生，那么在 $a$ 到 $b$ 之间且在第 $i$ 天出生的 $surreal\;number$ 有且只有一个。
- 若 $a<x<b$ 且 $x$ 是 $a$ 和 $b$ 之间最早出生的 $surreal\;number$ ，则 $x=\{a|b\}$ 

$surreal\;number$ 的加法法则为 $x+y=\{X_{L}|X_{R}\}+\{Y_{L}|Y_{R}\}=\{X_{L}+y,x+Y_{L}|X_{R}+y,x+Y_{R}\}$ 。

$surreal\;number$ 的取反法则为 $-x=-\{X_{L}|X_{R}\}=\{-X_{R}|-X_{L}\}$ 

$surreal\;number$ 的乘法法则为 $xy=\{X_{L}|X_{R}\}\{Y_{L}|Y_{R}\}=\{X_{L}y+xY_{L}-X_{L}Y_{L}，X_{R}y+xY_{R}-X_{R}Y_{R}|X_{L}y+xY_{R}-X_{L}Y_{R}，xY_{L}+X_{R}y-X_{R}Y_{L}\}$

$surreal\;number$ 的取逆法则为 $\displaystyle{\frac{1}{y}=\{0,\frac{1+(y^{R}-y)(\frac{1}{y})^{L}}{y^{R}},\frac{1+(y^{L}-y)(\frac{1}{y})^{R}}{y^{L}}|\frac{1+(y^{L}-y)(\frac{1}{y})^{L}}{y^{L}},\frac{1+(y^{R}-y)(\frac{1}{y})^{R}}{y^{R}}\}}$ ，其中 $y^{L}>0,y^{R}>0$

设有一组合游戏处于局面 $P$ ，玩家 $L$ 可以转移到的状态为 $P^{L}$ ，玩家 $R$ 可以转移到的状态为 $P^{R}$ ，我们记 $P=\{P^{L}|P^{R}\}$ 。那么：

- 若 $P>0$ ，则不论先手还是后手， $L$ 获胜
- 若 $P<0$ ，则不论先手还是后手， $R$ 获胜
- 若 $P=0$ ，则后手获胜

类似于 $Nim$ 和游戏，若有 $n$ 个不平等游戏 $P_{1},\cdots,P_{n}$ ，它们分别对应的 $surreal\;number$ 为 $x_{1},\cdots,x_{n}$ ，则 $P_{1}+\cdots+P_{n}$ 对应的 $surreal\;number$ 为 $x_{1}+\cdots+x_{n}$ 。

最后给出一些无穷大和无穷小的 $surreal\;number$

$$
\begin{aligned}\\
&\{0|1,\frac{1}{2},\frac{1}{4},\cdots\}=\epsilon(无穷小)\\
&\{0,1,2,3,\cdots|\}=\omega(无穷大)\\
&\{\epsilon|1,\frac{1}{2},\frac{1}{4},\cdots\}=2\epsilon\\
&\{0|\epsilon\}=\frac{\epsilon}{2}\\
&\{0,1,2,3,\cdots,\omega|\}=\omega+1\\
&\{0,1,2,3,\cdots|\omega\}=\omega-1\\
&\{\omega|\omega+1\}=\omega+\frac{1}{2}\\
\end{aligned}\\
$$


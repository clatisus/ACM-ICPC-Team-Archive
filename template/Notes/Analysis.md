# 数学分析

## Wallis公式

$$
\frac{\pi}{2} = \lim_{n \to +\infty}\frac{[\frac{(2n)!!}{(2n-1)!!}]^{2}}{2n+1}
$$

## Stirling公式

$$
n!\sim\sqrt{2\pi n}(\frac{n}{e})^{n}
$$

## n维球

$n$维球的体积公式：$\displaystyle{\frac{\pi^{\frac{n}{2}}}{\Gamma(\frac{n}{2}+1)}r^{n}}$

$n$维球的表面积公式：$\displaystyle{\frac{2\pi^{\frac{n}{2}}}{\Gamma(\frac{n}{2})}r^{n-1}=V_{n}'(r)}$

其中伽马函数 $\Gamma(z)=\int_{0}^{\infty}x^{z-1}e^{-x}\mathbb{d}x$ ，满足

 - $\Gamma(1)=1,\Gamma(z+1)=z\Gamma(z)(z>0)$
 - $\Gamma(1-z)\Gamma(z)=\frac{\pi}{\sin(\pi z)}(z\notin\mathbb{Z})$
 - $\Gamma(z)\Gamma(z+\frac{1}{2})=2^{1-2z}\sqrt{\pi}\Gamma(2z)$
 - $\Gamma(\frac{1}{2})=\sqrt{\pi}$

## KKT 条件

设有函数 $f(\mathbf{p})$，我们要求在 $g_{1}(\mathbf{p})\le0,\cdots,g_{n}(\mathbf{p})\le0,h_{1}(\mathbf{p})=\cdots=h_{m}(\mathbf{p})=0$ 的条件下求其极值，则必要条件为：

$$
\begin{cases}
&\nabla f(\mathbf{p})+\sum_{i=1}^{m}\lambda_{i}\nabla h_{i}(\mathbf{p})+\sum_{i=1}^{n}\mu_{i}\nabla g_{i}(\mathbf{p})=0\\
&h_{i}(\mathbf{p})=0\\
&\mu_{i}g_{i}(\mathbf{p})=0\\
&\mu_{i}\ge0\\
&g_{i}(\mathbf{p})\le0
\end{cases}
$$

可以看出这是拉格朗日乘因子法的推广。如果 $f$ 是凸函数（注意凸函数要求定义域是凸集，即 $g$ 和 $h$ 的限制以及 $f$ 的定义域都要是凸集），那么 KKT 条件是充要的。


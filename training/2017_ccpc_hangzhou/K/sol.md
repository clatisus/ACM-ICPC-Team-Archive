## K Master of Sequence

**题目大意**：给定 $a_{i}$ 和 $b_{i}$，每次操作可能修改某个 $a_{i}$ 或某个 $b_{i}$，也可能给出一个 $k$，询问满足 $\sum_{i=1}^{n}\lfloor\frac{t-b_{i}}{a_{i}}\rfloor\ge k$ 的最小的 $t$。

**题解**：显然二分答案，考虑对于一个 $t$ 如何快速计算左边的和式。下面为了方便，将所有的 $b_{i}$ 取反。
$$
\begin{aligned}\\
&\sum_{i=1}^{n}\lfloor\frac{t+b_{i}}{a_{i}}\rfloor\\
=&\sum_{i=1}^{n}\lfloor\frac{t\%a_{i}+b_{i}\%a_{i}}{a_{i}}\rfloor+\lfloor\frac{t}{a_{i}}\rfloor+\lfloor\frac{b_{i}}{a_{i}}\rfloor\\
=&\sum_{i=1}^{n}\lfloor\frac{t}{a_{i}}\rfloor+\sum_{i=1}^{n}\lfloor\frac{b_{i}}{a_{i}}\rfloor+\sum_{i=1}^{n}\lfloor\frac{t\%a_{i}+b_{i}\%a_{i}}{a_{i}}\rfloor
\end{aligned}
$$
注意到 $a_{i}$ 的范围很小，我们可以对每种不同的 $a_{i}$ 分别计算。和式的前两项都容易 $\mathcal{O}(1)$ 地更新和查询。第三项，显然有 $b_{i}\%a_{i}\in[a_{i}-t\%a_{i},a_{i})$ 时取 $1$，其它时候取 $0$，也就是说我们只需要维护一个后缀和即可。考虑到本题的数据范围，$\mathcal{O}(a_{i})$ 暴力更新，$\mathcal{O}(1)$ 查询更优。

时间复杂度 $\mathcal{O}(n+a^{2}_{i}+ma_{i}+qa_{i}\log ka_{i})$。
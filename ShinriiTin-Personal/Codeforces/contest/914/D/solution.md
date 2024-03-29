## [D. Bash and a Tough Math Puzzle](http://codeforces.com/contest/914/problem/D)

**题目大意：**

有一个长度为$n\le5\times10^5$的数组$a$，接下来$q\le4\times10^5$次操作，每次操作是以下两种之一：

- 询问区间 $[l,r]$ 是否可以最多只改变一个位置的数，使得区间的$gcd$等于$x$；

- 将位置$i$的数修改为$y$；

**题解：**

用线段树维护区间$gcd$，询问时二分找到最小的$i$，使得$[l,i]$的$gcd$不被$x$整除，然后尝试修改$a_i$，查询$[i+1,r]$区间的$gcd$，判断其是否能被$x$整除即可。修改则直接修改。

在线段树上二分，复杂度$O(n\log{n})$乘上求$gcd$的复杂度。
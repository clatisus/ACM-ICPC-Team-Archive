## L Mod, Xor and Everything

**题目大意**：求 $\bigoplus_{i=1}^{n}n\%i$。

**题解**：首先根号分块，设该块为 $[i,j]$。易知所求即为 $\bigoplus_{k=0}^{j-i}\lfloor\frac{n}{j}\rfloor k+n\%j$。考虑分别求结果的每一个二进制位，对于第 $u$ 位来说，答案恰为 $(\sum_{k=0}^{j-i}\lfloor\frac{\lfloor\frac{n}{j}\rfloor k+n\%j}{2^{u}}\rfloor)\&1$，这样就转化成了一个类欧几里得算法。由于对于每一段需要做 $\mathcal{O}(\log n)$ 次类欧，常数较大，因此区间较小时应当暴力。

时间复杂度 $\mathcal{O}(\sqrt{n}\log^{2} n)$。
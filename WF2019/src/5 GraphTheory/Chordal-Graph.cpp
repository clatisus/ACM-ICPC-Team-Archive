<TeX>
一些结论：

弦：连接环中不相邻的两个点的边。

弦图：一个无向图称为弦图当且仅当图中任意长度大于3的环都至少有一个弦。

单纯点：设 $N(v)$ 表示与点 $v$ 相邻的点集。一个点称为单纯点当 $\{v\} + N(v)$ 的诱导子图为一个团。

完美消除序列：这是一个序列 $\{v[i]\}$，它满足 $v[i]$ 在 $\{v[i..n]\}$ 的诱导子图中为单纯点。

弦图的判定：存在完美消除序列的图为弦图。可以用 MCS 最大势算法求出完美消除序列。

最大势算法 从 $n$ 到 $1$ 的顺序依次给点标号(标号为 $i$ 的点出现在完美消除序列的第 $i$ 个)。
设 $label[i]$ 表示第 $i$ 个点与多少个已标号的点相邻，每次选择 $label[i]$ 最大的未标号的点进行标号。

判断一个序列是否为完美消除序列： 设 $\{v_{i+1},\dots,v_n\}$ 中所有与 $v_i$ 相邻的点依次为 $v_{j1},\dots, v_{jk}$。只需判断 $v_{j1}$ 是否与 $v_{j2},\dots, v_{jk}$ 相邻即可。
弦图的最大点独立集——完美消除序列从前往后能选就选。最小团覆盖数=最大点独立集数。</TeX>
int label[10010], order[10010], seq[10010], color[10010], usable[10010];
int chordal() {
	label[0] = -5555;
	for(int i = N;i > 0;i--) {
		int t = 0;
		for(int j = 1;j <= N; j++) 
			if(!order[j] && label[j] > label[t]) t = j;
		order[t] = i; seq[i] = t;
		for(auto y: edges[t]) label[y]++;
	}
	int ans = 0;
	for(int i = N; i > 0; i--) {
		for(auto y: edges[seq[i]]) usable[color[e->y]] = i;
		int c = 1;
		while(usable[c] == i) c++;
		color[seq[i]] = c;
		ans = max(ans, c)
	}
	return ans;
}
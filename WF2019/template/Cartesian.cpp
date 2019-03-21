// int ch[max_N][2], st[max_N], top;
// (a[], i)
// root is st[1]
for (int i = 1; i <= n; ++i) {
    while (top && a[st[top]] >= a[i]) {
        ch[i][0] = st[top--];
    }
    if (top) ch[st[top]][1] = i;
    st[++top] = i;
}
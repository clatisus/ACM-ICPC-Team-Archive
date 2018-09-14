// 割点可能存在于多个点双中, 建图时对每个点双新建点, 
// 向除深度最小的点之外的所有点连边, 再从深度最小的点向其连边
// 这样原图中每个点的信息在树中对应的节点和父亲节点处维护即可
// 如果u到v的lca是新建点，则lca的父亲节点的信息也应该考虑
namespace BCC {
    const int max_N = (int) 2e5 + 21; //点开两倍
    int st[max_N], top;
    int dfn[max_N], low[max_N], cnt;
    int par[max_N], tot;
    std::vector<int> vec[max_N], bcc[max_N];
    bool cut[max_N];
    void tarjan(int u, int p) {
        st[++top] = u;
        dfn[u] = low[u] = ++cnt;
        int ch = 0;
        for (auto v : vec[u]) {
            if (v == p) continue;
            ++ch;
            if (!dfn[v]) {
                tarjan(v, u);
                low[u] = std::min(low[u], low[v]);
                if (dfn[u] <= low[v]) {
                    cut[u] = true;
                    ++tot;
                    do {
                        bcc[tot].push_back(st[top]);
                        assert(!par[st[top]]);
                        par[st[top]] = tot;
                    } while (st[top--] != v);
                    bcc[u].push_back(tot);
                    par[tot] = u;
                }
            } else if (dfn[v] < dfn[u]) {
                low[u] = std::min(low[u], dfn[v]);
            }
        }
        if (!p && ch == 1) {
            cut[u] = false;
        }
    }
};
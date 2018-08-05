#include <bits/stdc++.h>

const int max_N=2010,inf=0x7f7f7f7f;

namespace dinic{
    #define pb push_back
    struct edge{int v,c,f;};
    std::vector<edge>G;
    std::vector<int>vec[max_N+21];
    int n,s,t,cnt;
    int d[max_N+21],cur[max_N+21],q[max_N+21];
    inline bool bfs(){
        int tail=1;
        for(int i=1;i<=n;++i)d[i]=cur[i]=0;
        d[s]=1,q[1]=s;
        for(int j=1;j<=tail;++j){
            int x=q[j];
            for(auto&i:vec[x]){
                auto&e=G[i];
                if(e.c==e.f||d[e.v])continue;
                d[e.v]=d[x]+1;
                q[++tail]=e.v;
            }
        }
        return d[t];
    }
    int dfs(int x,int a){
        if(x==t||!a)return a;
        int flow=0,f;
        for(int&i=cur[x];i<vec[x].size();++i){
                auto&e=G[vec[x][i]];
                auto&re=G[vec[x][i]^1];
                if(e.c==e.f||d[e.v]!=d[x]+1)continue;
                f=dfs(e.v,std::min(a,e.c-e.f));
                if(f){
                    flow+=f,e.f+=f,re.f-=f;
                    if(!(a-=f))break;
                }
            }
        if(!flow)d[x]=0;
        return flow;
    }
    inline int max_flow(int S,int T){
        s=S,t=T;
        int flow=0;
        while(bfs())flow+=dfs(s,inf);
        return flow;
    }
    inline void add_edge(int u,int v,int c){
        if(!c)return;
        vec[u].pb(cnt++),G.pb({v,c,0});
        vec[v].pb(cnt++),G.pb({u,0,0});
    }
    inline void init(int N){
        n=N;
        for(int i=1;i<=n;++i)vec[i].clear();
        G.clear();
        cnt=0;
    }
};

#define MAXN (1010)

int n, m, tot;
std::vector<int> vec[MAXN];
bool mat[MAXN][MAXN];
int vis[MAXN];

bool check(int l) {
    int s = n + 1, t = s + 1;
    dinic::init(t);
    for (int i = 1; i <= n; ++ i) vis[i] = 0;
    for (int i = 1; i <= n; ++ i) {
        if (mat[l][i]) {
            vis[i] = 1;
            dinic::add_edge(s, i, 1);
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; ++ i) {
        if (i == l || vis[i]) continue;
        ++ cnt;
        dinic::add_edge(i, t, 1);
        for (auto v : vec[i]) {
            if (vis[v]) {
                dinic::add_edge(v, i, 1);
            }
        }
    }
    return dinic::max_flow(s, t) == cnt;
}

int ans[MAXN];

void getans() {
    for (int i = 1; i <= n; ++ i) {
        if (vis[i]) {
            ++ tot;
            for (auto j : dinic::vec[i]) {
                auto e = dinic::G[j];
                if (e.v == n + 1 || e.v == n + 2) continue;
                if (e.c == e.f) {
                    ans[i] = e.v;
                    break;
                }
            }
            if (!ans[i]) ans[i] = -1;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
        mat[u][v] = mat[v][u] = true;
    }
    for (int i = 1; i <= n; ++i) {
        if (check(i)) {
            getans();
            printf("Yes\n");
            printf("%d %d\n", i, tot);
            for (int j = 1; j <= n; ++j) {
                if (vis[j]) {
                    printf("%d %d\n", j, ans[j]);
                }
            }
            return 0;
        }
    }
    printf("No\n");
    return 0;
}

#include<bits/stdc++.h>

const int N = 100010;
typedef long long ll;

struct Trie{
    Trie *child[2];
    int value;

    Trie(){
        child[0] = child[1] = nullptr;
        value = 0;
    }
};

Trie *triepool;
int triecnt = 0;

Trie *newtrie(){
    if (!triecnt){
        triepool = new Trie [N];
        triecnt = N;
    }
    return triepool + -- triecnt;
}

Trie *getchild(Trie *p, int i){
    return p == nullptr ? nullptr : p -> child[i];
}

int getvalue(Trie *p){
    return p == nullptr ? 0 : p -> value;
}

ll a[N];
ll ans[N];

int main(){
    int n;
    scanf("%d", &n);
    Trie *root = newtrie();
    for (int i = 0; i < n; ++ i){
        scanf("%lld", &a[i]);
        Trie *p = root;
        for (int j = 60; j >= 0; -- j){
            int ch = a[i] >> j & 1;
            if (p -> child[ch] == nullptr){
                p -> child[ch] = newtrie();
            }
            ++ p -> value;
            p = p -> child[ch];
        }
        ++ p -> value;
    }
    ll now = 9;
    for (int k = 0; k < 18; ++ k){
        for (int i = 0; i < n; ++ i){
            int tot = 0;
            Trie *p = root;
            for (int j = 60; j >= 0; -- j){
                int x = a[i] >> j & 1;
                if (now >> j & 1){
                    tot += getvalue(getchild(p, x));
                    p = getchild(p, x ^ 1);
                }
                else{
                    p = getchild(p, x);
                }
            }
            ans[k] += tot;
        }
        now = now * 10 + 9;
    }
    ans[18] = 1ll * n * n;
    ll ret = 0;
    for (int i = 1; i <= 18; ++ i){
        ret += i * (ans[i] - ans[i - 1]);
    }
    printf("%lld\n", ret);
    return 0;
}

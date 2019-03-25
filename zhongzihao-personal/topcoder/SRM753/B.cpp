#include<bits/stdc++.h>

const int N = 100010;
const int moder = (int) 1e9 + 7;
const int BIT = 30;

struct trie{
    int cnt;
    trie* child[2];

    trie():cnt(0){
        for (int i = 0; i < 2; ++ i){
            child[i] = nullptr;
        }
    }
};

int getcnt(trie *p){
    return p == nullptr ? 0 : p -> cnt;
}

trie *getchild(trie *p, int sit){
    return p == nullptr ? nullptr : p -> child[sit];
}

trie *triepool;
int triecnt;

trie *newtrie(){
    if (!triecnt){
        triepool = new trie[N];
        triecnt = N;
    }
    return triepool + -- triecnt;
}

void add(trie *root, int x, int value){
    for (int i = BIT - 1; i >= 0; -- i){
        root -> cnt += value;
        int sit = x >> i & 1;
        if (root -> child[sit] == nullptr){
            root -> child[sit] = newtrie();
        }
        root = root -> child[sit];
    }
    root -> cnt += value;
}

int query(trie *root, int x){
    int max = 0;
    for (int i = BIT - 1; i >= 0; -- i){
        int sit = x >> i & 1;
        if (getcnt(getchild(root, sit ^ 1))){
            max |= (sit ^ 1) << i;
            root = getchild(root, sit ^ 1);
            continue;
        }
        max |= sit << i;
        root = getchild(root, sit);
    }
    return max;
}

class MojisBag{
public:
    int maximumXor(int Q, int base, int add, int rate){
        std::vector <int> x(N);
        std::vector <bool> exist(N);
        std::multiset <int> nowexist;
        int x0 = add;
        int insertcnt = 0;
        trie *root = newtrie();
        int sit1 = 0, sit2 = 0, ans = 0, res = 0;
        while (Q --){
            if (x0 % rate != 0){
                x[insertcnt] = x0;
                exist[insertcnt] = true;
                nowexist.insert(x0);
                ++ insertcnt;
                if (nowexist.size() < 2){
                    ans = 0;
                }
                else{
                    int tmp = query(root, x0);
                    if ((tmp ^ x0) > ans){
                        ans = tmp ^ x0;
                        sit1 = tmp, sit2 = x0;
                    }
                }
                ::add(root, x0, 1);
            }
            else{
                if (insertcnt) {
                    int sit = x0 % insertcnt;
                    if (exist[sit]) {
                        exist[sit] = false;
                        auto u = nowexist.find(x[sit]);
                        nowexist.erase(u);
                        ::add(root, x[sit], -1);
                        if (nowexist.size() < 2) {
                            ans = 0;
                            sit1 = sit2 = 0;
                        } else {
                            if (sit1 == x[sit] || sit2 == x[sit]) {
                                ans = sit1 = sit2 = 0;
                                for (auto u : nowexist) {
                                    int tmp = query(root, u);
                                    if ((tmp ^ u) > ans) {
                                        ans = tmp ^ u;
                                        sit1 = tmp, sit2 = u;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            res = (1ll * res * base + ans) % moder;
            x0 = (1ll * x0 * base + add) % moder;
        }
        return res;
    }
};

int main() {
    MojisBag m;
    printf("%d\n", m.maximumXor(10, 4747, 7, 3));
    return 0;
}

#include <bits/stdc++.h>

const int N = 500010;

char s[N];
int set[N << 1], set1[N << 1];
int fail[N << 1];
int mod[N << 1], mod1[N << 1];

void makeFail(int *p, int m){
    fail[0] = -1;
    for(int i = 1, j = -1; i <= m; ++ i){
        while(j >= 0 && p[j] != p[i - 1]) j = fail[j];
        fail[i] = ++ j;
    }
}

int searchForm(int *p, int *t, int m, int n){
    for(int i = 0, j = 0; i < n; ++ i){
        while(j >= 0 && p[j] != t[i]) j = fail[j];
        if(++ j == m){
            return i;
        }
    }
    return INT_MIN;
}

std::vector <char> solve(std::vector <int> vec){
    memset(set, 0, sizeof(set));
    memset(set1, 0, sizeof(set1));
    memset(mod, 0, sizeof(mod));
    memset(mod1, 0, sizeof(mod1));
    memset(fail, 0, sizeof(fail));
    int offset = 0, n = strlen(s);
    for (int i = 0; i < n; ++ i){
        if (s[i] == 'L'){
            -- offset;
        }
        else if (s[i] == 'R'){
            ++ offset;
        }
        else{
            set[N + offset] ^= 1;
        }
    }
    int minsit = INT_MAX, maxsit = INT_MIN;
    for (auto u : vec) {
        set1[u + N] ^= 1;
    }
    for (int i = 0; i < N << 1; ++ i){
        if (!set1[i]) continue;
        minsit = std::min(minsit, i);
        maxsit = std::max(maxsit, i);
    }
    std::vector <char> res;
    if (offset == 0){
        int cnt = 0, cnt1 = 0;
        for (int i = 0; i < N << 1; ++ i){
            cnt += set[i];
            cnt1 += set1[i];
        }
        if (cnt != cnt1){
            return {'\0'};
        }
        makeFail(set1 + minsit, maxsit - minsit + 1);
        int ret = searchForm(set1 + minsit, set, maxsit - minsit + 1, N << 1);
        if (ret == INT_MIN){
            return {'\0'};
        }
        ret -= maxsit - minsit;
        if (ret == minsit){
            return {};
        }
        else if (ret > minsit){
            for (int i = ret; i > minsit; -- i){
                res.push_back('L');
            }
        }
        else{
            for (int i = ret; i < minsit; ++ i){
                res.push_back('R');
            }
        }
        return res;
    }
    int absoffset = std::abs(offset);
    for (int i = 0; i < N << 1; ++ i){
        mod[i % absoffset] ^= set[i];
        mod1[i % absoffset] ^= set1[i];
    }
    for (int i = 0; i < absoffset; ++ i){
        mod[i + absoffset] = mod[i];
    }
    makeFail(mod1, absoffset);
    int ret = searchForm(mod1, mod, absoffset, absoffset << 1);
    if (ret == INT_MIN){
        return {'\0'};
    }
    ret -= absoffset - 1;
    for (int i = 0; i < N << 1; ++ i){
        if (set[i]){
            set1[i - ret] ^= 1;
        }
    }
    std::vector <int> ans;
    if (offset > 0) {
        for (int i = 0; i < absoffset; ++i) {
            int now = 0;
            for (int j = i; j < N << 1; j += absoffset) {
                now ^= set1[j];
                if (now) {
                    ans.push_back(j - N);
                }
            }
        }
    }
    else{
        for (int i = 0; i < absoffset; ++i) {
            int now = 0;
            for (int j = (N << 1) - 1 - i; j >= 0; j -= absoffset) {
                now ^= set1[j];
                if (now) {
                    ans.push_back(j - N);
                }
            }
        }
    }
    std::sort(ans.begin(), ans.end());
    if (ans.size() == 0){
        offset = 0;
    }
    else {
        if (ans[0] < 0) {
            for (int i = 0; i < -ans[0]; ++i) {
                res.push_back('L');
            }
        } else {
            for (int i = 0; i < ans[0]; ++i) {
                res.push_back('R');
            }
        }
        for (int i = 0, sz = ans.size(); i < sz; ++i) {
            res.push_back('X');
            if (i < sz - 1) {
                for (int j = ans[i]; j < ans[i + 1]; ++j) {
                    res.push_back('R');
                }
            }
        }
        offset = ans.back();
    }
    if (offset < -ret){
        for (int i = offset; i < -ret; ++ i){
            res.push_back('R');
        }
    }
    if (offset > -ret){
        for (int i = offset; i > -ret; -- i){
            res.push_back('L');
        }
    }
    return res;
}

bool check(std::vector <int> vec, std::vector <char> ans){
    std::map <int, int> map;
    int offset = 0;
    auto act = [&](char ch){
        if (ch == 'L'){
            -- offset;
        }
        else if (ch == 'R'){
            ++ offset;
        }
        else{
            map[offset] ^= 1;
        }
    };
    for (auto u : ans){
        act(u);
    }
    int n = strlen(s);
    for (int i = 0; i < n; ++ i){
        act(s[i]);
    }
    for (int i = (int) ans.size() - 1; i >= 0; -- i){
        char ch = ans[i];
        ch = ch == 'L' ? 'R' : ch == 'R' ? 'L' : 'X';
        act(ch);
    }
    std::map <int, int> map1;
    for (auto u : vec){
        map1[u] ^= 1;
    }
    std::vector <int> vec1, vec2;
    for (auto u : map){
        if (u.second){
            vec1.push_back(u.first);
        }
    }
    for (auto u : map1){
        if (u.second){
            vec2.push_back(u.first);
        }
    }
    return vec1 == vec2;
}

int main() {
    scanf("%s", s);
    int n;
    scanf("%d", &n);
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &vec[i]);
    }
    std::vector<char> ans = solve(vec);
    if (ans.empty()) {
        puts("LR");
    } else if (ans[0] == '\0') {
        puts("NO");
        return 0;
    } else {
        for (auto u : ans) {
            putchar(u);
        }
        puts("");
    }
    assert(check(vec, ans));
    return 0;
}

#include <bits/stdc++.h>

using namespace std;

class OneHandSort {
public:
    bool vis[1000];
    vector <int> sortShelf(vector <int> target)  {
        int n = target.size();
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (vis[i]) continue;
            vector<int> tmp;
            int u = i;
            while (!vis[u]) {
                tmp.push_back(u);
                vis[u] = true;
                u = target[u];
            }
            if (tmp.size() == 1) continue;
            int m = tmp.size();
            ans.push_back(tmp[0]);
            for (int j = m - 1; j > 0; --j) {
                ans.push_back(tmp[j]);
            }
            ans.push_back(n);
        }
        return ans;
    }
};

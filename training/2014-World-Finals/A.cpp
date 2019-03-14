#include <bits/stdc++.h>

typedef std::pair <int, int> pii;

void solve(int n, int offset){
    if (n <= 7){
        std::vector <int> begin(2 * n + 2), end(2 * n + 2);
        begin[0] = begin[1] = 2;
        for (int i = 2; i < 2 * n + 2; ++ i){
            begin[i] = (i + 1) & 1;
        }
        end[2 * n] = end[2 * n + 1] = 2;
        for (int i = 0; i < n; ++ i){
            end[i] = 0;
            end[i + n] = 1;
        }
        std::queue <std::vector <int>> queue;
        queue.push(begin);
        std::map <std::vector <int>, std::pair <pii, std::vector <int>>> map;
        map[begin] = {{-1, -1}, {}};
        std::vector <pii> option(n);
        while (!queue.empty()){
            std::vector <int> vec = queue.front();
            if (vec == end){
                break;
            }
            queue.pop();
            int empty = 0;
            for (int i = 0; i <= 2 * n; ++ i){
                if (vec[i] == 2 && vec[i + 1] == 2){
                    empty = i;
                }
            }
            for (int i = 0; i <= 2 * n; ++ i){
                if (vec[i] < 2 && vec[i + 1] < 2){
                    std::vector <int> nvec = vec;
                    std::swap(nvec[empty], nvec[i]);
                    std::swap(nvec[empty + 1], nvec[i + 1]);
                    if (!map.count(nvec)){
                        map[nvec] = {{i - 1 + offset, empty - 1 + offset}, vec};
                        queue.push(nvec);
                    }
                }
            }
        }
        assert(map.count(end));
        std::vector <pii> ans;
        while (end != begin){
            ans.push_back(map[end].first);
            end = map[end].second;
        }
        std::reverse(ans.begin(), ans.end());
        for (auto u : ans){
            printf("%d to %d\n", u.first, u.second);
        }
        return;
    }
    printf("%d to %d\n", 2 * n - 2 + offset, -1 + offset);
    printf("%d to %d\n", 3 + offset, 2 * n - 2 + offset);
    solve(n - 4, offset + 4);
    printf("%d to %d\n", 0 + offset, 2 * n - 5 + offset);
    printf("%d to %d\n", 2 * n - 1 + offset, 0 + offset);
}

int main(){
    int n;
    scanf("%d", &n);
    if (n == 3){
        puts("2 to -1\n5 to 2\n3 to -3");
        return 0;
    }
    solve(n, 0);
    return 0;
}

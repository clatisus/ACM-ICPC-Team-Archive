#include <bits/stdc++.h>

const int N = 30;

std::vector <int> e[N];
// left -> 0, right -> 1, center -> -1
char s[N];
int dir;
int low[N];
bool instack[N];

void ask(int num1, int d, int num2){
    printf("%d %s %d\n", num1, d ? "right" : "left", num2);
    fflush(stdout);
    scanf("%s", s);
    if (!strcmp(s, "treasure")){
        exit(0);
    }
    if (!strcmp(s, "left")){
        dir = 0;
    }
    else if (!strcmp(s, "right")){
        dir = 1;
    }
    else{
        dir = -1;
    }
}

int main(){
    int m;
    scanf("%d%s", &m, s);
    int u = 1, pcnt = 1;
    std::vector <int> stack = {1};
    instack[1] = true;
    while (!stack.empty()){
        if (e[u].size() == m){
            int sit = -1, min = INT_MAX;
            for (int i = 0; i < m; ++ i){
                int value;
                if (instack[e[u][i]]){
                    value = e[u][i];
                }
                else{
                    value = low[e[u][i]];
                }
                if (value < min){
                    min = value;
                    sit = i;
                }
            }
            low[u] = min;
            ask((sit + 1) % m, 0, (sit + 1) % m);
            while (dir == 0){
                ask(0, 0, 0);
            }
            sit = -1;
            stack.pop_back();
            instack[u] = false;
            for (int i = 0, sz = stack.size(); i < sz; ++ i){
                if (stack[i] == min){
                    sit = i;
                    break;
                }
            }
            for (int i = sit, sz = stack.size(); i < sz - 1; ++ i){
                ask(0, 1, 0);
            }
            u = stack.back();
            continue;
        }
        ask(1, 1, 1);
        if (dir == -1){
            ++ pcnt;
            e[u].push_back(pcnt);
            stack.push_back(pcnt);
            instack[pcnt] = true;
            u = pcnt;
            continue;
        }
        if (dir == 1){
            ask(0, 0, 0);
            int cnt = 1;
            while (dir == 1){
                ask(0, 1, 0);
                ++ cnt;
            }
            for (int i = 0; i < std::max(1, cnt - 1); ++ i){
                ask(0, 1, 0);
            }
            e[u].push_back(stack[stack.size() - cnt]);
            continue;
        }
        while (dir == 0){
            ask(0, 0, 0);
        }
        int cnt = 0;
        while (dir == 1){
            ask(0, 1, 0);
            ++ cnt;
        }
        while (dir == 0){
            ask(0, 0, 0);
        }
        for (int i = 0; i < cnt - 1; ++ i){
            ask(0, 1, 0);
        }
        e[u].push_back(stack[stack.size() - cnt]);
    }
    return 0;
}

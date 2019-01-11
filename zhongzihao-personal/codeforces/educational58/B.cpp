#include<bits/stdc++.h>

const int N = 500010;

char s[N];

int main(){
    scanf("%s", s);
    int n = strlen(s);
    int sit1 = -1, sit2 = -1, sit3 = -1, sit4 = -1;
    for (int i = 0; i < n; ++ i){
        if (s[i] == '['){
            sit1 = i;
            break;
        }
    }
    for (int i = sit1 + 1; i < n; ++ i){
        if (s[i] == ':'){
            sit2 = i;
            break;
        }
    }
    for (int i = n - 1; i >= 0; -- i){
        if (s[i] == ']'){
            sit4 = i;
            break;
        }
    }
    for (int i = sit4 - 1; i >= 0; -- i){
        if (s[i] == ':'){
            sit3 = i;
            break;
        }
    }
    if (sit1 == -1 || sit2 == -1 || sit3 == -1 || sit4 == -1 || sit2 >= sit3){
        puts("-1");
        return 0;
    }
    int len = 4;
    for (int i = sit2 + 1; i < sit3; ++ i){
        len += s[i] == '|';
    }
    printf("%d\n", len);
    return 0;
}

/*
��Ŀ���⣺����һ��ֻ��Сд��ĸ���ַ������������޸Ķ���λ�ÿ���ʹ�������Ӵ�Ϊ���Ĵ���
��⣺�ȼ�������λ����ͬ��ż��λ����ͬ���ֱ�ͳ��һ��������ĸ������࣬���ĳ����Ϳ����ˡ� 
*/
#include <bits/stdc++.h>

const int max_N = 100 + 21;

int T, n, cnt[2][26];

char s[max_N];

void testCase() {
    scanf("%s", s);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 26; ++j) {
            cnt[i][j] = 0;
        }
    n = strlen(s);
    for (int i = 0; i < n; i += 2) {
        ++cnt[0][s[i] - 'a'];
    }
    for (int i = 1; i < n; i += 2) {
        ++cnt[1][s[i] - 'a'];
    }
    int ans = n, tmp1 = 0, tmp2 = 0;
    for (int i = 0; i < 26; ++i) {
        tmp1 = std::max(tmp1, cnt[0][i]);
        tmp2 = std::max(tmp2, cnt[1][i]);
    }
    ans -= tmp1 + tmp2;
    printf("%d\n", ans);
}

int main() {
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}

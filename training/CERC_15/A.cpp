#include <bits/stdc++.h>

std::string num[10][7] = {
    {"xxxxx", "x...x", "x...x", "x...x", "x...x", "x...x", "xxxxx"},
    {"....x", "....x", "....x", "....x", "....x", "....x", "....x"},
    {"xxxxx", "....x", "....x", "xxxxx", "x....", "x....", "xxxxx"},
    {"xxxxx", "....x", "....x", "xxxxx", "....x", "....x", "xxxxx"},
    {"x...x", "x...x", "x...x", "xxxxx", "....x", "....x", "....x"},
    {"xxxxx", "x....", "x....", "xxxxx", "....x", "....x", "xxxxx"},
    {"xxxxx", "x....", "x....", "xxxxx", "x...x", "x...x", "xxxxx"},
    {"xxxxx", "....x", "....x", "....x", "....x", "....x", "....x"},
    {"xxxxx", "x...x", "x...x", "xxxxx", "x...x", "x...x", "xxxxx"},
    {"xxxxx", "x...x", "x...x", "xxxxx", "....x", "....x", "xxxxx"}
};

std::string ps[7] = {".....", "..x..", "..x..", "xxxxx", "..x..", "..x..", "....."};

int main() {

    std::string in[7];
    for (int i = 0; i < 7; ++i) {
        std::cin >> in[i];
    }
    int a = 0, b = 0, c = 0;
    int n = in[0].length();
    for (int i = 0; i < n; i += 6) {
        int d = -1;
        for (d = 0; d < 10; ++d) {
           bool flag = true;
           for (int j = 0; j < 7; ++j) {
               flag &= in[j].substr(i, 5) == num[d][j];
           }
           if (flag) break;
        }
        if (d == 10) c = 1;
        else if (c == 0) {
            a = a * 10 + d;
        } else {
            b = b * 10 + d;
        }
    }
    c = a + b;
    bool flag = false;
    std::string ans[7];
    if (c == 0) {
       for (int i = 0; i < 7; ++i) ans[i] = num[0][i];
    } else {
        while (c) {
            int d = c % 10;
            c /= 10;
            if (flag) {
                for (int i = 0; i < 7; ++i) {
                    ans[i] = "." + ans[i];
                }
            }
            flag = true;
            for (int i = 0; i < 7; ++i) {
                ans[i] = num[d][i] + ans[i];
            }
        }
    }
    for (int i = 0; i < 7; ++i) {
        std::cout << ans[i] << std::endl;
    }
    return 0;
}
/*
....x.xxxxx.xxxxx.x...x.xxxxx.xxxxx.xxxxx.......xxxxx.xxxxx.xxxxx
....x.....x.....x.x...x.x.....x.........x...x...x...x.x...x.x...x
....x.....x.....x.x...x.x.....x.........x...x...x...x.x...x.x...x
....x.xxxxx.xxxxx.xxxxx.xxxxx.xxxxx.....x.xxxxx.xxxxx.xxxxx.x...x
....x.x.........x.....x.....x.x...x.....x...x...x...x.....x.x...x
....x.x.........x.....x.....x.x...x.....x...x...x...x.....x.x...x
....x.xxxxx.xxxxx.....x.xxxxx.xxxxx.....x.......xxxxx.xxxxx.xxxxx
*/

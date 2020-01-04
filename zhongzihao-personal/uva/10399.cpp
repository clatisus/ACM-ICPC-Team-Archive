/*#include <bits/stdc++.h>

const int N = 3000010;
const int M = 3000010;

std::bitset<N> min;
int last[M];
bool success[M];
std::vector<int> prime;
FILE *fpout = fopen("result.txt", "a");

void solve(int n) {
    memset(success, 0, sizeof(success));
    memset(last, 0, sizeof(last));
    int sz = prime.size();
    for (int i = 0, j = 0; i < sz; ++i) {
        while (j < sz && prime[j] - prime[i] <= n) {
            ++j;
        }
        last[i] = j;
    }
    int lose = -1;
    for (int i = 0; i < sz; ++i) {
        if (last[i] == sz) {
            break;
        }
        if (last[i] == i + 1) {
            lose = i;
            break;
        }
        if (last[i] == last[i + 1]) {
            success[i] = true;
        }
    }
    while (lose == -1) {
        for (int i = 0; i < sz; ++i) {
            if (last[i + 1] == sz) {
                break;
            }
            if (success[i]) {
                continue;
            }
            bool flag = true;
            for (int j = last[i]; j < last[i + 1]; ++j) {
                if (!success[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                success[i] = true;
            }
        }
        for (int i = 0; i < sz; ++i) {
            if (last[i] == sz) {
                break;
            }
            bool flag = true;
            for (int j = i + 1; j < last[i]; ++j) {
                if (!success[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                //printf("fail %d\n", prime[i]);
                lose = i;
                break;
            }
        }
    }
    while (true) {
        bool flag = true;
        for (int i = lose - 1; i >= 0; --i) {
            if (prime[lose] - prime[i] > n) {
                lose = i;
                flag = false;
                break;
            }
        }
        if (flag) {
            if (prime[lose] > n) {
                lose = 0;
            } else {
                lose = prime[lose];
            }
            break;
        }
    }
    printf("ans[%d] = %d\n", n, lose);
    fprintf(fpout, "%d,\n", lose);
    fflush(stdout);
    fflush(fpout);
}

int main() {
    for (int i = 2; i < N; ++i) {
        if (!min[i]) {
            prime.push_back(i);
        }
        for (auto u : prime) {
            if (i * u >= N) break;
            min[i * u] = true;
            if (i % u == 0) break;
        }
    }
    int n;
    scanf("%d", &n);
    solve(n);
    for (int i = 828; i <= 1000; ++i) {
        solve(i);
    }
    return 0;
}*/

#include <bits/stdc++.h>

int ans[] =
    {0, 0, 0, 3, 0, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 13, 13, 3, 3, 13, 13, 13, 13, 23, 23, 23, 23, 23, 23, 13, 13, 31,
     31, 23, 23, 31, 31, 13, 13, 29, 29, 0, 43, 19, 19, 31, 31, 37, 37, 7, 7, 29, 29, 53, 53, 19, 19, 13, 13, 47, 47, 3,
     3, 61, 61, 31, 31, 67, 67, 17, 17, 13, 13, 37, 37, 31, 31, 31, 31, 2, 0, 0, 83, 79, 79, 47, 47, 19, 19, 37, 37, 83,
     83, 5, 5, 83, 83, 89, 89, 37, 37, 73, 73, 31, 31, 5, 5, 89, 89, 53, 53, 43, 43, 113, 113, 109, 109, 29, 29, 71, 71,
     109, 109, 101, 101, 53, 53, 47, 47, 47, 47, 127, 127, 103, 103, 13, 13, 97, 97, 23, 23, 131, 131, 139, 139, 109,
     109, 31, 31, 89, 89, 53, 53, 71, 71, 31, 31, 13, 13, 131, 131, 113, 113, 43, 43, 43, 43, 167, 167, 2, 0, 0, 173,
     73, 73, 139, 139, 89, 89, 67, 67, 131, 131, 181, 181, 67, 67, 37, 37, 7, 7, 181, 181, 13, 13, 113, 113, 29, 29,
     199, 199, 199, 199, 173, 173, 3, 3, 103, 103, 29, 29, 193, 193, 181, 181, 5, 5, 163, 163, 59, 59, 163, 163, 109,
     109, 5, 5, 47, 47, 181, 181, 103, 103, 23, 23, 43, 43, 211, 211, 157, 157, 241, 241, 83, 83, 43, 43, 181, 181, 179,
     179, 211, 211, 89, 89, 59, 59, 199, 199, 193, 193, 67, 67, 47, 47, 139, 139, 113, 113, 227, 227, 79, 79, 211, 211,
     13, 13, 241, 241, 173, 173, 89, 89, 83, 83, 191, 191, 281, 281, 181, 181, 271, 271, 19, 19, 211, 211, 199, 199,
     293, 293, 199, 199, 263, 263, 211, 211, 263, 263, 131, 131, 227, 227, 53, 53, 157, 157, 211, 211, 139, 139, 23, 23,
     61, 61, 79, 79, 269, 269, 107, 107, 131, 131, 211, 211, 199, 199, 199, 199, 331, 331, 331, 331, 271, 271, 241, 241,
     269, 269, 241, 241, 167, 167, 293, 293, 109, 109, 293, 293, 157, 157, 157, 157, 307, 307, 359, 359, 67, 67, 29, 29,
     149, 149, 139, 139, 31, 31, 181, 181, 139, 139, 293, 293, 233, 233, 271, 271, 73, 73, 389, 389, 389, 389, 337, 337,
     293, 293, 193, 193, 191, 191, 277, 277, 157, 157, 401, 401, 157, 157, 199, 199, 293, 293, 107, 107, 3, 3, 409, 409,
     149, 149, 199, 199, 293, 293, 317, 317, 89, 89, 17, 17, 317, 317, 193, 193, 193, 193, 167, 167, 79, 79, 389, 389,
     409, 409, 359, 359, 421, 421, 71, 71, 113, 113, 337, 337, 173, 173, 443, 443, 277, 277, 3, 3, 337, 337, 283, 283,
     53, 53, 211, 211, 227, 227, 139, 139, 467, 467, 401, 401, 113, 113, 127, 127, 113, 113, 239, 239, 409, 409, 83, 83,
     223, 223, 313, 313, 431, 431, 317, 317, 157, 157, 109, 109, 421, 421, 67, 67, 13, 13, 347, 347, 31, 31, 31, 31,
     191, 191, 277, 277, 449, 449, 443, 443, 401, 401, 173, 173, 373, 373, 409, 409, 293, 293, 317, 317, 139, 139, 137,
     137, 113, 113, 367, 367, 181, 181, 479, 479, 367, 367, 131, 131, 271, 271, 113, 113, 509, 509, 547, 547, 181, 181,
     127, 127, 263, 263, 421, 421, 73, 73, 179, 179, 277, 277, 373, 373, 73, 73, 211, 211, 317, 317, 397, 397, 263, 263,
     577, 577, 241, 241, 97, 97, 509, 509, 563, 563, 337, 337, 433, 433, 227, 227, 409, 409, 211, 211, 577, 577, 509,
     509, 601, 601, 373, 373, 167, 167, 89, 89, 353, 353, 409, 409, 73, 73, 523, 523, 251, 251, 607, 607, 521, 521, 479,
     479, 137, 137, 43, 43, 313, 313, 83, 83, 479, 479, 631, 631, 523, 523, 577, 577, 643, 643, 317, 317, 467, 467, 509,
     509, 163, 163, 71, 71, 157, 157, 331, 331, 613, 613, 631, 631, 397, 397, 449, 449, 211, 211, 647, 647, 503, 503,
     643, 643, 227, 227, 353, 353, 683, 683, 547, 547, 467, 467, 67, 67, 401, 401, 211, 211, 109, 109, 677, 677, 293,
     293, 113, 113, 613, 613, 359, 359, 449, 449, 401, 401, 509, 509, 449, 449, 467, 467, 223, 223, 131, 131, 461, 461,
     359, 359, 67, 67, 29, 29, 151, 151, 661, 661, 149, 149, 491, 491, 113, 113, 509, 509, 139, 139, 613, 613, 401, 401,
     653, 653, 109, 109, 503, 503, 29, 29, 421, 421, 461, 461, 523, 523, 479, 479, 173, 173, 157, 157, 397, 397, 733,
     733, 53, 53, 373, 373, 317, 317, 499, 499, 283, 283, 251, 251, 523, 523, 47, 47, 523, 523, 307, 307, 67, 67, 709,
     709, 349, 349, 661, 661, 743, 743, 409, 409, 389, 389, 509, 509, 617, 617, 433, 433, 313, 313, 467, 467, 53, 53,
     433, 433, 683, 683, 499, 499, 59, 59, 467, 467, 769, 769, 829, 829, 601, 601, 23, 23, 523, 523, 523, 523, 19, 19,
     661, 661, 37, 37, 163, 163, 727, 727, 653, 653, 643, 643, 719, 719, 199, 199, 661, 661, 619, 619, 661, 661, 757,
     757, 757, 757, 863, 863, 787, 787, 719, 719, 449, 449, 379, 379, 317, 317, 751, 751, 829, 829, 293, 293, 397, 397,
     631, 631, 563, 563, 31, 31, 467, 467, 313, 313, 821, 821, 887, 887, 887, 887, 241, 241, 631, 631, 829, 829, 617,
     617, 797, 797, 211, 211, 109, 109, 673, 673, 599, 599, 563, 563, 13, 13, 211, 211, 389, 389, 523, 523, 257, 257, 3,
     3, 383, 383, 509, 509, 163, 163, 353, 353, 503, 503, 683, 683, 647, 647, 199, 199, 547, 547, 109, 109, 839, 839,
     691, 691, 563, 563, 317, 317, 233, 233, 787, 787, 607, 607, 257, 257, 113, 113, 151, 151, 727, 727, 457, 457, 739,
     739, 563, 563, 523, 523, 983, 983, 563, 563, 167, 167, 53, 53, 619, 619, 421, 421, 127};

int main() {
    int test;
    scanf("%d", &test);
    while (test--) {
        int n;
        scanf("%d", &n);
        if (ans[n] == 0) {
            puts("B");
        } else {
            printf("A %d\n", ans[n]);
        }
    }
    return 0;
}
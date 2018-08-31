#include <bits/stdc++.h>

#define L (1)
#define F (2)
#define R (3)

char s[20];

bool ask(int t) {
    if (t == L) {
        puts("left");
        fflush(stdout);
        return false;
    } else if (t == R) {
        puts("right");
        fflush(stdout);
        return false;
    } else {
        puts("forward");
        fflush(stdout);
        scanf("%s", s);
        return s[0] == 'c';
    }
}

bool dig() {
    puts("dig");
    fflush(stdout);
    exit(0);
}

bool go() {
    if (ask(F)) return true;
    ask(L); ask(L); ask(F);
    if (ask(F)) return true;
    ask(L); ask(L); ask(F);
    ask(L);
    if (ask(F)) return true;
    ask(L); ask(L); ask(F);
    if (ask(F)) return true;
    ask(L); ask(L); ask(F);
    return false;
}

bool check() {
    bool ret = true;
    if (ask(F)) ret = false;
    ask(L); ask(L); ask(F);
    if (ask(F)) ret = false;
    ask(L); ask(L); ask(F);
    ask(L);
    if (ask(F)) ret = false;
    ask(L); ask(L); ask(F);
    if (ask(F)) ret = false;
    ask(L); ask(L); ask(F);
    ask(R);
    return ret;
}

int main() {
    while (go());
    int far = 0, clo = 0;
    while (true) {
        ask(F);
        if (s[0] == 'c') ++clo;
        if (s[0] == 'f') ++far;
        assert(s[0] != 's');
        if (check()) {
            if (far <= clo) dig();
            far = clo = 0;
        }
    }
    return 0;
}

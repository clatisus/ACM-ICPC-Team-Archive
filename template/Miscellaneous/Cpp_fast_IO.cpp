namespace fastIO {
#define BUF_SIZE (100000)
    bool IOerror = 0;
    inline char nc() {
        static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = p1;
        if (p1 == pend) {
            p1 = buf;
            pend = buf + fread(buf, 1, BUF_SIZE, stdin);
            if (pend == p1) {
                IOerror = 1;
                return -1;
            }
        }
        return *p1 ++;
    }

    inline bool blank(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }

    inline void read(int &x) {
        char ch;
        int f = 1;
        while (blank(ch = nc()) || ch == '-') if(ch == '-') f = -1;
        if (IOerror) return;
        for (x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0') ;
        x *= f;
    }
#undef BUF_SIZE
};

using namespace fastIO;

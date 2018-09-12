power = list()
s = list()
moder = 0
inv = list()
invcnt = list()


def eucinv(a, moder):
    b, s, t = moder, 1, 0
    while b:
        a, b, q = b, a % b, a // b
        s, t = t, s - t * q
    return s + moder if s < 0 else s


def initpower(p, e):
    global power
    power = [1] * (e + 1)
    for i in range(1, e + 1):
        power[i] = power[i - 1] * p


def inits(p, e):
    global s
    sz = min(p, e)
    s = list()
    for i in range(p + 1):
        s.append([0] * (sz + 1))
    s[0][0] = 1
    for i in range(1, p + 1):
        for j in range(1, sz + 1):
            s[i][j] = 0 if i < j else ((i - 1) * s[i - 1][j] + s[i - 1][j - 1]) % moder


def initinv(p, e):
    global inv, invcnt
    sz = max(2 * e - 2, p - 1)
    inv = [1] * (sz + 1)
    invcnt = [0] * (sz + 1)
    for i in range(1, sz + 1):
        x = i
        while x % p == 0:
            invcnt[i] += 1
            x //= p
        invcnt[i] += invcnt[i - 1]
        inv[i] = inv[i - 1] * eucinv(x, moder) % moder


def calcinter(u, v, p, e):
    ans = 0
    now = 1
    mult = u * p % moder
    for i in range(min(v, e - 1) + 1):
        ans = (ans + now * s[v + 1][i + 1]) % moder
        now = now * mult % moder
    return ans


def initpoly(p, e):
    global poly
    poly = [1] * (2 * e - 1)
    for i in range(1, 2 * e - 1):
        poly[i] = poly[i - 1] * calcinter(i - 1, p - 1, p, e) % moder * inv[p - 1] % moder


def powermod(a, exp):
    ret = 1
    while exp > 0:
        if (exp & 1) == 1:
            ret = ret * a % moder
        a = a * a % moder
        exp >>= 1
    return ret


def solve(n, p, e):
    most = e + invcnt[2 * e - 2]
    ans = 1
    cnt = 0
    while n:
        u = n // p
        v = n % p
        n = u
        cnt += u
        ans = ans * calcinter(u, v, p, e) % moder * powermod(s[p][1], u) % moder
        sz = 2 * e - 2
        if u <= sz:
            ans = ans * poly[u] % moder
            continue
        pre = list()
        suf = list()
        for i in range(sz + 1):
            pre.append([1, 0])
            suf.append([1, 0])
        for i in range(1, sz + 1):
            x = u - i + 1
            while x % p == 0 and pre[i][1] < most:
                pre[i][1] += 1
                x //= p
            pre[i][1] += pre[i - 1][1]
            pre[i][0] = pre[i - 1][0] * x % moder
        for i in range(sz - 1, -1, -1):
            x = u - i - 1
            while x % p == 0 and suf[i][1] < most:
                suf[i][1] += 1
                x //= p
            suf[i][1] += suf[i + 1][1]
            suf[i][0] = suf[i + 1][0] * x % moder
        sum = 0
        for i in range(0, sz + 1):
            ccnt = pre[i][1] + suf[i][1] - invcnt[i] - invcnt[sz - i]
            if ccnt >= e:
                continue
            tmp = power[ccnt] * pre[i][0] % moder * suf[i][0] % moder * inv[i] % moder * inv[sz - i] % moder * poly[i] % moder
            sum += tmp if (i & 1) == 0 else -tmp
            sum = (sum + moder) % moder
        ans = ans * sum % moder
    return ans, cnt


def combmod(n, m, p, e):
    global moder
    initpower(p, e)
    moder = power[e]
    inits(p, e)
    initinv(p, e)
    initpoly(p, e)
    p1 = solve(n, p, e)
    p2 = solve(m, p, e)
    p3 = solve(n - m, p, e)
    cnt = p1[1] - p2[1] - p3[1]
    if cnt >= e:
        return 0
    return p1[0] * eucinv(p2[0], moder) % moder * eucinv(p3[0], moder) % moder * power[cnt] % moder

if __name__ == '__main__':
    n = int(input())
    m = int(input())
    k = int(input())
    x1 = 2 ** k
    x2 = 5 ** k
    x3 = 10 ** k
    ans1 = combmod(n, m, 2, k)
    ans2 = combmod(n, m, 5, k)
    x3 = (ans1 * x2 * eucinv(x2, x1) + ans2 * x1 * eucinv(x1, x2)) % x3
    print(x3)

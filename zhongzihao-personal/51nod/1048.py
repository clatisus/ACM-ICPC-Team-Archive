MAX = 1010
fac = [1] * MAX
dp = [[1]]


def init():
    global fac
    for i in range(1, MAX):
        fac[i] = fac[i - 1] * i


def interpolation(vec, x):
    n = len(vec) - 1
    if x <= n:
        return vec[x]
    pre = [0] * (n + 1)
    suf = [0] * (n + 1)
    pre[0] = suf[n] = 1
    for i in range(1, n + 1):
        pre[i] = pre[i - 1] * (x - i + 1)
    for i in range(n - 1, -1, -1):
        suf[i] = suf[i + 1] * (x - i - 1)
    ans = 0
    global fac
    for i in range(0, n + 1):
        ans += (-1 if (n - i) & 1 else 1) * vec[i] * pre[i] * suf[i] // fac[i] // fac[n - i]
    return ans


if __name__ == '__main__':
    init()
    n = int(input())
    for i in range(1, 101):
        now = (n & ((1 << i) - 1)) >> (i - 1)
        tot = 0 
        dp.append([])
        for j in range(0, i + 1):
            tot += interpolation(dp[i - 1], now)
            dp[i].append(tot)
            now += 2
    print(dp[100][0])


def sum(n):
    global moder
    return n * (n + 1) * (2 * n + 1) // 6 % moder


if __name__ == '__main__':
    moder = 10 ** 9
    n = int(input())
    i = 1
    ans = 0
    cnt = 0
    while i <= n:
        cnt += 1
        if cnt % 10000 == 0:
            print(cnt)
        j = n // (n // i)
        ans = (ans + (n // i) * (sum(j) - sum(i - 1))) % moder
        i = j + 1
    print(ans)

import queue


if __name__ == '__main__':
    q = queue.Queue()
    init = (1, 1)
    q.put(init)
    ans = set()
    ans.add(init)
    init = (4, 2)
    q.put(init)
    ans.add(init)
    INF = 10 ** 30
    while not q.empty():
        u = q.get()
        x, y = 1, 0
        while x < INF and y < INF:
            ans1, ans2 = u[0] * x + 5 * u[1] * y, u[0] * y + u[1] * x
            if ans1 < INF and ans2 < INF and (ans1, ans2) not in ans:
                ans.add((ans1, ans2))
                q.put((ans1, ans2))
            ans1, ans2 = abs(u[0] * x - 5 * u[1] * y), abs(u[0] * y - u[1] * x)
            if ans1 < INF and ans2 < INF and (ans1, ans2) not in ans:
                ans.add((ans1, ans2))
                q.put((ans1, ans2))
            x, y = 9 * x + 4 * 5 * y, 9 * y + 4 * x
    ret = list()
    for x, y in ans:
        if (x - 1) % 5 == 0:
            ret.append((x - 1) // 5)
    ret.sort()
    print(ret)
    print(ret[10])
    print(ret[15])

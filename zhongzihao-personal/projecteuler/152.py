import math


def lcm(a, b):
    return a // math.gcd(a, b) * b


if __name__ == '__main__':
    ret = 1
    for i in range(2, 81):
        ret = lcm(ret, i * i)
    unable = [11, 16, 17, 19, 22, 23, 25, 26, 27, 29, 31, 32, 33, 34, 37, 38, 41, 44, 46, 47, 48, 49, 50, 51, 53, 54,
              55, 57, 58, 59, 61, 62, 64, 65, 66, 67, 68, 69, 71, 73, 74, 75, 76, 77, 78, 79, 80]
    # not_zero = []
    # moder = 26 * 26 * 23 * 23
    # for i in range(2, 81):
    #    value = ret // (i * i) % moder
    #    if value > 0:
    #        print('%d: %d' % (i, value))
    #        not_zero.append((i, value))
    # print(ret // 2)
    # if ret // 2 % moder:
    #    print('fake!!!')
    #    exit(0)
    # possible = 0
    # for i in range(1 << len(not_zero)):
    #    tot = 0
    #    for j in range(len(not_zero)):
    #        if i >> j & 1:
    #            tot += not_zero[j][1]
    #    if tot % moder == 0:
    #        possible |= i
    # unable = [11, 16, 17, 19, 22, 23, 25, 26, 27, 29, 31, 32, 33, 34, 37, 38, 41, 44, 46, 47, 48, 49, 50, 51, 53, 54,
    #          55, 57, 58, 59, 61, 62, 64, 65, 66, 67, 68, 69, 71, 73, 74, 75, 76, 77, 78, 79, 80]
    # for i in range(len(not_zero)):
    #    if not possible >> i & 1:
    #        print(not_zero[i][0])
    #        if not_zero[i][0] not in unable:
    #            unable.append(not_zero[i][0])

    # unable.sort()
    # print('unable = ' + repr(unable))
    # print(len(unable))
    able = list()
    for i in range(2, 81):
        if i not in unable:
            able.append(i)
    left = able[:len(able) // 2]
    right = able[len(able) // 2:]
    left_map = dict()
    for i in range(1 << len(left)):
        tot = 0
        for j in range(len(left)):
            if i >> j & 1:
                tot += ret // (left[j] ** 2)
        left_map.setdefault(tot, 0)
        left_map[tot] += 1

    right_map = dict()
    for i in range(1 << len(right)):
        tot = 0
        for j in range(len(right)):
            if i >> j & 1:
                tot += ret // (right[j] ** 2)
        right_map.setdefault(tot, 0)
        right_map[tot] += 1

    ans = 0
    for key, value in left_map.items():
        ans += value * right_map.get(ret // 2 - key, 0)
    print(ans)

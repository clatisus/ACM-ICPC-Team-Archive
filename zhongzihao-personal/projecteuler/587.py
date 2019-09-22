import scipy.integrate
import math


def calc(n):
    a = 1 / n ** 2 + 1
    b = -2 * (n - 1) / n ** 2
    c = ((n - 1) / n) ** 2 - 1
    x = (-b - (b ** 2 - 4 * a * c) ** 0.5) / (2 * a)
    f = lambda xx: (xx + 1) / n
    g = lambda xx: -(1 - xx ** 2) ** 0.5 + 1
    area = scipy.integrate.quad(f, -1, x)[0] + scipy.integrate.quad(g, x, 0)[0]
    tot = 1 - math.acos(-1.0) / 4
    return area / tot


if __name__ == '__main__':
    for i in range(1, 10000):
        if calc(i) < 10 ** -3:
            print(i)
            break

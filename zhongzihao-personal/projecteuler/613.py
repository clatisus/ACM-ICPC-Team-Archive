import scipy.integrate
import math


def g(value):
    return value * math.atan(value) - 0.5 * math.log(1 + value ** 2)


def f(x, y):
    value1 = (3 - y) / x
    value2 = y / (4 - x)
    global PI
    return PI * y + x * g(value1) + (4 - x) * g(value2)


def ff(x):
    return f(x, -3.0 / 4 * x + 3) - f(x, 0)


if __name__ == '__main__':
    PI = math.acos(-1.0)
    pair = scipy.integrate.quad(ff, 0, 4)
    print(pair[0] / 6 / 2 / PI)
    print(pair[1])

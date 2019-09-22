import fractions


if __name__ == '__main__':
    LEFT, RIGHT = 1, 500
    prime = [0 not in [i % j for j in range(2, i)] for i in range(RIGHT * 2)]
    prime[0] = prime[1] = False
    print(prime)
    dp = [[fractions.Fraction(0, 1) for _ in range(RIGHT * 2)] for _ in range(20)]
    string = 'PPPPNNPPPNPPNPN'
    for i in range(LEFT, RIGHT + 1):
        dp[1][i] = fractions.Fraction(1, 3) if prime[i] else fractions.Fraction(2, 3)
    for i in range(2, 16):
        for j in range(LEFT, RIGHT + 1):
            coe = fractions.Fraction(2, 3) if (string[-i] == 'P') == prime[j] else fractions.Fraction(1, 3)
            if j == LEFT:
                dp[i][j] += dp[i - 1][j + 1] * coe
            elif j == RIGHT:
                dp[i][j] += dp[i - 1][j - 1] * coe
            else:
                dp[i][j] += (dp[i - 1][j - 1] + dp[i - 1][j + 1]) * coe * fractions.Fraction(1, 2)
    ans = sum([dp[15][i] for i in range(LEFT, RIGHT + 1)]) * fractions.Fraction(1, RIGHT - LEFT + 1)
    print(ans)

import java.util.*;
import java.math.*;
 
public class Main{
    public static final int MODER = 998244353;
 
    public static int power(int a, int exp){
        int ret = 1;
        for ( ; exp > 0; exp >>= 1){
            if ((exp & 1) == 1){
                ret *= a;
            }
            a *= a;
        }
        return ret;
    }
 
    public static Vector <Integer> getFact(int n) {
        Vector <Integer> fact = new Vector<>();
        for (int i = 1; i * i <= n; ++ i) {
            if (n % i == 0) {
                fact.add(i);
                if (i * i != n) {
                    fact.add(n / i);
                }
            }
        }
        return fact;
    }
 
    public static Vector <Integer> getPrime(int n) {
        Vector <Integer> prime = new Vector<>();
        for (int i = 2; i * i <= n; ++ i) {
            if (n % i == 0) {
                while (n % i == 0) {
                    n /= i;
                }
                prime.add(i);
            }
        }
        if (n > 1) {
            prime.add(n);
        }
        return prime;
    }
 
    public static Vector <Integer> getPhi(Vector <Integer> fact, Vector <Integer> prime, int tot) {
        int n = fact.size();
        Vector <Integer> phi = new Vector<>();
        for (int i = 0; i < n; ++ i) {
            int x = tot / fact.elementAt(i);
            int tmp = 1;
            for (int u : prime) {
                int cnt = 0;
                while (x % u == 0) {
                    x /= u;
                    ++ cnt;
                }
                if (cnt > 0) {
                    tmp *= (u - 1) * power(u, cnt - 1);
                }
            }
            phi.add(tmp);
        }
        return phi;
    }
 
    public static BigInteger powermod(BigInteger a, long exp, BigInteger moder) {
        BigInteger ret = new BigInteger("1");
        for ( ; exp > 0; exp >>= 1) {
            if ((exp & 1) == 1) {
                ret = ret.multiply(a).mod(moder);
            }
            a = a.multiply(a).mod(moder);
        }
        return ret;
    }
 
    public static int gcd(int a, int b) {
        if (b == 0) {
            return a;
        }
        return gcd(b, a % b);
    }
 
    public static long lcm(int a, int b) {
        return (long) a * b / gcd(a, b);
    }
 
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt(), m = scanner.nextInt();
        Vector <Integer> fact1 = getFact(n);
        Vector <Integer> fact2 = getFact(m);
        Vector <Integer> prime1 = getPrime(n);
        Vector <Integer> prime2 = getPrime(m);
        Vector <Integer> phi1 = getPhi(fact1, prime1, n);
        Vector <Integer> phi2 = getPhi(fact2, prime2, m);
        int sz1 = fact1.size(), sz2 = fact2.size();
        BigInteger sum = new BigInteger("0");
        BigInteger mod = BigInteger.valueOf(n).multiply(BigInteger.valueOf(m)).multiply(BigInteger.valueOf(MODER));
        for (int i = 0; i < sz1; ++ i) {
            for (int j = 0; j < sz2; ++ j) {
                int u = fact1.elementAt(i), v = fact2.elementAt(j);
                BigInteger tmp = new BigInteger("1");
                tmp = tmp.multiply(BigInteger.valueOf(phi1.elementAt(i))).multiply(BigInteger.valueOf(phi2.elementAt(j))).mod(mod);
                long lcm = lcm(n / u, m / v);
                long cntv = lcm * u / n, cntu = lcm * v / m;
                assert (cntu & 1) == 1 || (cntv & 1) == 1;
                long exp;
                if ((cntu & 1) == 1 && (cntv & 1) == 1) {
                    exp = (long) n * m / lcm - u - v + 1;
                }
                else if ((cntu & 1) == 1) {
                    exp = (long) n * m / lcm - v;
                }
                else {
                    exp = (long) n * m / lcm - u;
                }
                 tmp = tmp.multiply(powermod(BigInteger.valueOf(2), exp, mod)).mod(mod);
                sum = sum.add(tmp).mod(mod);
            }
        }
        sum = sum.divide(BigInteger.valueOf(n).multiply(BigInteger.valueOf(m)));
        System.out.println(sum);
    }
}

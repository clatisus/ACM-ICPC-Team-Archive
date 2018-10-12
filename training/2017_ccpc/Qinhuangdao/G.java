import java.util.*;
import java.math.*;

public class Main {
    public static void main(String []args) {
        Scanner scan = new Scanner(System.in);
        int test = scan.nextInt();
        while ((test --) > 0) {
            BigInteger n = scan.nextBigInteger();
            BigInteger m = scan.nextBigInteger();
            BigInteger[] pow = new BigInteger[4000];
            pow[0] = new BigInteger("0");
            int sz = 0;
            for (int i = 1; i < 4000; ++ i) {
                pow[i] = pow[i - 1].shiftLeft(1).add(m);
                if (pow[i].compareTo(n) > 0) {
                    sz = i;
                    break;
                }
            }
            BigInteger ans = new BigInteger("0");
            for (int i = sz; i >= 0; -- i) {
                if (n.compareTo(pow[i]) > 0) {
                    ans = ans.or(BigInteger.ONE.shiftLeft(i));
                    BigInteger num = n.shiftRight(i);
                    if (num.compareTo(m) > 0) {
                        num = m;
                    }
                    n = n.subtract(num.shiftLeft(i));
                }
            }
            System.out.println(ans);
        }
    }
}

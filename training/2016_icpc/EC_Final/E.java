import java.util.*;
import java.math.*;
import java.lang.*;

public class Main {
    public class Fraction implements Comparable{
        public BigInteger x, y;
        
        public Fraction(BigInteger x, BigInteger y){
            this.x = x;
            this.y = y;
        }
        
        public Fraction add(Fraction f){
            BigInteger newx = x.multiply(f.y).add(y.multiply(f.x));
            BigInteger newy = y.multiply(f.y);
            return new Fraction(newx, newy);
        }
        
        public int compareTo(Object o){
            Fraction f = (Fraction) o;
            return x.multiply(f.y).compareTo(y.multiply(f.x));
        }
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int test = scan.nextInt();
        for (int Test = 1; Test <= test; ++ Test){
            int n = scan.nextInt();
            Fraction[] c = new Fraction [n];
            String tmp = scan.nextLine();
            for (int i = 0; i < n; ++ i){
                tmp = scan.nextLine();
                String[] str = tmp.split(":");
                int x1, y1;
                if (str[0].contains(".")){
                    boolean flag = false;
                    x1 = 0;
                    y1 = 1;
                    for (int j = 0; j < str[0].length(); ++ j){
                        if (str[0].charAt(j) == '.'){
                            flag = true;
                            continue;
                        }
                        x1 = x1 * 10 + str[0].charAt(j) - '0';
                        if (flag){
                            y1 *= 10;
                        }
                    }
                }
                else{
                    x1 = Integer.parseInt(str[0]);
                    y1 = 1;
                }
                int x2, y2;
                if (str[1].contains(".")){
                    boolean flag = false;
                    x2 = 0;
                    y2 = 1;
                    for (int j = 0; j < str[1].length(); ++ j){
                        if (str[1].charAt(j) == '.'){
                            flag = true;
                            continue;
                        }
                        x2 = x2 * 10 + str[1].charAt(j) - '0';
                        if (flag){
                            y2 *= 10;
                        }
                    }
                }
                else{
                    x2 = Integer.parseInt(str[1]);
                    y2 = 1;
                }
                c[i] = new Main().new Fraction(BigInteger.valueOf(1L * x1 * y2), BigInteger.valueOf(1L * x2 * y1));
                c[i].y = c[i].y.add(c[i].x);
            }
            Arrays.sort(c);
            /*for (int i = 0; i < n; ++ i){
            System.out.println(c[i].x);
            System.out.println(c[i].y);
        }*/
            Fraction sum = new Main().new Fraction(new BigInteger("0"), new BigInteger("1"));
            int ans = 0;
            for (int i = 0; i < n; ++ i){
                sum = sum.add(c[i]);
                if (sum.x.compareTo(sum.y) >= 0){
                    break;
                }
                ++ ans;
            }
            System.out.print(String.format("Case #%d: %d\n", Test, ans));
        }
        scan.close();
    }
}


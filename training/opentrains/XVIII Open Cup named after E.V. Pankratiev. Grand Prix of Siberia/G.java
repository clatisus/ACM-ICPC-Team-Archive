import java.io.*;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.StringTokenizer;
import java.util.regex.Pattern;

public class Main {
    private HashSet<String>[] set;
    private ArrayList<String>[] dp;
    private ArrayList<Pattern>[] reg;
    private final String sigma = "agtc";

    private BufferedReader inp;

    private Main() {
        set = new HashSet[16];
        dp = new ArrayList[16];
        reg = new ArrayList[16];
        for (int i = 0; i < 16; ++i) {
            set[i] = new HashSet<>();
            dp[i] = new ArrayList<>();
            reg[i] = new ArrayList<>();
        }
        inp = new BufferedReader(new InputStreamReader(System.in));
    }

    private boolean no_extra(String s) {
        return !s.contains("*") && !s.contains("|");
    }

    private void dfs(String s) {
        if (s.length() == 2 && s.charAt(0) == s.charAt(1)) return;
        if (s.length() == 3 && s.charAt(1) == s.charAt(2)) return;
        if (s.length() == 4 && (
                (s.charAt(0) == s.charAt(2) && s.charAt(1) == s.charAt(3)) ||
                        s.charAt(2) == s.charAt(3)
        )) return;
        if (s.length() == 5 && (
                (s.charAt(1) == s.charAt(3) && s.charAt(2) == s.charAt(4)) ||
                        s.charAt(3) == s.charAt(4)
        )) return;

        StringBuilder t = new StringBuilder();
        for (int i = 1; i < s.length(); ++i) t.append("(");
        t.append(s.charAt(0));
        for (int i = 1; i < s.length(); ++i) t.append(s.charAt(i)).append(")");
        set[t.length()].add(t.toString());

        if (s.length() == 5) return;
        for (int i = 0; i < 4; ++i) dfs(s + sigma.charAt(i));
    }

    private void solve() throws Throwable {
        for (int i = 0; i < 4; ++i) dfs("" + sigma.charAt(i));
        for (int i = 1; i <= 12; ++i) {
            dp[i].addAll(set[i]);
            for (int j = 1; j < i; ++j) {
                for (String u : dp[i]) {
                    for (String v : dp[j]) {
                        if (i + j + 3 <= 15) {
                            set[i + j + 3].add("(" + u + "|" + v + ")");
                        }
                        if (i + j + 2 <= 15) {
                            if (no_extra(u) && no_extra(v)) continue;
                            if (i == j + 3 && u.equals("(" + v + "*)")) continue;
                            set[i + j + 2].add("(" + u + v + ")");
                            set[i + j + 2].add("(" + v + u + ")");
                        }
                    }
                }
            }
            for (String u : dp[i]) {
                if (i >= 2 && u.charAt(i - 2) == '*') continue;
                set[i + 3].add("(" + u + "*)");
            }
            if (i + i + 2 <= 15) {
                for (String u : dp[i]) {
                    for (String v : dp[i]) {
                        if (u.equals(v)) continue;
                        if (no_extra(u) && no_extra(v)) continue;
                        set[i + i + 2].add("(" + u + v + ")");
                    }
                }
            }
            if (i + i + 3 <= 15) {
                for (int u = 0; u < dp[i].size(); ++u) {
                    for (int v = u + 1; v < dp[i].size(); ++v) {
                        set[i + i + 3].add("(" + dp[i].get(u) + "|" + dp[i].get(v) + ")");
                    }
                }
            }
        }
        for (int i = 13; i < 16; ++i) {
            dp[i].addAll(set[i]);
        }

        for (int i = 1; i < 16; ++i) {
            for (String u : dp[i]) {
                reg[i].add(Pattern.compile(u));
            }
        }

        StringTokenizer stT = new StringTokenizer(inp.readLine());
        int tests = Integer.parseInt(stT.nextToken());
        for (int tt = 0; tt < tests; ++tt) {
            StringTokenizer stN = new StringTokenizer(inp.readLine());
            int n = Integer.parseInt(stN.nextToken());

            ArrayList<String> words = new ArrayList<>();
            for (int i = 0; i < n; ++i) {
                StringTokenizer stL = new StringTokenizer(inp.readLine());
                int x = Integer.parseInt(stL.nextToken());
                if (x == 0) words.add("");
                else words.add(stL.nextToken());
            }

            boolean found = false;
            for (int i = 1; i < 16; ++i) {
                for (int j = 0; j < reg[i].size(); ++j) {
                    found = true;
                    for (String word : words) {
                        if (!reg[i].get(j).matcher(word).matches()) {
                            found = false;
                            break;
                        }
                    }
                    if (found) {
                        System.out.println(dp[i].get(j));
                        break;
                    }
                }
                if (found) break;
            }

            if (!found) {
                System.out.println("((((a|g)|t)|c)*)");
            }
        }

    }

    public static void main(String[] args) throws Throwable{
        new Main().solve();
    }

}

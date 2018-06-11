## [B. Conan and Agasa play a Card Game](http://codeforces.com/contest/914/problem/B)

**题目大意：**

Conan和Agasa玩游戏，有$n$种卡片，第$i$种卡片有$a_i$张，两人轮流操作，每次操作选择一张剩下的卡片，将它和所有数量比它少的种类的卡片都删掉，无法进行操作的人输。Conan先手，问双方都采取最优策略的情况下谁会获胜。

**题解：**

显然只要有一种卡片的数量是奇数，就是先手赢，否则后手赢。
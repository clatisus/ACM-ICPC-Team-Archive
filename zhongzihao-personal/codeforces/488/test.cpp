#include<bits/stdc++.h>

int AND(int a, int b){
    return a & b;
}

int OR(int a, int b){
    return a | b;
}

int NAND(int a, int b){
    return (a & b) ^ 1;
}

int NOR(int a, int b){
    return (a | b) ^ 1;
}

int (*func[4])(int, int) = {AND, OR, NAND, NOR};
char s[4][10] = {"AND", "OR", "NAND", "NOR"};

int main(){
    for (int x = 0; x < 4; ++ x){
        for (int y = x + 1; y < 4; ++ y){
            for (int z = 0; z < 4; ++ z){
                bool flag = true;
                for (int i = 0; i < 2; ++ i){
                    for (int j = 0; j < 2; ++ j){
                        for (int u = 0; u < 2; ++ u){
                            //for (int v = 0; v < 2; ++ v){
                                int ori = func[z](func[x](i, j), func[y](i, u));
                                int rev = 1 ^ func[z](1 ^ func[x](i, j), 1 ^ func[y](i, u));
                                if (ori == 1 && rev == 1){
                                    flag = false;
                                    break;
                                }
                            //}
                        }
                    }
                }
                if (flag){
                    printf("%s %s %s\ni j i u ori rev\n", s[z], s[x], s[y]);
                    for (int i = 0; i < 2; ++ i){
                        for (int j = 0; j < 2; ++ j){
                            for (int u = 0; u < 2; ++ u){
                                //for (int v = 0; v < 2; ++ v){
                                int ori = func[z](func[x](i, j), func[y](i, u));
                                int rev = 1 ^ func[z](1 ^ func[x](i, j), 1 ^ func[y](i, u));
                                printf("%d %d %d %d %d %d\n", i, j, i, u, ori, rev);
                                //}
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

#include <bits/stdc++.h>

int T, Ax1, Ax2, Ay1, Ay2, Bx1, Bx2, By1, By2;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d", &Ax1, &Ay1, &Ax2, &Ay2);
        scanf("%d%d%d%d", &Bx1, &By1, &Bx2, &By2);
        if (Ax1 <= Bx1 && Bx2 <= Ax2 && Ay1 <= By1 && By2 <= Ay2) {
            puts("B in A");
        } else if (Bx1 <= Ax1 && Ax2 <= Bx2 && By1 <= Ay1 && Ay2 <= By2) {
            puts("A in B");
        } else {
            int x1 = std::max(Ax1, Bx1), x2 = std::min(Ax2, Bx2);
            int y1 = std::max(Ay1, By1), y2 = std::min(Ay2, By2);
            if (x1 <= x2 && y1 <= y2) puts("Intersect");
            else puts("Separate");
        }
    }
    return 0;
}

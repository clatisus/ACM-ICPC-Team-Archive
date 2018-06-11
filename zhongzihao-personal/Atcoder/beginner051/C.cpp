#include<bits/stdc++.h>

void move(int x1, int y1, int x2, int y2){
	for (int i = 0; i < std::abs(x2 - x1); ++ i){
		if (x1 < x2){
			putchar('R');
		}
		else{
			putchar('L');
		}
	}
	for (int i = 0; i < std::abs(y2 - y1); ++ i){
		if (y1 < y2){
			putchar('U');
		}
		else{
			putchar('D');
		}
	}
}

int main(){
	int sx, sy, tx, ty;
	scanf("%d%d%d%d", &sx, &sy, &tx, &ty);
	move(sx, sy, tx, ty);
	move(tx, ty, sx, sy);
	int beginx, beginy, endx, endy;
	if (tx > sx){
		beginx = sx - 1;
		endx = tx + 1;
	}
	else{
		beginx = sx + 1;
		endx = tx - 1;
	}
	if (ty > sy){
		beginy = sy - 1;
		endy = ty + 1;
	}
	else{
		beginx = sy + 1;
		endx = ty - 1;
	}
	move(sx, sy, sx, beginy);
	move(sx, beginy, endx, ty);
	move(endx, ty, tx, ty);
	move(tx, ty, tx, endy);
	move(tx, endy, beginx, sy);
	move(beginx, sy, sx, sy);
	return 0;
}

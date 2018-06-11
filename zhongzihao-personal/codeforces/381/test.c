#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INFINITY (1000000000)
#define N (110)

typedef struct{
	int vexnum, arcnum;
	int vexs[N];
	int arcs[N][N];
} Graph;

typedef struct{
	int adjvex, lowcost;
} Edge;


Edge closedge[N];

void CreateUDN(Graph &G){ 
	int i, j, u, v, w;
	for (i = 0; i < G.vexnum; ++ i){
		for (j = 0; j < G.vexnum; ++ j){
				G.arcs[i][j] = 0;
			}
		}
	printf("������ͼ�Ķ��㣺\n");
	for (i = 0; i < G.vexnum; ++ i){
		scanf("%d", &G.vexs[i]);
	}
	printf("�����붥��v1��v2��֮���Ȩ�أ�\n");
	for (i = 0; i < G.arcnum; ++ i){
		scanf("%d%d%d", &u, &v, &w);
		G.arcs[u][v] = G.arcs[v][u] = w;
	}
}

void MiNiSpanTree_PRIM(Graph G,int u){
	int i, j, k;
	k = u;
	for(i = 0;i < G.vexnum; ++ i){
		if(i != k){
			closedge[i].adjvex = u;
        	closedge[i].lowcost = G.arcs[k][j];
		}
	}
	closedge[k].lowcost = 0;
	printf("��С�������ı�Ϊ��\n");
	for(i = 1;i < G.vexnum; ++ i){
		k = minmum(G);
		printf("%d %d\n", closedge[k].adjvex, G.vexs[k]); 
		closedge[k].lowcost = 0;
		for(j = 0; j < G.vexnum; ++ j){
		if(G.arcs[k][j] < closedge[j].lowcost){
			closedge[j].adjvex = G.vexs[k];
			closedge[j].lowcost = G.arcs[k][j];
			}
		}
	}
}
          
int minmum(Graph G){
	int min_cost = INFINITY, i;
	int temp;
	for(i = 0; i < G.vexnum; ++ i){
		if(closedge[i].lowcost < min_cost && closedge[i].lowcost != 0){
			min_cost = closedge[i].lowcost;
			temp = i;
		}
	}
	return temp;  
}

int main(){
	Graph G;
	int i, j;
	printf("�����붥������������\n");
	scanf("%d%d", &G.vexnum, &G.arcnum);
	printf("��ͼ���ڽӾ���Ϊ��\n");
	for (i = 0; i < G.vexnum; ++ i){
		for (j = 0; j < G.vexnum; ++ j){
			printf("%5d ", G.arcs[i][j]);
		}
		printf("\n");
	}
	printf("�ڽӾ��󴴽��ɹ���\n�����������ĳ����㣺\n"); 
}

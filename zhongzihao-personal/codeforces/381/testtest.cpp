#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=2010;
int n,a,b;
double p[N],u[N],q[N];
double f[N][N];int g[N][N];
#define eps 1e-9
#define nowf (f[i][j])
#define nowg (g[i][j])
int dcmp(double x)
{
    if(fabs(x)<eps)return 0;
    return ((x>0)?1:-1);
}
void up(double &f1,int &g1,double f2,int g2)
{
    if(f2>f1+eps){f1=f2;g1=g2;}
}
int get(double K)
{
    for (int i=1;i<=n;++i)
        for (int j=0;j<=a;++j)
        {
            nowf=nowg=0;
            up(nowf,nowg,f[i-1][j],g[i-1][j]);
            up(nowf,nowg,f[i-1][j]+u[i]-K,g[i-1][j]+1);
            if(j)up(nowf,nowg,f[i-1][j-1]+p[i],g[i-1][j-1]);
            if(j)up(nowf,nowg,f[i-1][j-1]+q[i]-K,g[i-1][j-1]+1);
        }
    return g[n][a];
}
int main()
{
    scanf("%d%d%d",&n,&a,&b);
    for (int i=1;i<=n;++i)scanf("%lf",p+i);
    for (int i=1;i<=n;++i)scanf("%lf",u+i);
    for (int i=1;i<=n;++i)q[i]=p[i]+u[i]-p[i]*u[i];
    double l=-1e4,mid,r=1e4;
    while(r-l>eps)
    {
        mid=(l+r)*0.5;
        if(get(mid)<b)r=mid;
        else l=mid;
    }
    printf("%lf\n",f[n][a]+l*b);
    return 0;
}

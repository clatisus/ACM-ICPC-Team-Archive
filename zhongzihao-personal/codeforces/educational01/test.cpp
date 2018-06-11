
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;
#define eps 1e-5
double x[1001],y[1001];
int n,m;
double xa,ya,xb,yb;
int seg(double xa,double ya,double xb,double yb,int p)
{
    if((x[p]-xa)*(yb-ya)-(y[p]-ya)*(xb-xa)>eps)
        return 1;
    else if((x[p]-xa)*(yb-ya)-(y[p]-ya)*(xb-xa)<-eps)
        return -1;
    else return 0;
}
double len(double xa,double ya,double xb,double yb,int p)
{
    return ((x[p]-xa)*(y[p]-y[(p+1)%n])-(x[p]-x[(p+1)%n])*(y[p]-ya))/((xb-xa)*(y[p]-y[(p+1)%n])-(x[p]-x[(p+1)%n])*(yb-ya));
}
double calc(double xa,double ya,double xb,double yb)
{
    int sign;
    double temp,t;
    priority_queue<pair<double,int>,vector<pair<double,int> >,greater<pair<double,int> > > pq;
    for(int i=0;i<n;i++)
    {
        if(seg(xa,ya,xb,yb,i)==seg(xa,ya,xb,yb,(i+1)%n))
            continue;
        pq.push(make_pair(len(xa,ya,xb,yb,i),seg(xa,ya,xb,yb,i)-seg(xa,ya,xb,yb,(i+1)%n)));
    }
    sign=0;
    temp=0;
    while(pq.size()>1)
    {
        sign+=pq.top().second;
        t=pq.top().first;
        pq.pop();
        if(sign)
            temp+=pq.top().first-t;
    }
    return temp*sqrt((xb-xa)*(xb-xa)+(yb-ya)*(yb-ya));
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
        scanf("%lf%lf",&x[i],&y[i]);
    for(int i=0;i<m;i++)
    {
        scanf("%lf%lf%lf%lf",&xa,&ya,&xb,&yb);
        printf("%lf\n",calc(xa,ya,xb,yb));
    }
    return 0;
}

#include<cstdio>
#include<algorithm>
#include<iostream>
#include<queue>
#include<cstring>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
using namespace std;
const int MAXN=1e9;

struct node
{
    int cost;
    int from;
    int to;
    int cap;
    int flow;
}edge[1010*1010];

vector<int>w[1010];
int mark[1010];
int get[1010];
int path[1010];
int pre[1010];
int step;

bool MCMF(int vstart,int vend,int &flow,int &cost)
{
    for(int ii=vstart;ii<=vend;ii++){mark[ii]=0;path[ii]=MAXN;get[ii]=MAXN;}
    queue<int>q;
    q.push(vstart);
    path[vstart]=0;
    pre[vstart]=vstart;
    while(!q.empty())
    {
        int tt=q.front();
        q.pop();
        mark[tt]=0;
        int len=w[tt].size();
        for(int ii=0;ii<len;ii++)
        {
            int son=w[tt][ii];
            node e=edge[son];
            if(e.cap>e.flow&&path[e.to]>path[tt]+e.cost)
            {
                path[e.to]=path[tt]+e.cost;
                get[e.to]=min(get[tt],e.cap-e.flow);
                pre[e.to]=son;
                if(!mark[e.to])
                {
                    q.push(e.to);
                    mark[e.to]=1;
                }
            }
        }
    }
    if(path[vend]==MAXN)return false;
    flow+=get[vend];
    cost+=path[vend]*get[vend];
    int uu=vend;
    while(uu!=vstart)
    {
        edge[pre[uu]].flow+=get[vend];
        edge[pre[uu]^1].flow-=get[vend];
        uu=edge[pre[uu]].from;
    }
    return true;
}
void add2(int ss,int ee,int cost,int many)
{
    w[ee].push_back(step);
    edge[step].from=ee;
    edge[step].to=ss;
    edge[step].cost=cost;
    edge[step].flow=0;
    edge[step++].cap=many;

    w[ss].push_back(step);
    edge[step].from=ss;
    edge[step].to=ee;
    edge[step].cost=-cost;
    edge[step].flow=0;
    edge[step++].cap=0;
}

void add1(int ss,int ee,int cost,int many,int kk)
{
    w[ss].push_back(step);
    edge[step].from=ss;
    edge[step].to=ee;
    edge[step].cost=cost;
    edge[step].flow=0;
    edge[step++].cap=many;

    w[ee].push_back(step);
    edge[step].from=ee;
    edge[step].to=ss;
    edge[step].cost=-cost;
    edge[step].flow=0;
    edge[step++].cap=0;
    if(kk==0)add2(ss,ee,cost,many);
    return ;
}

int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        memset(edge,0,sizeof(edge));
        step=0;
        for(int ii=0;ii<=n+1;ii++)w[ii].clear();
        while(m--)
        {
            int x,y,t;
            scanf("%d%d%d",&x,&y,&t);
            add1(x,y,t,1,0);
        }
        add1(0,1,0,2,1);
        add1(n,n+1,0,2,1);
        int flow=0;
        int cost=0;
        while(MCMF(0,n+1,flow,cost));
        printf("%d\n",cost);
    }
    return 0;
}

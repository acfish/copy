#include<cstring>
#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
#include<stack>
#define inf 1e9
using namespace std;

const int MAXN=31000;
struct node
{
    int num;
    int son;
};
int next[MAXN];

int pre[150100];
int cnt[150100];

int mark[MAXN];
int path[MAXN];
int cost[150100];

int spfa(int nn)
{
    for(int ii=1;ii<=nn;ii++)path[ii]=inf;
    stack<int>q;
    q.push(1);
    mark[1]=1;
    path[1]=0;
    while(!q.empty())
    {
        int ee=q.top();
        q.pop();
        mark[ee]=0;
        for(int ii=next[ee];ii!=-1;ii=pre[ii])
        {
            int va=cost[ii];
            int so=cnt[ii];
            if(path[ee]+va<path[so])
            {
                path[so]=path[ee]+va;
                if(!mark[so]){q.push(so);mark[so]=1;}
            }
        }
    }
    return path[nn];
}
int main()
{
    int m,n;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        memset(next,-1,sizeof(next));
        memset(mark,0,sizeof(mark));
        int step=0;
        for(int ii=1;ii<=m;ii++)
        {
            int x,y,tt;
            scanf("%d%d%d",&x,&y,&tt);
            cnt[step]=y;
            cost[step]=tt;
            pre[step]=next[x];
            next[x]=step++;
        }
        int ans=spfa(n);
        printf("%d\n",ans);
    }
    return 0;
}

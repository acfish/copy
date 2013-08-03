#include<cstdio>
#include<algorithm>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
struct node
{
    int sta;
    int mark;
};
vector<node>q[10010];
int pre[10010];
int len[100010];
int bridge[100010];
int ee;
int ti;
void add_edge(int xx,int yy,int id)
{
    int judge=0;
    for(int ii=0;ii<q[xx].size();ii++)
    {
        if(q[xx][ii].sta==yy)
        {
            judge=q[xx][ii].mark;
            break;
        }
    }
    if(judge!=0)len[judge]=1;
    else
    {
        node uu;
        uu.mark=id;
        uu.sta=yy;
        q[xx].push_back(uu);
        uu.sta=xx;
        q[yy].push_back(uu);
    }
    return ;
}
int tarjan(int son,int fa)
{
    int lowu=pre[son]=++ti;
    for(int ii=0;ii<q[son].size();ii++)
    {
        int rr=q[son][ii].sta;
        if(!pre[rr])
        {
            int lowv=tarjan(rr,son);
            lowu=min(lowu,lowv);
            if(lowv>pre[son]&&!len[q[son][ii].mark])
            {
                bridge[ee++]=q[son][ii].mark;
            }
        }
        else if(rr!=fa)lowu=min(pre[rr],lowu);
    }
    return lowu;
}
void init()
{
    for(int ii=1;ii<=10000;ii++)
        q[ii].clear();
}
int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        init();
        ti=0;
        ee=0;
        memset(len,0,sizeof(len));
        memset(pre,0,sizeof(pre));
         int a,b;
         scanf("%d%d",&a,&b);
         for(int ii=1;ii<=b;ii++)
         {
             int x,y;
             scanf("%d%d",&x,&y);
             add_edge(x,y,ii);
         }
         tarjan(1,-1);
         printf("%d\n",ee);
         sort(bridge,bridge+ee);
         if(ee>0)
        {
             printf("%d",bridge[0]);
             for(int ii=1;ii<ee;ii++)
             printf(" %d",bridge[ii]);
             printf("\n");
        }
        if(n!=0)printf("\n");
    }
    return 0;
}
/*
无向图求桥；
用pre数组记录他及其子树的反向树的最小祖先，如果小于自己的pre，那么就不存在桥；
对于割点，同理。
*/

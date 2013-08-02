#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> next[10100];
int mark[10100];
int fa[10100];
int ans[10100];
int sta[10100];
int ww;
int a2,b2;
void init(int nn)
{
    for(int ii=1;ii<=nn;ii++)
       {
         fa[ii]=ii;
         sta[ii]=0;
         mark[ii]=0;
         ans[ii]=0;
         next[ii].clear();
       }
    return ;
}
int find(int aa)
{
    if(fa[aa]==aa)return aa;
    fa[aa]=find(fa[aa]);
    return fa[aa];
}
void unnit(int aa,int bb)
{
    int a1=find(aa);
    int b1=find(bb);
    fa[a1]=b1;
}
void lca(int nn)
{
    ans[nn]=nn;//存在寻问（n,n）的情况，其中n为叶子节点，会跳过下面的循环，所以这个是必须的。
    for(int ii=0;ii<next[nn].size();ii++)
    {
        lca(next[nn][ii]);
        unnit(nn,next[nn][ii]);
        ans[find(next[nn][ii])]=nn;
    }
    if(ww==1)return ;
    sta[nn]=1;
    if(sta[a2]&&sta[b2])
    {
                if(nn==a2)
                printf("%d\n",ans[find(b2)]);//必须是求另外一个节点的祖先，因为是另外一个节点的祖先在不断的后退。
                else printf("%d\n",ans[find(a2)]);
                ww=1;
                return ;
    }
    return ;
}
int main()
{
    int i,j,m,n;
    scanf("%d",&n);
    while(n--)
    {
        ww=0;
        scanf("%d",&m);
        init(m);
        for(i=2;i<=m;i++)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            next[a].push_back(b);
            mark[b]=1;
        }
        scanf("%d%d",&a2,&b2);
        for(i=1;i<=m;i++)
        {
            if(!mark[i])
            {
                lca(i);
                break;
            }
        }
    }
    return 0;
}

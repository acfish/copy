#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
#include<iostream>

#define inf 1e8
#define MAX(a,b)((a)>(b)?(a):(b))
#define MIN(a,b)((a)<(b)?(a):(b))

using namespace std;
const int MAXN=510;
int get_min,S,T;
int path[MAXN];
int mark[MAXN];
int combine[MAXN];
int rela[MAXN][MAXN];
void relax(int nn)
{
    int rr=1;
    memset(mark,0,sizeof(mark));
    memset(path,0,sizeof(path));
    while(rr!=-1)
    {
        rr=-1;
        int get_max=-inf;
        for(int ii=0;ii<nn;ii++)
        {
            if(get_max<path[ii]&&!mark[ii]&&!combine[ii])
            {
                rr=ii;
                get_max=path[ii];
            }
        }

        if(rr==-1)return ;
        mark[rr]=1;
       // cout<<"rr = "<<rr<<endl;
        get_min=get_max;
        S=T;T=rr;
        for(int ii=0;ii<nn;ii++)
            if(!combine[ii]&&!mark[ii])
                path[ii]+=rela[rr][ii];
    }
    return ;
}
int find_min(int nn)
{
    int ans=inf;
    for(int ii=0;ii<nn-1;ii++)
    {
        relax(nn);
       // cout<<get_min<<endl;
        ans=min(get_min,ans);
        if(ans==0)return 0;
        combine[T]=1;
        for(int ii=0;ii<nn;ii++)
        {
            if(!combine[ii])
            {
                rela[S][ii]+=rela[T][ii];
                rela[ii][S]+=rela[ii][T];
            }
        }
    }
    return ans;
}
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        memset(combine,0,sizeof(combine));
        memset(rela,0,sizeof(rela));
        for(int ii=1;ii<=m;ii++)
        {
            int x,y,num;
            scanf("%d%d%d",&x,&y,&num);
            rela[x][y]+=num;
            rela[y][x]+=num;
        }
        int ans=find_min(n);
        printf("%d\n",ans);
    }
    return 0;
}

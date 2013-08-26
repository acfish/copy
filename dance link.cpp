#include<cstdio>
#include<iostream>
#include<cstring>
#include<climits>
using namespace std;
const int MAXN=35*35*510;
int xrow[500000];
int xcol[500000];
int h[MAXN];
int rest;
int cnt=0;
int D[MAXN],R[MAXN],L[MAXN],U[MAXN],S[35*35];
void insert_addnode(int &nn)
{
    nn++;
    R[nn]=L[nn]=U[nn]=D[nn]=nn;
    return ;
}
void insert_row(int nn,int index)
{
    R[L[nn]]=index;
    L[index]=L[nn];
    R[index]=nn;
    L[nn]=index;
}
void insert_col(int nn,int index)
{
    U[index]=U[nn];
    D[U[nn]]=index;
    D[index]=nn;
    U[nn]=index;
}
void init(int nn)
{
    cnt=-1;
    memset(S,0,sizeof(S));
    memset(h,-1,sizeof(h));
    insert_addnode(cnt);
    for(int ii=1;ii<=nn;ii++){insert_addnode(cnt);insert_row(0,cnt);}
    return ;
}
inline void remove(int nn)
{
    R[L[nn]]=R[nn];
    L[R[nn]]=L[nn];
    for(int ii=D[nn];ii!=nn;ii=D[ii])
    {
        for(int jj=R[ii];jj!=ii;jj=R[jj])//为什么没有删除到ii呢，ii要保留，因为恢复需要，并且，由于在列的最顶
//该列删除，对于下一次迭代，只需考虑其他列的行，而这其中，肯定都被删除了。
        {
            U[D[jj]]=U[jj];
            D[U[jj]]=D[jj];
            S[xcol[jj]]--;
         }
    }
    return ;
}

inline void resume(int nn)
{
    for(int ii=U[nn];ii!=nn;ii=U[ii])
    {
        for(int jj=L[ii];jj!=ii;jj=L[jj])
        {
            U[D[jj]]=jj;
            D[U[jj]]=jj;
            S[xcol[jj]]++;
        }
    }
    R[L[nn]]=nn;
    L[R[nn]]=nn;
    return ;
}


void dfs(int deep)
{
    if(rest<=deep)return ;
    if(R[0]==0)
    {
        rest=deep;
        return ;
    }
    int get_min=INT_MAX;
    int mark;
    for(int ii=R[0];ii;ii=R[ii])
    {
        if(S[ii]<get_min)
        {
            mark=ii;
            get_min=S[ii];
        }
    }
    //if(get_min==0)return ;
    remove(mark);
    for(int ii=D[mark];ii!=mark;ii=D[ii])
    {
        for(int jj=R[ii];jj!=ii;jj=R[jj])remove(xcol[jj]);
        dfs(deep+1);
        for(int jj=L[ii];jj!=ii;jj=L[jj])resume(xcol[jj]);
        //删除的顺序要相反，不然得不到原来的顺序。
    }
    resume(mark);
    return ;
}
void insert_node(int xx,int yy)
{
    S[yy]++;
    insert_addnode(cnt);
    xcol[cnt]=yy;
    xrow[cnt]=xx;
    insert_col(yy,cnt);
    if(h[xx]==-1)h[xx]=cnt;
    else insert_row(h[xx],cnt);
}

int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        int x,y,m;
        scanf("%d%d%d",&x,&y,&m);
        init(x*y);
        for(int ii=1;ii<=m;ii++)
        {
            int x1,y1,x2,y2;
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            for(int kk=x1+1;kk<=x2;kk++)
            {
                for(int jj=y1+1;jj<=y2;jj++)
                {
                    int aim=y*(kk-1)+jj;
                    insert_node(ii,aim);
                }
            }
        }
       /* int ee=0;
        for(int ii=1;ii<=x*y;ii++)
        {
            if(S[ii]<=0)
            {
                ee=1;
                break;
            }
        }
        if(ee==1){printf("-1\n");continue;};*/
        rest=INT_MAX;
        dfs(0);
        if(rest==INT_MAX)printf("-1\n");
        else printf("%d\n",rest);
    }
    return 0;
}

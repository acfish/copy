#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<iostream>
using namespace std;

const int MAXN=1e8;
char s[120][120];
struct node
{
    int xx;
    int yy;
}mm[120],hh[120];
int m,n,link[120],vx[120],vy[120],lx[120],ly[120],get_min[120],value[120][120];
int h1,m1;
void get_scanf()
{
    m1=0;
    h1=0;
    for(int ii=0;ii<m;ii++)
    scanf("%s",s[ii]);
    for(int ii=0;ii<m;ii++)
    {
        for(int jj=0;jj<n;jj++)
        {
            if(s[ii][jj]=='m')
             {
                 mm[m1].xx=ii;
                 mm[m1++].yy=jj;
             }
             else if(s[ii][jj]=='H')
             {
                 hh[h1].xx=ii;
                 hh[h1++].yy=jj;
             }
        }
    }
    for(int ii=0;ii<m1;ii++)
        for(int jj=0;jj<h1;jj++)
                value[ii][jj]=-1*(abs(mm[ii].xx-hh[jj].xx)+abs(mm[ii].yy-hh[jj].yy));
    return ;
}
bool find(int nn)
{
   vx[nn]=1;
   for(int ii=0;ii<h1;ii++)
   {
       if(vy[ii]==-1)
       {

           int left=lx[nn]+ly[ii]-value[nn][ii];
           if(left==0)//先要找到相等子图才能再判断增广路
           {
             vy[ii]=1;//S,T必须是在相等子图中的匹配失败的两个集合
             if(link[ii]==-1||find(link[ii]))
             {
               link[ii]=nn;
               return true;
             }
           }
           else
           get_min[ii]=min(get_min[ii],left);
       }
   }
   return false;
}
int KM()
{
    int ans=0;
    for(int ii=0;ii<m1;ii++)
    lx[ii]=-MAXN;
    for(int ii=0;ii<m1;ii++)
        for(int jj=0;jj<h1;jj++)
           lx[ii]=max(lx[ii],value[ii][jj]);
    memset(ly,0,sizeof(ly));
    memset(link,-1,sizeof(link));
    for(int jj=0;jj<m1;jj++)
    {
        while(1)
        {
            memset(vy,-1,sizeof(vy));
            memset(vx,-1,sizeof(vx));
            for(int ii=0;ii<h1;ii++)get_min[ii]=MAXN;
            if(find(jj))break;
            int get_ans=MAXN;
            for(int ii=0;ii<h1;ii++)
                if(vy[ii]==-1)
                    get_ans=min(get_ans,get_min[ii]);
            for(int ii=0;ii<m1;ii++)
                if(vx[ii]!=-1)
                lx[ii]-=get_ans;
            for(int ii=0;ii<h1;ii++)
                if(vy[ii]!=-1)
                ly[ii]+=get_ans;
        }
    }
    for(int ii=0;ii<h1;ii++)
    if(link[ii]!=-1)
    ans+=value[link[ii]][ii];
    return ans;
}
int main()
{
    while(scanf("%d%d",&m,&n),m||n)
    {
        get_scanf();
        printf("%d\n",-1*KM());
    }
    return 0;
}

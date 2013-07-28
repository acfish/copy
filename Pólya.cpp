#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int gcd(int aa,int bb)
{
    int tt;
    while(bb)
    {
        tt=bb;
        bb=aa%bb;
        aa=tt;
    }
    return aa;
}
int poww(int nn,int mm)
{
    __int64 num=1;
    for(int ii=1;ii<=mm;ii++)
        num*=nn;
    return num;
}
int main()
{
    int i,j,m,n;
    while(scanf("%d%d",&n,&m),m||n)
    {
        __int64 nu=0;
        __int64 sum=0;
        for(i=1;i<=m;i++)
        {
           int u=gcd(m,i);
          // cout<<u<<endl;
            sum+=poww(n,u);
        }//旋转的情况，其中的循环节的个数为gcd（长度，移动的位置），移动的位置从1开始
        nu+=m;
        if(m%2)
        {
            int u=m/2+1;
            sum+=m*poww(n,u);
            nu+=m;
        }
        else
        {
            int u=m/2+1;
            sum+=(m/2)*poww(n,u);
            u=m/2;
            sum+=u*poww(n,u);
            nu+=m;
        }
        printf("%I64d\n",sum/nu);
    }
    return 0;
}
/*
其中，先考旋转的情况，用gcd（L，i）来求出每个循环分裂的循环个数；（其中，这个方法与求T^k的方法差不多，T为循环）；
然后，求出翻转的情况，反转分为两种：
1.给的总位置数为奇数，那么反转只能为从其中的一个位置折叠，总共分裂为n/2+1个循环，其中有n/2个长度为2的循环，和一个
长度为1的循环。
2.给的总位置个数为偶数，那么反转有两种情况；a.从某两个位置中间折叠和恰好从两个位置上折叠。个数分别为n/2,n/2+1.
所以总的结果为(1/|K|)*(m^(循环个数)+....).（其中m为颜色的个数）。
*/
/*
m个点，n种颜色
L=(1/|G|)*(n^（c(g1)）+n^(c(g2))...+..)
其中G={g1 ,...gs}
c(gi )为置换gi的循环节数(i=1...s)
*/

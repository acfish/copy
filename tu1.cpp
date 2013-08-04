#include<cstdio>
#include<cstring>
#include<iostream>
#include<map>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
struct node
{
    int xx;
    int yy;
};
vector<node>man;
vector<node>house;
const int MAXN=120;
const int INT_MAX=1e8;
const int INT_MIN=0;
char s[120][120];
bool bimap[MAXN][MAXN];
bool tx[MAXN],ty[MAXN];
int lx[MAXN],ly[MAXN];
int match[MAXN];
int w[MAXN][MAXN],n;
bool dfs(int pos)
{
    int i;
    for(i=0;i<n;i++){
        if(!ty[i]&&bimap[pos][i]){ty[i]=true;int pre=match[i];match[i]=pos;
        if(pre==-1||dfs(pre))return true;match[i]=pre;
        if(match[i]!=-1)tx[match[i]]=true;}}
        return false;}

int KM_Perfect_Match()
{int i,j;
    for(i=0;i<n;i++){lx[i]=INT_MIN;ly[i]=0;
    for(j=0;j<n;j++)lx[i]=max(lx[i],w[i][j]);}
    bool perfect=false;
    while(!perfect){
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(lx[i]+ly[j]==w[i][j])bimap[i][j]=true;
                else bimap[i][j]=false;}}
        int max_match=0;memset(match,-1,sizeof(match));
        for(i=0;i<n;i++){
            memset(tx,false,sizeof(tx));memset(ty,false,sizeof(ty));
            if(dfs(i))max_match++;
            else {tx[i]=true;break;}}
            if(max_match==n)perfect=true;
            else {
                int ex=INT_MAX;
                for(i=0;i<n;i++){
                    for(j=0;tx[i]&&j<n;j++){
                        if(!ty[j])ex=min(ex,lx[i]+ly[j]-w[i][j]);}}
                for(i=0;i<n;i++){
                    if(tx[i])lx[i]-=ex;
                    if(ty[i])ly[i]+=ex;}}}
                    int cost=0;
                    for(i=0;i<n;i++){cost+=w[match[i]][i];}return cost;}

int main()
{
    int nn,mm;
    while(scanf("%d%d",&mm,&nn),mm||nn)
    {
        house.clear();
        man.clear();
        for(int ii=0;ii<mm;ii++)
            scanf("%s",s[ii]);
        for(int ii=0;ii<mm;ii++)
        {
            for(int jj=0;jj<nn;jj++)
            {
                if(s[ii][jj]=='m')
                {
                    node uu;
                    uu.xx=ii;
                    uu.yy=jj;
                    man.push_back(uu);
                }
                else if(s[ii][jj]=='H')
                {
                    node uu;
                    uu.xx=ii;
                    uu.yy=jj;
                    house.push_back(uu);
                }
            }
        }
        for(int ii=0;ii<man.size();ii++)
        {
            for(int jj=0;jj<house.size();jj++)
            {
                w[ii][jj]=-abs(man[ii].xx-house[jj].xx)-abs(man[ii].yy-house[jj].yy);
                bimap[ii][jj]=1;
            }
        }
        n=man.size();
        int ans=KM_Perfect_Match();
        printf("%d\n",-ans);
    }
    return 0;
}

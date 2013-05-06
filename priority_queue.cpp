#include<queue>
#include<functional>
#include<vector>
#include<iostream>
#include<cstdio>
using namespace std;
struct cmp
{
    bool operator()(int &a,int &b)
    {
        return a<b;
    }
};
int main()
{
    int i,j,m,n;
    priority_queue<int,vector<int>,cmp> q;
    return 0;
}


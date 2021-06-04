#include <iostream>
#include <queue>

using namespace std;


int v[100]={1,3,2,5,2,1,-1,-5,3},p,n=8;
queue <int> myq;

void solve()
{
    p=1;
    for(i=0;i<n;i++)
        if(v[i]>1)
        {
            p*=v[i];
            myq.push(v[i]);
        }
    while(!myq.empty())
    {
        cout<<myq.pop();
    }
    cout<<p<<" ";
}

int main()
{
    return 0;
}
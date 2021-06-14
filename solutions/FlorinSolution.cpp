#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

char m[1000][1000],v[1000];
int n;
bool gasit=false;
ifstream f("inf.txt");
ofstream g("outf.txt");

void citire()
{
    int i,j;
    f>>n;
    for(i=0;i<n*n;i++)
        f>>v[i];
    for(i=0;i<n*n;i++)
        for(j=0;j<n*n;j++)
            f>>m[i][j];
}

void afisare()
{
    int i,j;
    for(i=0;i<n*n;i++)
    {
        for(j=0;j<n*n;j++)
            g<<m[i][j]<<" ";
        g<<endl;
    }
   g<<endl;
}


bool verif(int i,int j)
{
    int i2,j2;
    for(i2=(i/n)*n;i2<(i/n)*n+n;i2++)
        for(j2=(j/n)*n;j2<(j/n)*n+n;j2++)
            if(m[i][j]==m[i2][j2]&&i!=i2&&j!=j2)
                return false;
    for(i2=0;i2<n*n;i2++)
        if(m[i][j]==m[i2][j]&&i!=i2)
            return false;
    for(j2=0;j2<n*n;j2++)
        if(m[i][j]==m[i][j2]&&j!=j2)
            return false;  
    return true;     
}



void back(int i,int j,int k,int l)
{
    if(m[k][l]=='0')
    {
        if(gasit==true)
            return;
        for(int x=0;x<n*n;x++)
        {
            m[k][l]=v[x];
            if(verif(k,l))
            {
                
                if(l+1>=j*n+n)
                {  
                    if(k+1>=i*n+n)
                    {
                        if(j+1>=n)
                        {
                            if(i+1>=n)
                            {
                                gasit==true;
                                afisare();
                                return;
                            }
                            else
                                back(i+1,0,i*n+n,0);
                        }
                        else
                            back(i,j+1,i*n,j*n+n);
                    }
                    else
                        back(i,j,k+1,j*n);
                }
                else
                    back(i,j,k,l+1);
            }
            m[k][l]='0';
        }
    }
    else
    {
        if(l+1>=j*n+n)
        {  
            if(k+1>=i*n+n)
            {
                if(j+1>=n)
                {
                    if(i+1>=n)
                    {
                        gasit==true;
                        afisare();
                        return;
                    }
                    else
                        back(i+1,0,i*n+n,0);
                }
                else
                    back(i,j+1,i*n,j*n+n);
            }
            else
                back(i,j,k+1,j*n);
        }
        else
            back(i,j,k,l+1);
    }
}

int main()
{
    citire();
    clock_t start, end;
    start= clock();
    back(0,0,0,0);
    end=clock();
    cout<<fixed<<double(end - start) / double(CLOCKS_PER_SEC);
    return 0;
}
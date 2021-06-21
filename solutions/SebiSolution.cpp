#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
char t[10][10],c[100];
int n,poz[2][100],npoz;


ifstream f("inWordoku.txt");
ofstream g("outWordoku.txt");
ofstream g2("timeWordoku.txt");

void citire()  //se citeste n
{   int i,j;
    f>>n;
    for(i=1;i<=n*n;i++) //se citesc cele n litere la dispozitie
        f>>c[i];
    for(i=1; i<=n*n; i++) //se citeste tabela initiala
        for(j=1; j<=n*n; j++)
            f>>t[i][j];
}
void afisare()  //se afiseaza tabela
{
    int i,j;
    for(i=1; i<=n*n; i++)
    {
        for(j=1; j<=n*n; j++)
        {
            g<<t[i][j]<<" ";
            if(j%3==0 && j<n*n) g<<"| ";
        }
        g<<endl;
        if(i%3==0 && i<9) g<<"------+-------+------"<<endl;
    }
    g<<endl;
}
void zpoz() //functia salveaza in matricea poz pozitiile tuturor spatiilor goale din tabela,in care se poate scrie,reprezentate prin 0
{   for(int i=1; i<=n*n; i++)
        for(int j=1; j<=n*n; j++)
            if(t[i][j]=='0') //daca se gaseste un spatiu gol
            {   npoz++; //se creste numarul de spatii goale
                poz[1][npoz]=i;   //pe linia 1 se scrie linia pe care a fost gasit elementul
                poz[2][npoz]=j; //pe linia 2 se scrie coloana pe care a fost gasit elementul
            }
}
int scan(int x,int y,int z) //functia scan returneaza 1 daca o litera c[z](a z a litera din cele n litere date la inceput) poate fii scrisa in spatiul d dat de coordonatele x,y , x fiind linia si y coloana, si returneaza 0 in caz contrar
{
    int i,j;
    for(i=1; i<=n*n; i++) //se verifica daca o litera asemenea este gasita pe linia spatiului sau coloana spatiului
        if(t[x][i]==c[z] || t[i][y]==c[z]) return 0;
    int a=((x-1)/3*3+1),b=((y-1)/3*3+1); //a si b memoreaza linia si coloana spatiului din stanga sus al unei mini-tabele de 3x3 din care face parte spatiul
    for(i=a; i<=a+2; i++) //folosind a si b ca punct de plecare se parcurge mini tabela de 3x3 pentru a se verifica daca exista o litera asemenea in aceasta
    {
        for(j=b; j<=b+2; j++)
            if(t[i][j]==c[z]) return 0;
    }
    return 1; //daca sunt indeplinite conditiile se returneaza 1
}
void backtracking(int x)
{
    for(int i=1; i<=9; i++) //se parcurg cele 9 litere pentru fiecare spatiu
    {
        if(scan(poz[1][x],poz[2][x],i)==1) //daca litera curenta c[i] se poate scrie in acel spatiu,este scrisa
        {   t[poz[1][x]][poz[2][x]]=c[i];
            if(x==npoz) //daca se completeaza ultimul spatiu gol,inseamna ca tabela este completa si se afiseaza
            {
                afisare();
                return;
            }
            else
            {
                backtracking(x+1);  //daca nu s-a ajuns la finalul tabelei,algoritmul continua
            }
        }
        t[poz[1][x]][poz[2][x]]='0'; //fiecare spatiu gol modificat,la intoarcerea algoritmului,devine 0
    }

}
int main()
{
    citire();
    //afisare();
    zpoz();
    //backtracking(1);
    clock_t start, end;
    start= clock();
    backtracking(1);
    end=clock();
    g2<<fixed<<double(end - start) / double(CLOCKS_PER_SEC);
    return 0;
}

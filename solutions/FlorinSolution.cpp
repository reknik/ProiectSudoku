#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

char m[1000][1000],v[1000];
int n;
bool gasit=false;
ifstream f("inWordoku.txt");
ofstream g("outWordoku.txt");
ofstream g2("timeWordoku.txt");

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


/*
    Functia 'verif' foloseste 2 parametrii:
    - 'i' este indicele randului casutei curente
    - 'j' este indicele coloanei casutei curente
*/

bool verif(int i,int j)
{
    int i2,j2;
    //se verifica daca nu exista un duplicat in chenarul curent
    for(i2=(i/n)*n;i2<(i/n)*n+n;i2++)
        for(j2=(j/n)*n;j2<(j/n)*n+n;j2++)
            if(m[i][j]==m[i2][j2]&&i!=i2&&j!=j2)
                return false;
    //se verifica daca nu exista duplicat pe coloana
    for(i2=0;i2<n*n;i2++)
        if(m[i][j]==m[i2][j]&&i!=i2)
            return false;
    //se verifica daca nu exista duplicat pe rand
    for(j2=0;j2<n*n;j2++)
        if(m[i][j]==m[i][j2]&&j!=j2)
            return false;
    return true;
}


/*
    Functia 'back' foloseste 4 parametrii:
    - 'i' este indicele randului(de chenare) pe care se afla chenarul
    - 'j' este indicele coloanei(de chenare) pe care se afla chenarul
    - 'k' este indicele de rand pentru casuta curenta
    - 'l' este indicele de coloana pentru casuta curenta
*/
void back(int i,int j,int k,int l)
{
    if(gasit==true) //daca o solutie a fost deja gasita functia se intoarce
            return;
    if(m[k][l]=='0') //verificare daca casuta de la indicele curent este goala
    {
        for(int x=0;x<n*n;x++) //parcurgerea vectorului cu litere posibile
        {
            m[k][l]=v[x]; //atribuire casuta curenta cu valoarea de pe pozitia x din vectorul de litere
            if(verif(k,l)) //verificare daca se respecta conditiile
            {
                if(l+1>=j*n+n) //verificare daca indicele de coloana iese in afara chenarului curent
                {
                    if(k+1>=i*n+n) //verificare daca indicele de rand iese in afara chenarului curent
                    {
                        if(j+1>=n) //verificare daca indicele coloanei(de chenare) depaseste matricea
                        {
                            if(i+1>=n) //verificare daca indicele randului(de chenare) depaseste matricea
                            {
                                gasit=true;
                                afisare();
                                return;
                            }
                            else
                                back(i+1,0,i*n+n,0); //se creste indicele randului(de chenar) si se reseateaza ceilalti indici.
                        }
                        else
                            back(i,j+1,i*n,j*n+n); //se creste indicele coloanei(de chenar) si se reseteaza indicele de rand si coloana
                    }
                    else
                        back(i,j,k+1,j*n); //se creste indicele de rand si se reseteaza indicele de coloana
                }
                else
                    back(i,j,k,l+1); //se creste indicele de coloana si se trece la urmatoarea casuta
            }
            m[k][l]='0'; //la final se reseteaza casuta modificata
        }
    }
    else //daca casuta nu este goala se trece de etapa de verificare
    {
        if(l+1>=j*n+n)
        {
            if(k+1>=i*n+n)
            {
                if(j+1>=n)
                {
                    if(i+1>=n)
                    {

                        gasit=true;
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
    clock_t start, end; //Initializare cronometru
    start= clock(); //Start cronometru
    back(0,0,0,0); //Apel functie backtracking
    end=clock(); //Stop cronometru
    g2<<fixed<<double(end - start) / double(CLOCKS_PER_SEC); //Afisare timp executie in milisecunde
    if(gasit==false)
    {
        g<<"Nu exista solutie";
    }
    return 0;
}

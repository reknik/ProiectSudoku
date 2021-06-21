#include <iostream>
#include <fstream>
using namespace std;

int matriceID[11][11], sumaGrupe[50]; //matriceID este folosita pentru a retine ID-ul fiecarei patretele de joc. cu ajutorul
//ID-ului voi identifica grupa de celule din care face parte. sumaGrupe este folosita pentru a memora suma fiecarei grupe de celule
int solutieInitiala[11][11] = {0};                                     //in solutieInitiala voi memora casutele in care se gasesc valori default
int solutie[11][11] = {0};                                             //in solutie voi memora tabla de joc
int numarGrupe;                                                        //numarGrupe este o variabila folosita pentru a numara grupele de celule a caror suma trebuie sa o calculam
int vectorFrecventaInitial[50] = {0}, vectorFrecventaCurent[50] = {0}; //vectirFrecventaInitial este folosit pentru a calcula cate
//celule avem in fiecare grupa, iar in vectorFrecventaCurent vom itera cu 1 de fiecare data cand gasim valoarea corecta dintr-o casuta

ifstream f("killerdataVlad.in"); //fisierul care contine date de intrare
ofstream g("killerSudoku.out");  //fisierul care contine date de iesire

void initializare() //functia prin care sunt citite datele de intrare
{
    int i, j, aux;
    while (f >> i >> j)       //se citeste cate un indice i, pentru rand, si j, pentru coloana
        if (i > -1 && j > -1) //cat timp indicii pot fi folositi pentru a construi o matrice
        {
            f >> solutie[i][j];        //se citestc valorile default
            solutieInitiala[i][j] = 1; //si in solutieInitiala se marcheaza faptul ca acea valoare este default si nu trebuie schimbata prin backtracking
        }
        else
            break;
    f >> numarGrupe; //se citeste numarul de grupe de celule

    for (int k = 1; k <= numarGrupe; k++)
    {
        f >> sumaGrupe[k];              //pentru fiecare grupa de celule citim suma ei
        f >> vectorFrecventaInitial[k]; //si numarul de elemente din grupa
        for (int l = 1; l <= vectorFrecventaInitial[k]; l++)
        {
            f >> i >> j;         //iar pentru fiecare celula din grupa citim pozitia din matrice
            matriceID[i][j] = k; //si atribuim in matriceID id-ul.
        }
    }
}

void afisare() //functia de afisare a solutiei
{
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
            g << solutie[i][j] << " ";
        g << endl;
    }
}

bool folositInRand(int rand, int coloana, int numarVerificat) //functia folosita pentru a verifica daca un numar este folosit in rand
{
    bool aux = false;
    for (int j = 1; j <= 9; j++)
    {
        if (solutie[rand][j] == numarVerificat && j != coloana) //se elimina din verificare cazul in care comparam celula cu ea insasi
        {
            aux = true;
        }
    }
    return aux;
}
bool folositInColoana(int rand, int coloana, int numarVerificat) //functia folosita pentru a verifica daca un numar este folosit in coloana
{
    bool aux = false;
    for (int i = 1; i <= 9; i++)
    {
        if (solutie[i][coloana] == numarVerificat && i != rand) //se elimina din verificare cazul in care comparam celula cu ea insasi
            aux = true;
    }
    return aux;
}

bool folositInChenar(int rand, int coloana, int xChenar, int yChenar, int numarVerificat) //functia folosita pentru a verifica daca un numar  este folosit in chenarul
// de 3x3
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (solutie[i + xChenar][j + yChenar] == numarVerificat && rand != i + xChenar && coloana != j + yChenar) //se elimina din verificare cazul in care comparam celula cu ea insasi
                return true;
        }
    }
    return false;
}

bool verifica(int rand, int coloana, int numarVerificat) //functia apelata in backtracking pentru a verifica daca un numar poate fi plasat intr-o anumita celula
{
    bool aux = !folositInRand(rand, coloana, numarVerificat);                                                                            //se verifica daca numarul este folosit in rand
    bool aux2 = !folositInColoana(rand, coloana, numarVerificat);                                                                        //se verifica daca numarul este folosit in coloana
    bool aux3 = !folositInChenar(rand, coloana, (rand - 1) - (rand - 1) % 3 + 1, (coloana - 1) - (coloana - 1) % 3 + 1, numarVerificat); //se verifica daca numarul
    // este folosit in chenarul de 3x3
    return aux && aux2 && aux3; //si se unesc solutiile
}

int calculareSumaPartiala(int id) //se calculeaza suma partiala a grupului de celule cu id-ul dat ca indice
{
    int suma = 0;
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
            if (matriceID[i][j] == id)
            {
                suma = suma + solutie[i][j];
            }
    }
    return suma;
}

bool verificareSuma() //se verifica daca sumele obtinute prin umplerea celulelor corespund celor introduse ca si date de intrare
{
    bool verificaSuma = true;
    int i = 1;
    while (i <= numarGrupe && verificaSuma == true)
    {
        if (calculareSumaPartiala(i) != sumaGrupe[i])
            verificaSuma = false;
        else
            i++;
    }
    return verificaSuma;
}

bool valoareLibera(int i, int j) //se verifica daca valoarea din casuta cu coordonatele i si j mai poate fi incrementata astfel incat ea sa fie maxim 9
{
    if (solutie[i][j] < 9)
    {
        return true;
    }
    else
        return false;
}

void backtracking(int linie, int coloana) //functia de backtracking
{
    if (linie == 9 && coloana == 10 && verificareSuma() == true) //se verifica daca am ajuns la finalul matricii solutie
    {
        afisare(); //in caz afirmativ se afiseaza solutia in fisierul de iesire
    }
    else //atfel
    {
        if (linie < 9 && coloana == 10) //daca ne aflam la finalul unei linii trecem pe linia urmatoare si pe prima coloana
        {
            backtracking(linie + 1, 1);
        }
        else
        {
            if (solutieInitiala[linie][coloana] == 0) //daca in casuta in care dorim sa introducem valori nu se afla deja o valoarea default
            {
                vectorFrecventaCurent[matriceID[linie][coloana]]++; //crestem vectorul de frecventa care ne masoara cate casute am completat pana acum
                while (valoareLibera(linie, coloana) == true)       // daca valoarea din casuta pe care o completam este mai mica decat 9
                {
                    solutie[linie][coloana]++;                                     //o incrementam
                    if (verifica(linie, coloana, solutie[linie][coloana]) == true) //si verificam daca aceasta poate fi folosita
                    {
                        if (vectorFrecventaCurent[matriceID[linie][coloana]] != vectorFrecventaInitial[matriceID[linie][coloana]]) //in cazul in care nu am completat
                        //toate casutele dintr-o grupa de celule
                        {
                            if ((linie != 3 && linie != 6 && linie != 9) && (coloana == 3 || coloana == 6 || coloana == 9)) //daca nu se gaseste pe ultima linie
                            //din orice chenar, dar se gaseste pe ultima coloana
                            {
                                backtracking(linie + 1, coloana - 2); //trecem pe linia urmatoare, de la inceputul chenarului
                            }
                            else if (linie == 3 && (coloana == 3 || coloana == 6)) //daca se gaseste pe linia 3, la finalul chenarului,
                                backtracking(1, coloana + 1);                      //mergem pe prima linie, in prima casuta din chenarul urmator
                            else if (linie == 6 && (coloana == 3 || coloana == 6)) //daca se gaseste pe linia 6, la finalul chenarului,
                                backtracking(4, coloana + 1);                      //mergem pe linia 4, in prima casuta din urmatorul chenar
                            else if (linie == 9 && (coloana == 3 || coloana == 6)) //daca se gaseste pe linia 9, la finalul chenarului,
                                backtracking(7, coloana + 1);                      //mergem pe linia 7, in prima casuta din chenarul urmator
                            else if ((linie == 3 || linie == 6) && coloana == 9)   //daca se gaseste pe linia 3 sau 6 si pe ultima coloana, mergem
                                                                                   // in urmatorul chenar de jos
                                backtracking(linie + 1, 1);
                            else //cazul de baza, atunci cand trebuie sa mergem doar pe urmatoarea coloana
                            {
                                backtracking(linie, coloana + 1);
                            }
                        }
                        else
                        {
                            if ((linie != 3 && linie != 6 && linie != 9) && (coloana == 3 || coloana == 6 || coloana == 9))
                            {
                                backtracking(linie + 1, coloana - 2);
                            }
                            else if (linie == 3 && (coloana == 3 || coloana == 6))
                                backtracking(1, coloana + 1);
                            else if (linie == 6 && (coloana == 3 || coloana == 6))
                                backtracking(4, coloana + 1);
                            else if (linie == 9 && (coloana == 3 || coloana == 6))
                                backtracking(7, coloana + 1);
                            else if ((linie == 3 || linie == 6) && coloana == 9)
                                backtracking(linie + 1, 1);
                            else
                            {
                                backtracking(linie, coloana + 1);
                            }
                        }
                    }
                }
                solutie[linie][coloana] = 0;                        //resetam
                vectorFrecventaCurent[matriceID[linie][coloana]]--; //scadem numarul de elemente puse
            }
            else if ((linie != 3 && linie != 6 && linie != 9) && (coloana == 3 || coloana == 6 || coloana == 9)) //daca avem deja o valoare pe acea pozitie nu
                                                                                                                 //modificam
            {
                backtracking(linie + 1, coloana - 2);
            }
            else if (linie == 3 && (coloana == 3 || coloana == 6))
                backtracking(1, coloana + 1);
            else if (linie == 6 && (coloana == 3 || coloana == 6))
                backtracking(4, coloana + 1);
            else if (linie == 9 && (coloana == 3 || coloana == 6))
                backtracking(7, coloana + 1);
            else if ((linie == 3 || linie == 6) && coloana == 9)
                backtracking(linie + 1, 1);
            else
            {
                backtracking(linie, coloana + 1);
            }
        }
    }
}

int main()
{
    initializare();     //initializam variabilele
    backtracking(1, 1); //facem apel de prima casuta din matrice

    return 0;
}
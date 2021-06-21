#include <iostream>
#include <fstream>
using namespace std;

int matriceID[11][11], sumaGrupe[50];
int sumaPartiala[50] = { 0 };
int solutieInitiala[11][11] = { 0 };
int solutie[11][11] = { 0 };
int numarGrupe;
int vectorFrecventaInitial[50] = { 0 }, vectorFrecventaCurent[50] = { 0 };

ifstream f("killerdataVlad.in");
ofstream g("killerSudoku.out");

void initializare()
{
    int i, j, aux;
    while (f >> i >> j)
        if (i >- 1 && j >- 1) {
            f >> solutie[i][j];
            solutieInitiala[i][j] = 1;
        }
        else
            break;
    f >> numarGrupe;

   for(int k=1;k<=numarGrupe;k++){
        f>>sumaGrupe[k];
        f >> vectorFrecventaCurent[k];
        for (int l = 1; l <= vectorFrecventaCurent[k]; l++) {
            f >> i >> j;
            matriceID[i][j] = k;
        }
    }
}

void calculareNumarElementeInCage()
{
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
        {
            if (solutie[i][j] == 0)
                vectorFrecventaInitial[matriceID[i][j]]++;
        }
}

void afisare()
{
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
            g << solutie[i][j] << " ";
        g << endl;
    }
}

bool folositInRand(int rand, int coloana, int numarVerificat)
{
    bool aux = false;
    for (int j = 1; j <= 9; j++)
    {
        if (solutie[rand][j] == numarVerificat && j != coloana)
        {
            //cout << solutie[rand][j] << " == " << numarVerificat << endl;
            aux = true;
        }
        //cout << aux << " ";
    }
    //cout << endl;
    return aux;
}
bool folositInColoana(int rand, int coloana, int numarVerificat)
{
    bool aux = false;
    for (int i = 1; i <= 9; i++)
    {
        if (solutie[i][coloana] == numarVerificat && i != rand)
            aux = true;
    }
    //cout << aux << " ";
    return aux;
}

bool folositInChenar(int rand, int coloana, int xChenar, int yChenar, int numarVerificat)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (solutie[i + xChenar][j + yChenar] == numarVerificat && rand != i + xChenar && coloana != j + yChenar)
                return true;
        }
    }
    return false;
}

bool verifica(int rand, int coloana, int numarVerificat)
{
    //cout << solutie[rand][coloana] << " " << numarVerificat << " " << rand << "-" << coloana << endl;
    bool aux = !folositInRand(rand, coloana, numarVerificat);
    bool aux2 = !folositInColoana(rand, coloana, numarVerificat);
    bool aux3 = !folositInChenar(rand, coloana, (rand-1) - (rand-1) % 3+1, (coloana-1) - (coloana-1) % 3+1, numarVerificat);
    //cout << endl

    //cout << aux << " " << aux2 << " " << aux3 << endl;
    return aux && aux2 && aux3;
}

int calculareSumaPartiala(int id)
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

bool verificareSuma()
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

bool valoareLibera(int i, int j)
{
    if (solutie[i][j] < 9)
    {
        return true;
    }
    else
        return false;
}

void backtracking(int linie, int coloana)
{
    if (linie == 9 && coloana == 10 && verificareSuma() == true)
    {
        afisare();
    }
    else
    {
        if (linie < 9 && coloana == 10)
        {
            //cout << "verifica" << endl;
            backtracking(linie + 1, 1);
        }
        else
        {
            if (solutieInitiala[linie][coloana] == 0)
            {
                //cout << 1 << " ";
                vectorFrecventaCurent[matriceID[linie][coloana]]++;
                //cout << linie << " " << coloana << " " << vectorFrecventaCurent[matriceID[linie][coloana]] << endl;
                while (valoareLibera(linie, coloana) == true)
                {
                    solutie[linie][coloana]++;
                    //cout << 2 << " ";
                    //cout << solutie[linie][coloana] << " " << linie << " " << coloana << " " << endl;
                    //cout << linie << " " << coloana << " " << solutie[linie][coloana];
                    if (verifica(linie, coloana, solutie[linie][coloana]) == true)
                    {
                        //afisare();
                        //cout << endl << endl;
                        if (vectorFrecventaCurent[matriceID[linie][coloana]] != vectorFrecventaInitial[matriceID[linie][coloana]])
                        {
                            if (linie < 3 && (coloana == 3 || coloana == 6 || coloana == 9)) {
                                backtracking(linie + 1, coloana - 2);
                            }
                            else if (linie == 3 && (coloana == 3 || coloana == 6))
                                backtracking(1, coloana + 1);
                            else if ((linie == 3 || linie == 6) && coloana == 9)
                                backtracking(linie + 1, 1);
                            else
                            {
                                backtracking(linie, coloana + 1);
                            }
                        }
                        else
                        {
                            if (calculareSumaPartiala(matriceID[linie][coloana]) == sumaGrupe[matriceID[linie][coloana]])
                            {
                                if (linie < 3 && (coloana == 3 || coloana == 6 || coloana == 9)) {
                                    backtracking(linie + 1, coloana - 2);
                                }
                                else if (linie == 3 && (coloana == 3 || coloana == 6))
                                    backtracking(1, coloana + 1);
                                else if ((linie == 3 || linie == 6) && coloana == 9)
                                    backtracking(linie + 1, 1);
                                else
                                {
                                    backtracking(linie, coloana + 1);
                                }
                            }
                        }
                    }
                }
                solutie[linie][coloana] = 0;
                vectorFrecventaCurent[matriceID[linie][coloana]]--;
            }
            else if (linie < 3 && (coloana == 3 || coloana == 6 || coloana == 9)) {
                backtracking(linie + 1, coloana - 2);
            }
            else if (linie == 3 && (coloana == 3 || coloana == 6))
                backtracking(1, coloana + 1);
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
    initializare();
    calculareNumarElementeInCage();
    backtracking(1, 1);
    //cout << "Deschideti fisierul solutie.out pentru a vizualiza rezultatul...";

    return 0;
}
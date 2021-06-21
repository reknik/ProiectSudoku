#include <iostream>
#include <fstream>
using namespace std;

//struct-ul sudoku va fi folosit pentru matricea de backtracking care va cauta solutia
//si contine 3 campuri: value (valoarea unei anumite celule din sudoku), cage (indicele cage-ului caruia ii apartine o anumita celula)
//si def (prescurtare de la ,,default", avand valoarea true daca celula a fost completata din citirea fisierului si false 
//daca este o celula libera in care se vor testa valori)
struct sudoku {
	int value = 0, cage = 0;
	bool def = false;
};

//struct-ul cage va fi folosit pentru vectorul cages[] care va retine detaliile legate de cage-uri:
//si contine 3 camprui: value (valoarea unui cage, pe desen fiind reprezentata ca numarul din coltul sus-stanga al cage-ului),
//curent (cate celule au o valoare la un moment dat intr-un cage) si total (numarul total de celule dintr-un cage)
struct cage {
	int value = 0, curent = 0, total = 0;
};

//matricea sud este folosita pentru backtracking, iar vectorul cages contine detaliile cage-urilor
sudoku sud[50][50];
cage cages[85];
int n_cages;

//functia read citeste datele din fisierul de intrare
void read() {
	ifstream f("d:\\killerdataDavid.in");
	//testarea deschiderii fisierului
	if (!f) {
		cout << "Nu s-a deschis fisierul!";
	}
	else {
		int i = -10, j = -10;
		//citirea celulelor default (care contin o valoare de la inceput)
		while (f >> i >> j) {
			if (i > -1 && j > -1) {
				f >> sud[i][j].value;
				sud[i][j].def = true;
			}
			else {
				break;
			}
		}
		//citirea numarului de cage-uri apoi a cage-urilor individuale (valoarea, numarul total de celule si
		//asignarea id-ului de cage pentru fiecare celula care face parte din aceasta)
		f >> n_cages;
		for (int i = 1; i <= n_cages; i++) {
			f >> cages[i].value;
			f >> cages[i].total;
			for (int j = 1; j <= cages[i].total; j++) {
				int l, c;
				f >> l;
				f >> c;
				sud[l][c].cage = i;
			}
		}
	}
}

//functia reglare_curent_cu_default cauta celulele default si incrementeaza pentru cage-ul de care apartin campul curent
//din moment ce acele celule au deja o valoare care nu se va schimba pe parcurs
void reglare_curent_cu_default() {
	for (int k = 1; k <= n_cages; k++) {
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 9; j++) {
				if (sud[i][j].value != 0) {
					if (sud[i][j].cage == k) {
						cages[k].curent++;
					}
				}
			}
		}
	}
}

//aceasta functie poate fi folosita pentru afisarea in consola, sub forma de sudoku, a matricei sud intr-un anumit moment
void afisare() {
	cout << endl << "-------------------------------------------------------------------------------------------------" << endl;
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			if (j == 1) {
				cout << "|\t";
			}
			cout << sud[i][j].value << "\t";
			if (j % 3 == 0 && j!=9) {
				cout << "|\t";
			}
			else if (j == 9) {
				cout << "|";
			}
		}
		if (i % 3 == 0) {
			cout << endl << "-------------------------------------------------------------------------------------------------" << endl;
		}
		else {
			cout << endl;
		}
	}
	cout << endl;
}

//functia compile_file este folosita pentru a scrie intr-un fisier de iesire solutia
void compile_file() {
	ofstream h("d:\\solutie.txt");
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			h << sud[i][j].value << " ";
		}
		h << endl;
	}
	h.close();
}

//functia linie_coloana_box testeaza daca o anumita valoare, aflata pe linia line si coloana column, respecta regulile standard de
//sudoku: nu se repeta pe linie, pe coloana sau in box (portiunea de 3x3 celule)
//returneaza true daca valoarea v este gasita pe linie, pe coloana sau in box
//returneaza false daca nu este gasita
bool linie_coloana_box(int line, int column, int v) {
	int i = 1;
	bool aux = false;
	//testarea pe linie
	while (i <= 9 && aux == false) {
		if (sud[line][i].value == v && i!=column) {
			aux = true;
		}
		else {
			i++;
		}
	}
	int j = 1;
	//testarea pe coloana
	while (j <= 9 && aux == false) {
		if (sud[j][column].value == v && j!=line) {
			aux = true;
		}
		else {
			j++;
		}
	}
	int l, c;
	//obtinerea punctului de plecare pentru testarea in box (coltul sus-stanga al box-ului)
	if (line == 1 || line == 2 || line == 3) {
		l = 1;
	}
	else if (line == 4 || line == 5 || line == 6) {
		l = 4;
	}
	else {
		l = 7;
	}
	if (column == 1 || column == 2 || column == 3) {
		c = 1;
	}
	else if (column == 4 || column == 5 || column == 6) {
		c = 4;
	}
	else {
		c = 7;
	}
	i = l;
	//testarea in box
	while (i <= (l + 2) && aux == false) {
		j = c;
		while (j <= (c + 2) && aux == false) {
			if (i != line || j != column) {
				if (sud[i][j].value==v) {
					aux = true;
				}
				else {
					j++;
				}
			}
			else {
				j++;
			}
		}
		i++;
	} 
	return aux;
}

//functia suma_cage calculeaza suma cage-ului cu indicele which
int suma_cage(int which) {
	int s = 0;
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			if (sud[i][j].cage == which) {
				s += sud[i][j].value;
			}
		}
	}
	return s;
}

//functia solutie testeaza daca valorile dintr-un cage au suma corespunzatoare cu valoarea care se cere - cages[i].value
bool solutie() {
	bool solved = true;
	int i = 1;
	while (i <= n_cages && solved == true) {
		if (suma_cage(i) != cages[i].value) {
			solved = false;
		}
		else {
			i++;
		}
	}
	return solved;
}

//functia initializare initializeaza valoarea celulei de linie i si coloana j cu 0
void initializare(int i, int j) {
	sud[i][j].value = 0;
}

//functia succesor returneaza true in cazul in care valoarea de pe linia i si coloana j este mai mica decat 9 (se mai poate incrementa)
//sau false daca valoarea amintita este mai mare sau egala cu 9 (nu se mai poate incrementa)
bool succesor(int i, int j) {
	if (sud[i][j].value < 9) {
		return true;
	}
	else {
		return false;
	}
}

//functia back reprezinta portiunea de backtracking a programului si porneste de la linia k si coloana k2
void back(int k, int k2) {
	//daca indicele liniei a ajuns la 9, indicele coloanei la 10 (s-a trecut de ultima celula din coltul jos-dreapta) - adica avem o 
	//structura de sudoku valida - si functia solutie returneaza true (toate sumele corespund) se scrie solutia intr-un fisier
	if (k == 9 && k2 == 10 && solutie()==true) {
		compile_file();
	}
	else {
		//altfel se testeaza daca s-a ajuns la capat de rand
		//in caz afirmativ se trece pe randul urmator
		if (k < 9 && k2 == 10) {
			back(k + 1, 1);
		}
		else {
			//in caz negativ se testeaza daca valoarea la care s-a ajuns este default (nu trebuie modificata)
			//in caz afirmativ se incepe cautarea unei valori valide pentru celula respectiva
			if (sud[k][k2].def == false) {
				//se creste numarul de celule care au o valoare din cage-ul cu id-ul sud[k][k2].cage
				cages[sud[k][k2].cage].curent++;
				//cat timp celula cu indicii k si k2 are succesor se incrementeaza si se testeaza valoarea acesteia
				while (succesor(k, k2) == true) {
					sud[k][k2].value++;
					//daca valoarea sud[k][k2].value nu este gasita pe linie, coloana sau in box (respecta regulile standard de sudoku)
					if (linie_coloana_box(k, k2, sud[k][k2].value) == false) {
						//se testeaza cage-ul sud[k][k2].cage: daca exista celule care nu au valori in aceasta (curent != total)
						//se trece la urmatoarea celula
						if (cages[sud[k][k2].cage].curent != cages[sud[k][k2].cage].total) {
							back(k, k2 + 1);
						}
						//altfel se testeaza daca suma din cage este valida si doar in caz afirmativ se trece la urmatoarea celula
						else {
							if (suma_cage(sud[k][k2].cage) == cages[sud[k][k2].cage].value) {
								back(k, k2 + 1);
							}
						}
					}
				}
				//atunci cand procesul ,,se intoarce" valorile care raman in fata pot influenta functia linie_coloana_box chiar daca ele
				//nu mai conteaza asa ca trebuie readuse la 0 si in aceeasi maniera este redus si cages[sud[k][k2].cage].curent
				initializare(k, k2);
				cages[sud[k][k2].cage].curent--;
			}
			//in caz negativ se trece la urmatoarea celula
			else {
				back(k, k2 + 1);
			}
		}
	}
}

int main() {
	read();
	reglare_curent_cu_default();
	back(1,1);
	return 0;
}
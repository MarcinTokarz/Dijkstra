#include <cmath>
#include <iostream>

using namespace std;

//Zmienne
int miastoPoczatkowe, nastepneNajkrotsze, *sciezka, *miastoPrzejechane, i, j, n;
double najkrotszaDroga, calkowitaDroga, **wspolzedneMiast, **odleglosciMiedzyMiastami;

double OdlegloscMiedzyMiastami(int a, int b) {
	double kwadratOdleglosci, roznicaX, roznicaY;
	roznicaX = wspolzedneMiast[a][0] - wspolzedneMiast[b][0];
	roznicaY = wspolzedneMiast[a][1] - wspolzedneMiast[b][1];
	kwadratOdleglosci = roznicaX * roznicaX + roznicaY * roznicaY;
	return sqrt(kwadratOdleglosci);
}

void WypelnijOdleglosciMiedzyMiastami() {
	for (i = 0; i < n; i++ ) {
		for (j = 0; j < n; j++) {
			odleglosciMiedzyMiastami[i][j] = OdlegloscMiedzyMiastami(i,j);
		}
	}
}

void WypelnijWspolrzedneMiast() {
	for (i = 0; i < n; i++ ) {
		cout << i << ": ";
		cin >> wspolzedneMiast[i][0] >> wspolzedneMiast[i][1];
	}
}

void InicjalizacjaZmiennych() {
	nastepneNajkrotsze = -1;
	for (i = 0; i < n; i++) {
		sciezka[i] = 0;
		miastoPrzejechane[i] = 0;
		najkrotszaDroga = 9999;
		calkowitaDroga = 0;
	}
	miastoPrzejechane[miastoPoczatkowe] = 1;
	sciezka[0] = miastoPoczatkowe;
}

int main() {

	cout << "Podaj liczbe miast: ";
	cin >> n;

	cout << "Podaj miasto poczatkowe: ";
	cin >> miastoPoczatkowe;

	sciezka = new int [n];
	miastoPrzejechane = new int [n];

	// dynamic allocation
	wspolzedneMiast = new double*[n];
	for(i = 0; i < n; ++i)
		wspolzedneMiast[i] = new double[2];

	odleglosciMiedzyMiastami = new double*[n];
	for(i = 0; i < n; ++i)
		odleglosciMiedzyMiastami[i] = new double[n];

	InicjalizacjaZmiennych();

	WypelnijWspolrzedneMiast();

	WypelnijOdleglosciMiedzyMiastami();

	for (i = 1; i < n; i++) { //tyle razy ile jest miast - 1 bo juz mamy start
		//zresetuj zmienne
		najkrotszaDroga = 9999;

		//szukaj najkrotszej drogi
		for (j = 0; j < n; j++) { //tyle razy ile jest miast - szukamy nastepnej najkrotszej drogi
			if (miastoPrzejechane[j] != 1 && sciezka[i-1] != j) { //jezeli jeszcze nie bylismy w danym miescie
				if (odleglosciMiedzyMiastami[sciezka[i-1]] [j] < najkrotszaDroga) { //jezeli dana trasa bedzie krotsza od juz znalezionej
					najkrotszaDroga = odleglosciMiedzyMiastami[sciezka[i-1]] [j];
					nastepneNajkrotsze = j;
				}
			}
		}

		//zapisz ze najkrotsza droga
		calkowitaDroga += najkrotszaDroga;
		sciezka[i] = nastepneNajkrotsze;
		cout << "Nastepne miasto to: " << nastepneNajkrotsze << ", bo najkrotsza trasa to: " << najkrotszaDroga << endl;
	}

	cout << "Sciezka:" << endl;
	for (i = 0; i < n; i++ ) {
		cout << sciezka[i] << endl;
	}
	cout << "Calkowita droga: " << calkowitaDroga << endl;
}

// Projekt 1 - Wielomiany


#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
vector<double> suma(vector<vector<double>> wektory) {					//funkcja sumujaca wielomiany

	vector<double> wynik = wektory[0];

	for (int i = 1; i < wektory.size(); i++) {
		for (int j = 0; j < wektory[i].size(); j++) {

			wynik[j] += wektory[i][j];
		}
	}

	return wynik;
}

vector<double> roznica(vector<vector<double>> wektory) {				//funkcja odejmujaca wielomiany

	vector<double> wynik = wektory[0];

	for (int i = 1; i < wektory.size(); i++) {
		for (int j = 0; j < wektory[i].size(); j++) {

			wynik[j] -= wektory[i][j];
		}
	}

	return wynik;
}

double ck(vector<double> a, vector<double> b, int k) {			//funkcja pomocnicza dla funckji iloczyn
	double wynik = 0;
	for (int i = 0; i <= k; i++) {
		if (i < a.size() && (k - i) < b.size())
			wynik += a[i] * b[k - i];
	}

	return wynik;
}
int maxdlugosc(vector<vector<double>> wektory) {			//funkcja sprawdzajaca jaka dlugosc ma najdluzszy wielomian
	if (wektory.size() > 0) {
		int max = wektory[0].size();
		for (int i = 0; i < wektory.size(); i++) {
			if (wektory[i].size() > max) {
				max = wektory[i].size();
			}
		}
		return max;
	}return 0;

}


void normalizacja(vector<vector<double>> &wektory) {			//funkcja ustawiajaca odpowiednio wielomiany w vectorach
	int max = maxdlugosc(wektory);
	for (int i = 0; i < wektory.size(); i++) {
		if (wektory[i].size() < max) {
			int iterations = max - wektory[i].size();
			for (int j = 0; j < iterations; j++) {
				wektory[i].insert(wektory[i].begin(), 0.0);
			}
		}

	}

}

void usunzera(vector<double> &wektor) {					//funkcja usuwajaca zbedne zera z wyniku mnozenia wielomianow
	vector<double> pom;
	int index = 0;
	while (wektor[index] == 0) {
		index++;
	}
	for (int i = index; i<wektor.size(); i++) {
		pom.push_back(wektor[i]);

	}
	wektor = pom;
}


vector<double> iloczyn(vector<vector<double>> wektory) {			//funkcja mnozaca wielomiany

	vector<double> wynik = wektory[0];
	for (int j = 1; j < wektory.size(); j++) {
		vector<double> pom;
		int n = wynik.size();
		vector<vector<double>> pom2;
		pom2.push_back(wynik);
		pom2.push_back(wektory[j]);
		normalizacja(pom2);
		for (int i = 0; i <= (2 * n - 2); i++) {
			pom.push_back(ck(pom2[0], pom2[1], i));
		}
		wynik = pom;
	}
	usunzera(wynik);
	return wynik;
}


bool testplikuwejsciowego(string nazwapliku)			//funkcja sprawdzajaca poprawnosc pliku wejsciowego
{
	
	fstream wejscie;
	wejscie.open(nazwapliku, ios::in);
	if (!wejscie.good())
		return false;
	else {
		while (true) {
			char znak;
			wejscie >> znak;
			if (wejscie.good()) {
				if ((znak>='0'&&znak<='9')||znak=='-'||znak=='.') {
				continue;
			}
			else
					return false;
			}
			else
				break;
		}
	}
	wejscie.close();
}



vector<vector<double>> wczytywanie(string nazwapliku)				//funkcja wczytujaca dane z pliku
{
	vector<vector<double>> wynik;
	fstream wejscie;
	wejscie.open(nazwapliku, ios::in);
	string linia;
	int numerlinii = 0;
	while (getline(wejscie, linia)) {
		stringstream liniastream = stringstream(linia);
		vector<double> pomocniczy;
		while (!liniastream.eof()) {
			double liczba;
			liniastream >> liczba;
			pomocniczy.push_back(liczba);
		}
		wynik.push_back(pomocniczy);

	}

	wejscie.close();
	return wynik;
}

void zapis(string wyjscie, vector<double> wynik) {				//funkcja zapisujaca wyniki do pliku
	fstream output;
	output.open(wyjscie, ios::out);
	for (int i = 0; i < wynik.size(); i++) {
		output << wynik[i] << " ";
	}
	output.close();
}

int main(int argc, char *argv[]) {
	int i=1;
	string sciezkawejscia;
	string sciezkawyjscia;
	string operacja;
	
	while(i<argc){							//odczyt parametrow programu
		string text = string(argv[i]);
		if (text == "-i") {
			sciezkawejscia = argv[i + 1];
			i = i + 2;
		}
		else {
			if (text == "-o") {
				sciezkawyjscia = argv[i + 1];
				i = i + 2;
			}
			else {
				if(text == "-d"){
					operacja = argv[i + 1];
					i = i + 2;
			}else{
					cout << "Nieprawidlowe parametry!"<<endl;
					system("PAUSE");
					return 0;
			}
		}
		


		}
	}
	if (!testplikuwejsciowego(sciezkawejscia))						//test pliku wejsciowego
	{
		cout << "Nieprawidlowe dane w pliku wejsciowym lub brak pliku wejscoiwego!"<<endl;
		system("PAUSE");
		return 0;
		
	}
	vector<vector<double>> wyn = wczytywanie(sciezkawejscia);
	normalizacja(wyn);
	vector<double> wyniksuma;
	vector<double> wynikroznica;
	vector<double> wynikiloczyn;

	if (operacja == "suma") {							// wybor odpoiedniego dzialania
		wyniksuma = suma(wyn);
		zapis(sciezkawyjscia, wyniksuma);
	}
	else {
		if (operacja == "roznica") {
			wynikroznica = roznica(wyn);
			zapis(sciezkawyjscia, wynikroznica);
		}
		else {
			if (operacja == "iloczyn") {
				wynikiloczyn = iloczyn(wyn);
				zapis(sciezkawyjscia, wynikiloczyn);
			}
			else {
				cout << "Nieprawidlowe parametry!";
				system("PAUSE");
			}
		}
	}
	return 0;
}

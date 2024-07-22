#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int darab;

struct Adat {
  int kezd, veg;
  char szin;
};

vector<Adat> adatok;

void feladat1();
void feladat2();
void feladat3();
void feladat4();

int main() {
  feladat1();
  feladat2();
  feladat3();
  feladat4();
  return 0;
}

void feladat1() {
  ifstream infile("felajanlas.txt");
  if (!infile.is_open()) {
    cout << "Nem sikerult megnyitni a fajlt!" << endl;
    return;
  }

  infile >> darab;
  Adat a;
  while (infile >> a.kezd >> a.veg >> a.szin) {
    adatok.push_back(a);
  }

  infile.close();
}

void feladat2() {
  cout << endl << "2. feladat" << endl;
  cout << "A felajánlások száma: " << adatok.size() << endl;
}

void feladat3() {
  cout << endl << "3. feladat" << endl;
  int n = 0;
  cout << "A bejárat mindkét oldalán ültetők: ";
  for (const auto &adat : adatok) {
    n++;
    if (adat.veg < adat.kezd) {
      cout << n << " ";
    }
  }
  cout << endl;
}

void feladat4() {
  cout << endl << "4. feladat" << endl;
  int szam;
  cout << "Adja meg az ágyás sorszámát! ";
  cin >> szam;
  int ajanlok = 0;
  for (const auto &adat : adatok) {
    if (adat.kezd <= szam && adat.veg >= szam) {
      ajanlok++;
    }
  }
  cout << "A felajánlók száma: " << ajanlok << endl;
}

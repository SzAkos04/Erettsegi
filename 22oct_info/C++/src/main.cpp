#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct adat_t {
    int ora, perc, masodperc;
    int x, y;
};

vector<adat_t> adatok;

void feladat1();
void feladat2();
int eltelt();
void feladat4();

int main() {
    feladat1();
    feladat2();
    feladat4();

    return 0;
}

void feladat1() {
    ifstream infile("jel.txt");
    if (!infile.is_open()) {
        cerr << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    adat_t adat;
    while (infile >> adat.ora >> adat.perc >> adat.masodperc >> adat.x >> adat.y) {
        adatok.push_back(adat);
    }

    infile.close();
}

void feladat2() {
    cout << "2. feladat" << endl;
    int input;
    cout << "Adja meg a jel sorszámát! ";
    cin >> input;
    input--; // egyes index

    cout << "x=" << adatok.at(input).x << " y=" << adatok.at(input).y << endl;
    
    cout << endl;
}

int eltelt(adat_t a1, adat_t a2) {
    return
        ((a2.ora - a1.ora) * 60 * 60) +
        ((a2.perc - a1.perc) * 60) +
        (a2.masodperc - a1.masodperc);
}

void feladat4() {
    cout << "4. feladat" << endl;

    int mp = eltelt(adatok.front(), adatok.back());

    cout << "Időtartam: " << ((mp / 3600 < 10) ? "0" : "") << (mp / 3600)
        << ":" << ((mp / 60 % 60 < 10) ? "0" : "") << (mp / 60 % 60)
        << ":" << ((mp % 60 < 10) ? "0" : "") << (mp % 60) << endl;
    
    cout << endl;
}
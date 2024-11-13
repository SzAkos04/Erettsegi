#include <cmath>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

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
void feladat5();
void feladat6();
void feladat7();

int main() {
    feladat1();
    feladat2();
    feladat4();
    feladat5();
    feladat6();
    feladat7();

    return 0;
}

void feladat1() {
    ifstream infile("jel.txt");
    if (!infile.is_open()) {
        cerr << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    adat_t adat;
    while (infile >> adat.ora >> adat.perc >> adat.masodperc >> adat.x >>
           adat.y) {
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
    return ((a2.ora - a1.ora) * 60 * 60) + ((a2.perc - a1.perc) * 60) +
           (a2.masodperc - a1.masodperc);
}

void feladat4() {
    cout << "4. feladat" << endl;

    int mp = eltelt(adatok.front(), adatok.back());

    cout << "Időtartam: " << ((mp / 3600 < 10) ? "0" : "") << (mp / 3600) << ":"
         << ((mp / 60 % 60 < 10) ? "0" : "") << (mp / 60 % 60) << ":"
         << ((mp % 60 < 10) ? "0" : "") << (mp % 60) << endl;

    cout << endl;
}

void feladat5() {
    cout << "5. feladat" << endl;
    int xmin = INT32_MAX, xmax = INT32_MIN;
    int ymin = INT32_MAX, ymax = INT32_MIN;

    for (const auto &adat : adatok) {
        if (adat.x < xmin) {
            xmin = adat.x;
        }
        if (adat.x > xmax) {
            xmax = adat.x;
        }
        if (adat.y < ymin) {
            ymin = adat.y;
        }
        if (adat.y > ymax) {
            ymax = adat.y;
        }
    }

    cout << "Bal alsó: " << xmin << " " << ymin << ", jobb felső: " << xmax
         << " " << ymax << endl;

    cout << endl;
}

void feladat6() {
    cout << "6. feladat" << endl;

    double s = 0;

    for (size_t i = 0; i < adatok.size() - 1; ++i) {
        s += sqrt(pow(abs(adatok.at(i).x - adatok.at(i + 1).x), 2) +
                  pow(abs(adatok.at(i).y - adatok.at(i + 1).y), 2));
    }

    cout << "Elmozdulás: " << fixed << setprecision(3) << s << " egység"
         << endl;

    cout << endl;
}

void feladat7() {
    ofstream outfile("kimaradt.txt");
    if (!outfile.is_open()) {
        cerr << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    // TODO: Last task

    outfile.close();
}

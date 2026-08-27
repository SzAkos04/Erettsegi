#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct adat {
    int kezdet, veg, sebesseg;
};

vector<adat> adatok;

void feladat1();
void feladat2();
void feladat3();
void feladat4();
void feladat5();
void feladat6();
void feladat7();

int main() {
    feladat1();
    feladat2();
    feladat3();
    feladat4();
    feladat5();
    feladat6();
    feladat7();

    return 0;
}

string azonosito;

void feladat1() {
    cout << "1. feladat" << endl;
    cout << "Kérem adja meg az autó azonosítóját! ";
    cin >> azonosito;

    ifstream infile(azonosito + string(".txt"));
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni a " << azonosito << ".txt fajlt!"
             << endl;
        return;
    }

    adat a;
    while (infile >> a.kezdet >> a.veg >> a.sebesseg) {
        adatok.push_back(a);
    }

    infile.close();
}

void feladat2() {
    cout << "2. feladat" << endl;
    cout << "Az autó a " << adatok.at(0).kezdet << ". másodpercben indult el."
         << endl;
    cout << "Az autó a megfigyelés végén "
         << adatok.at(adatok.size() - 1).sebesseg << " m/s sebességgel haladt."
         << endl;
}

void feladat3() {
    cout << "3. feladat" << endl;
    for (const auto &adat : adatok) {
        if (adat.sebesseg > 14) {
            cout << "Az autó átlépte a sebességhatárt." << endl;
            return;
        }
    }
    cout << "Az autó nem lépte át a sebességhatárt." << endl;
}

void feladat4() {
    cout << "4. feladat" << endl;

    // addig all, amig elso gyorsulas meg nem tortenik
    int max = adatok.at(0).kezdet;
    int kezd = 0, veg = max; // ez kezdodik es vegzodik mint max
    for (int i = 0; i < adatok.size() - 1;
         ++i) { // i-edik lelassul 0-ra, ahol a vege a kezdete az allasnak
        if (adatok.at(i).sebesseg == 0) {
            int delta = adatok.at(i + 1).kezdet - adatok.at(i).veg;
            if (delta > max) {
                max = delta;
                kezd = adatok.at(i).veg;
                veg = adatok.at(i + 1).kezdet;
            }
        }
    }
    cout << "A leghosszabb állásidő " << kezd << " és " << veg
         << " másodperc között volt." << endl;
}

void feladat5() {
    cout << "5. feladat" << endl;

    int ido;
    cout << "Mikor vizsgáljuk az autó sebességét? ";
    cin >> ido;

    double sebesseg;
    if (ido >= adatok.at(0).kezdet && ido <= adatok.at(0).veg) {
        double a = (double)adatok.at(0).sebesseg /
                   (adatok.at(0).veg - adatok.at(0).kezdet);
        sebesseg = 0 + (ido - adatok.at(0).kezdet) * a;
    }

    for (int i = 0; i < adatok.size() - 1; ++i) {
        if (adatok.at(i).veg < ido && adatok.at(i + 1).kezdet > ido) {
            // ha eppen konstans sebesseggel ment
            sebesseg = adatok.at(i).sebesseg;
        } else if (adatok.at(i + 1).kezdet <= ido &&
                   ido <= adatok.at(i + 1).veg) {
            // ha eppen gyorsult
            int kezd_v = adatok.at(i).sebesseg;
            double a =
                (double)(adatok.at(i + 1).sebesseg - adatok.at(i).sebesseg) /
                (adatok.at(i + 1).veg - adatok.at(i + 1).kezdet);
            sebesseg = kezd_v + (ido - adatok.at(i + 1).kezdet) * a;
        }
    }
    cout << "Az autó sebessége a(z) " << ido << ". másodpercben " << sebesseg
         << " m/s volt." << endl;
}

void feladat6() {
    cout << "6. feladat" << endl;

    // legelso gyorsulas
    double s = (0.0 + adatok.at(0).sebesseg) / 2.0 *
               (adatok.at(0).veg - adatok.at(0).kezdet);
    for (int i = 0; i < adatok.size() - 1; ++i) {
        // konstans sebessegu reszek
        s += (adatok.at(i).sebesseg) *
             (adatok.at(i + 1).kezdet - adatok.at(i).veg);

        // gyorsulasok
        s += ((adatok.at(i).sebesseg + adatok.at(i + 1).sebesseg) / 2.0) *
             (adatok.at(i + 1).veg - adatok.at(i + 1).kezdet);
    }

    cout << "A megtett út: " << fixed << setprecision(1) << s << " méter."
         << endl;
}

void feladat7() {
    string filename = string("v") + azonosito + string(".txt");
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cout << "Nem sikerult megnyitni a " << filename << " fajlt!" << endl;
        return;
    }

    int cur_sebesseg = 0;

    for (const auto &adat : adatok) {
        outfile << adat.kezdet << "\t" << cur_sebesseg << endl;
        outfile << adat.veg << "\t" << adat.sebesseg << endl;
        cur_sebesseg = adat.sebesseg;
    }

    outfile.close();
}

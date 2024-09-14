#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Adat {
    int adoszam;
    string utca;
    string hazszam;
    char adosav;
    int alapterulet;
};

vector<Adat> adatok;
int a, b, c;

void feladat1();
void feladat2();
void feladat3();
int ado(char adosav, int alapterulet);
void feladat5();
void feladat6();
void feladat7();

int main() {
    feladat1();
    feladat2();
    feladat3();
    feladat5();
    feladat6();
    feladat7();

    return 0;
}

void feladat1() {
    ifstream infile("utca.txt");
    if (!infile.is_open()) {
        cerr << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    infile >> a >> b >> c;

    Adat adat;
    while (infile >> adat.adoszam >> adat.utca >> adat.hazszam >> adat.adosav >>
           adat.alapterulet) {
        adatok.push_back(adat);
    }
    infile.close();
}

void feladat2() {
    cout << "2. feladat. ";
    cout << "A mintában " << adatok.size() << " telek szerepel." << endl;
}

void feladat3() {
    cout << "3. feladat. ";

    int adoszam;
    cout << "Egy tulajdonos adószáma: ";
    cin >> adoszam;

    bool szerepel = false;

    for (const auto &adat : adatok) {
        if (adat.adoszam == adoszam) {
            cout << adat.utca << " utca " << adat.hazszam << endl;
            szerepel = true;
        }
    }

    if (!szerepel) {
        cout << "Nem szerepel az adatállományban." << endl;
    }
}

int ado(char adosav, int alapterulet) {
    int negyzetmeterenkent;
    switch (adosav) {
    case 'A':
        negyzetmeterenkent = a;
        break;
    case 'B':
        negyzetmeterenkent = b;
        break;
    case 'C':
        negyzetmeterenkent = c;
        break;
    }
    int ado = negyzetmeterenkent * alapterulet;

    return ado < 10000 ? 0 : ado;
}

void feladat5() {
    cout << "5. feladat" << endl;

    int a_darab = 0, a_osszeg = 0;
    int b_darab = 0, b_osszeg = 0;
    int c_darab = 0, c_osszeg = 0;

    for (const auto &adat : adatok) {
        switch (adat.adosav) {
        case 'A':
            a_darab++;
            a_osszeg += ado(adat.adosav, adat.alapterulet);
            break;
        case 'B':
            b_darab++;
            b_osszeg += ado(adat.adosav, adat.alapterulet);
            break;
        case 'C':
            c_darab++;
            c_osszeg += ado(adat.adosav, adat.alapterulet);
            break;
        }
    }

    cout << "A sávba " << a_darab << " telek esik, az adó " << a_osszeg
         << " Ft." << endl;
    cout << "B sávba " << b_darab << " telek esik, az adó " << b_osszeg
         << " Ft." << endl;
    cout << "C sávba " << c_darab << " telek esik, az adó " << c_osszeg
         << " Ft." << endl;
}

void feladat6() {
    cout << "6. feladat. ";

    cout << "A több sávba sorolt utcák:" << endl;

    map<string, char> savok;
    set<string> utcak;
    for (const auto &adat : adatok) {
        savok[adat.utca] = adat.adosav;
        utcak.insert(adat.utca);
    }

    for (const auto &utca : utcak) {
        for (const auto &adat : adatok) {
            if (adat.utca == utca) {
                if (savok[adat.utca] != adat.adosav) {
                    cout << adat.utca << endl;
                    break;
                }
            }
        }
    }
}

void feladat7() {
    map<int, int> fizetendo;
    for (const auto &adat : adatok) {
        fizetendo[adat.adoszam] += ado(adat.adosav, adat.alapterulet);
    }

    ofstream outfile("fizetendo.txt");
    if (!outfile.is_open()) {
        cerr << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    for (const auto &pair : fizetendo) {
        outfile << pair.first << " " << pair.second << endl;
    }

    outfile.close();
}

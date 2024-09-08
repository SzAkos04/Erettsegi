#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Adat {
    int megallo;
    struct {
        int ev, honap, nap, ora, perc;
    } felszallas;
    int id;
    string tipus;
    union {
        int hatra;
        struct {
            int ev, honap, nap;
        } datum;
    } ervenyesseg;
};

vector<Adat> adatok;

void feladat1();
void feladat2();
void feladat3();
void feladat4();
void feladat5();
int napokszama(int e1, int h1, int n1, int e2, int h2, int n2);
void feladat7();

int main() {
    feladat1();
    feladat2();
    feladat3();
    feladat4();
    feladat5();
    feladat7();

    return 0;
}

void feladat1() {
    ifstream infile("utasadat.txt");
    if (!infile.is_open()) {
        cerr << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    Adat a;
    string felszallas;
    string ervenyesseg;
    while (infile >> a.megallo >> felszallas >> a.id >> a.tipus >>
           ervenyesseg) {

        a.felszallas.ev = stoi(felszallas.substr(0, 4));
        a.felszallas.honap = stoi(felszallas.substr(4, 2));
        a.felszallas.nap = stoi(felszallas.substr(6, 2));
        a.felszallas.ora = stoi(felszallas.substr(9, 2));
        a.felszallas.perc = stoi(felszallas.substr(11, 2));

        if (a.tipus == "JGY") {
            a.ervenyesseg.hatra = stoi(ervenyesseg);
        } else {
            a.ervenyesseg.datum.ev = stoi(ervenyesseg.substr(0, 4));
            a.ervenyesseg.datum.honap = stoi(ervenyesseg.substr(4, 2));
            a.ervenyesseg.datum.nap = stoi(ervenyesseg.substr(6, 2));
        }

        adatok.push_back(a);
    }

    infile.close();
}

void feladat2() {
    cout << "2. feladat" << endl;
    cout << "A buszra " << adatok.size() << " utas akart felszállni." << endl;
}

void feladat3() {
    cout << "3. feladat" << endl;
    int ervenytelen = 0;
    int felszall;
    int lejar;
    for (const auto &adat : adatok) {
        if (adat.tipus == "JGY") {
            if (adat.ervenyesseg.hatra == 0) {
                ervenytelen++;
            }
        } else {
            felszall = adat.felszallas.ev * 365 + adat.felszallas.honap * 30 +
                       adat.felszallas.nap;
            lejar = adat.ervenyesseg.datum.ev * 365 +
                    adat.ervenyesseg.datum.honap * 30 +
                    adat.ervenyesseg.datum.nap;

            if (felszall > lejar) {
                ervenytelen++;
            }
        }
    }

    cout << "A buszra " << ervenytelen << " utas nem szállhatott fel." << endl;
}

void feladat4() {
    cout << "4. feladat" << endl;

    unordered_map<int, int> megallok;
    for (const auto &adat : adatok) {
        megallok[adat.megallo]++;
    }

    int max = -1;
    int legkisebb = INT_MAX;
    for (const auto &megallo : megallok) {
        if (megallo.second > max) {
            max = megallo.second;
            legkisebb = megallo.first;
        } else if (megallo.second == max) {
            if (megallo.first < legkisebb) {
                legkisebb = megallo.first;
            }
        }
    }

    cout << "A legtöbb utas (" << max << " fő) a " << legkisebb
         << ". megállóban próbált felszállni." << endl;
}

void feladat5() {
    cout << "5. feladat" << endl;

    int ingyenes = 0;
    int kedvezmenyes = 0;

    int felszall;
    int lejar;
    for (const auto &adat : adatok) {
        // check if ticket is valid
        if (adat.tipus == "JGY") {
            if (adat.ervenyesseg.hatra == 0) {
                continue;
            }
        } else {
            felszall = adat.felszallas.ev * 365 + adat.felszallas.honap * 30 +
                       adat.felszallas.nap;
            lejar = adat.ervenyesseg.datum.ev * 365 +
                    adat.ervenyesseg.datum.honap * 30 +
                    adat.ervenyesseg.datum.nap;

            if (felszall > lejar) {
                continue;
            }
        }

        if (adat.tipus == "TAB" || adat.tipus == "NYB") {
            kedvezmenyes++;
        } else if (adat.tipus == "NYP" || adat.tipus == "RVS" ||
                   adat.tipus == "GYK") {
            ingyenes++;
        }
    }

    cout << "Ingyenesen utazók száma: " << ingyenes << " fő" << endl;
    cout << "A kedvezményesen utazók száma: " << kedvezmenyes << " fő" << endl;
}

int napokszama(int e1, int h1, int n1, int e2, int h2, int n2) {
    h1 = (h1 + 9) % 12;
    e1 = e1 - h1 / 10;
    int d1 =
        365 * e1 + e1 / 4 - e1 / 100 + e1 / 400 + (h1 * 306 + 5) / 10 + n1 - 1;
    h2 = (h2 + 9) % 12;
    e2 = e2 - h2 / 10;
    int d2 =
        365 * e2 + e2 / 4 - e2 / 100 + e2 / 400 + (h2 * 306 + 5) / 10 + n2 - 1;
    return d2 - d1;
}

void feladat7() {
    ofstream outfile("figyelmeztetes.txt");
    if (!outfile.is_open()) {
        cerr << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    int felszall;
    int lejar;
    for (const auto &adat : adatok) {
        if (adat.tipus != "JGY") {
            felszall = adat.felszallas.ev * 365 + adat.felszallas.honap * 30 +
                       adat.felszallas.nap;
            lejar = adat.ervenyesseg.datum.ev * 365 +
                    adat.ervenyesseg.datum.honap * 30 +
                    adat.ervenyesseg.datum.nap;

            if (lejar - felszall <= 3 && lejar - felszall >= 0) {
                outfile << adat.id << " " << adat.ervenyesseg.datum.ev << "-"
                        << (adat.ervenyesseg.datum.honap < 10 ? "0" : "")
                        << adat.ervenyesseg.datum.honap << "-"
                        << (adat.ervenyesseg.datum.nap < 10 ? "0" : "")
                        << adat.ervenyesseg.datum.nap << endl;
            }
        }
    }

    outfile.close();
}

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Adat {
    int nap;
    string varos;
    int darab;
};

vector<Adat> adatok;

void feladat1();
void feladat2();
void feladat3();
void feladat4();
void feladat5();
int osszes(string varos, int nap);
void feladat7();
void feladat8();

int main() {
    feladat1();
    feladat2();
    feladat3();
    feladat4();
    feladat5();
    feladat7();
    feladat8();

    return 0;
}

void feladat1() {
    ifstream infile("rendel.txt");
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    Adat adat;
    while (infile >> adat.nap >> adat.varos >> adat.darab) {
        adatok.push_back(adat);
    }

    infile.close();
}

void feladat2() {
    cout << "2. feladat" << endl;
    cout << "A rendelések száma: " << adatok.size() << endl;
}

void feladat3() {
    cout << "3. feladat" << endl;

    int nap;
    cout << "Kérem, adjon meg egy napot: ";
    cin >> nap;

    int n = 0;
    for (const auto &adat : adatok) {
        if (adat.nap == nap) {
            n++;
        }
    }
    cout << "A rendelések száma az adott napon: " << n << endl;
}

void feladat4() {
    cout << "4. feladat" << endl;
    int n = 0;
    bool rendel;

    int min = 31, max = -1;
    for (const auto &adat : adatok) {
        if (adat.nap < min) {
            min = adat.nap;
        }
        if (adat.nap > max) {
            max = adat.nap;
        }
    }
    for (int i = min; i <= max; i++) {
        rendel = false;
        for (const auto &adat : adatok) {
            if (adat.nap == i && adat.varos == "NR") {
                rendel = true;
                break;
            }
        }
        if (!rendel) {
            n++;
        }
    }
    if (n == 0) {
        cout << "Minden nap volt rendelés a reklámban nem érintett városból"
             << endl;
    } else {
        cout << n << " nap nem volt a reklámban nem érintett városból rendelés"
             << endl;
    }
}

void feladat5() {
    cout << "5. feladat" << endl;

    int max = -1;
    for (const auto &adat : adatok) {
        if (adat.darab > max) {
            max = adat.darab;
        }
    }

    for (const auto &adat : adatok) {
        if (adat.darab == max) {
            cout << "A legnagyobb darabszám: " << max
                 << ", a rendelés napja: " << adat.nap << endl;
            return;
        }
    }
}

int osszes(string varos, int nap) {
    if (!(varos == "PL" || varos == "TV" || varos == "NR")) {
        cout << "Helytelen varos" << endl;
        return -1;
    }
    if (nap < 0 || nap > 30) {
        cout << "Helytelen nap" << endl;
        return -1;
    }
    int sum = 0;
    for (const auto &adat : adatok) {
        if (adat.varos == varos && adat.nap == nap) {
            sum += adat.darab;
        }
    }
    return sum;
}

void feladat7() {
    cout << "7. feladat" << endl;
    cout << "A rendelt termékek darabszáma a 21. napon PL: " << osszes("PL", 21)
         << " TV: " << osszes("TV", 21) << " NR: " << osszes("NR", 21) << endl;
}

void feladat8() {
    cout << "8. feladat" << endl;

    int pl10 = 0, pl20 = 0, pl30 = 0;
    int tv10 = 0, tv20 = 0, tv30 = 0;
    int nr10 = 0, nr20 = 0, nr30 = 0;

    for (const auto &adat : adatok) {
        if (adat.nap <= 10) {
            if (adat.varos == "PL") {
                pl10++;
            } else if (adat.varos == "TV") {
                tv10++;
            } else {
                nr10++;
            }
        } else if (adat.nap <= 20) {
            if (adat.varos == "PL") {
                pl20++;
            } else if (adat.varos == "TV") {
                tv20++;
            } else {
                nr20++;
            }
        } else if (adat.nap <= 30) {
            if (adat.varos == "PL") {
                pl30++;
            } else if (adat.varos == "TV") {
                tv30++;
            } else {
                nr30++;
            }
        }
    }

    cout << "Napok\t1..10\t11..20\t21..30" << endl;
    cout << "PL\t" << pl10 << "\t" << pl20 << "\t" << pl30 << endl;
    cout << "TV\t" << tv10 << "\t" << tv20 << "\t" << tv30 << endl;
    cout << "NR\t" << nr10 << "\t" << nr20 << "\t" << nr30 << endl;

    ofstream outfile("kampany.txt");
    if (!outfile.is_open()) {
        cout << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    outfile << "Napok\t1..10\t11..20\t21..30" << endl;
    outfile << "PL\t" << pl10 << "\t" << pl20 << "\t" << pl30 << endl;
    outfile << "TV\t" << tv10 << "\t" << tv20 << "\t" << tv30 << endl;
    outfile << "NR\t" << nr10 << "\t" << nr20 << "\t" << nr30 << endl;

    outfile.close();
}

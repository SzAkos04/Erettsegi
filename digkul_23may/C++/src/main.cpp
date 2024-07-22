#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Tabor {
    int kezd_ho, kezd_nap;
    int veg_ho, veg_nap;
    string erdek;
    string tema;
};
vector<Tabor> taborok;

void feladat1();
void feladat2();
void feladat3();
void feladat4();
int sorszam(int ho, int nap);
void feladat6();
void feladat7();

int main() {
    feladat1();
    feladat2();
    feladat3();
    feladat4();
    feladat6();
    feladat7();

    return 0;
}

void feladat1() {
    ifstream infile("taborok.txt");
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    Tabor t;
    while (infile >> t.kezd_ho >> t.kezd_nap >> t.veg_ho >> t.veg_nap >>
           t.erdek >> t.tema) {
        taborok.push_back(t);
    }

    infile.close();
}

void feladat2() {
    cout << "2. feladat" << endl;

    cout << "Az adatsorok száma: " << taborok.size() << endl;
    cout << "Az először rögzített tábor témája: " << taborok.front().tema
         << endl;
    cout << "Az utoljára rögzített tábor témája: " << taborok.back().tema
         << endl;
}

void feladat3() {
    cout << "3. feladat" << endl;

    for (const auto &tabor : taborok) {
        if (tabor.tema == "zenei") {
            cout << "Zenei tábor kezdődik " << tabor.kezd_ho << ". hó "
                 << tabor.kezd_nap << ". napján." << endl;
        }
    }
}

void feladat4() {
    cout << "4. feladat" << endl;

    int max = 0;
    for (const auto &tabor : taborok) {
        if ((int)tabor.erdek.length() > max) {
            max = tabor.erdek.length();
        }
    }

    cout << "Legnépszerűbbek:" << endl;
    for (const auto &tabor : taborok) {
        if ((int)tabor.erdek.length() == max) {
            cout << tabor.kezd_ho << " " << tabor.kezd_nap << " " << tabor.tema
                 << endl;
        }
    }
}

int sorszam(int ho, int nap) {
    int napok = 0;
    if (ho > 8 || (ho == 6 && nap > 30) || nap > 31) {
        cout << "Helytelen datum" << endl;
        return -1;
    }
    if (ho == 7) {
        napok += 30;
    } else if (ho == 8) {
        napok += 31 + 30;
    }
    napok += nap - 15;

    return napok;
}

void feladat6() {
    cout << "6. feladat" << endl;

    int ho, nap;
    cout << "hó: ";
    cin >> ho;
    if (ho < 6 || ho > 8) {
        cout << "Helytelen datum" << endl;
        return;
    }
    cout << "nap: ";
    cin >> nap;
    if (nap < 0 || nap > 31) {
        cout << "Helytelen datum" << endl;
        return;
    }

    int tart = 0;
    for (const auto &tabor : taborok) {
        if (sorszam(tabor.kezd_ho, tabor.kezd_nap) < sorszam(ho, nap) &&
            sorszam(tabor.veg_ho, tabor.veg_nap) > sorszam(ho, nap)) {
            tart++;
        }
    }
    cout << "Ekkor éppen " << tart << " tábor tart." << endl;
}

void feladat7() {
    cout << "7. feladat" << endl;

    char tanulo;
    cout << "Adja meg egy tanuló betűjelét: ";
    cin >> tanulo;

    ofstream outfile("egytanulo.txt");
    if (!outfile.is_open()) {
        cout << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    vector<Tabor> erdekelt;
    for (const auto &tabor : taborok) {
        for (const auto &ch : tabor.erdek) {
            if (ch == tanulo) {
                erdekelt.push_back(tabor);
                break;
            }
        }
    }
    if (erdekelt.empty()) {
        cout << "Helytelen diak." << endl;
        return;
    }

    sort(erdekelt.begin(), erdekelt.end(), [](const Tabor &a, const Tabor &b) {
        return sorszam(a.kezd_ho, a.kezd_nap) < sorszam(b.kezd_ho, b.kezd_nap);
    });

    for (const auto &tabor : erdekelt) {
        outfile << tabor.kezd_ho << "." << tabor.kezd_nap << "-" << tabor.veg_ho
                << "." << tabor.veg_nap << ". " << tabor.tema << endl;
    }

    outfile.close();

    for (const auto &tabor : erdekelt) {
        for (const auto &t : erdekelt) {
            if (sorszam(tabor.veg_ho, tabor.veg_nap) <
                sorszam(t.kezd_ho, t.kezd_nap)) {
                cout << "Nem mehet el mindegyik táborba." << endl;
                goto done;
            }
        }
    }
    cout << "Elmehet mindegyik táborba." << endl;
done:
    return;
}

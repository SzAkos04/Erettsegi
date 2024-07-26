#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Adat {
    string tanulo;
    int ora, perc;
    int kod;
};
vector<Adat> adatok;

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

void feladat1() {
    ifstream infile("bedat.txt");
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    Adat a;
    string ido;
    while (infile >> a.tanulo >> ido >> a.kod) {
        a.ora = stoi(ido.substr(0, 2));
        a.perc = stoi(ido.substr(3, 2));

        adatok.push_back(a);
    }

    infile.close();
}

void feladat2() {
    cout << "2. feladat" << endl;
    // elso belepes
    for (const auto &adat : adatok) {
        if (adat.kod == 1) {
            cout << "Az első tanuló " << (adat.ora < 10 ? "0" : "") << adat.ora
                 << ":" << (adat.perc < 10 ? "0" : "") << adat.perc
                 << "-kor lépett be a főkapun." << endl;
            break;
        }
    }

    for (int i = adatok.size() - 1; i >= 0; --i) {
        if (adatok.at(i).kod == 2) {
            cout << "Az utolsó tanuló " << (adatok.at(i).ora < 10 ? "0" : "")
                 << adatok.at(i).ora << ":"
                 << (adatok.at(i).perc < 10 ? "0" : "") << adatok.at(i).perc
                 << "-kor lépett ki a főkapun." << endl;
            break;
        }
    }
}

void feladat3() {
    ofstream outfile("kesok.txt");
    if (!outfile.is_open()) {
        cout << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    for (const auto &adat : adatok) {
        if (adat.kod == 1 && ((adat.ora == 7 && adat.perc > 50) ||
                              (adat.ora == 8 && adat.perc <= 15))) {
            outfile << (adat.ora < 10 ? "0" : "") << adat.ora << ":"
                    << (adat.perc < 10 ? "0" : "") << adat.perc << " "
                    << adat.tanulo << endl;
        }
    }

    outfile.close();
}

void feladat4() {
    cout << "4. feladat" << endl;
    int i = 0;
    for (const auto &adat : adatok) {
        if (adat.kod == 3) {
            i++;
        }
    }
    cout << "A menzán aznap " << i << " tanuló ebédelt." << endl;
}

void feladat5() {
    cout << "5. feladat" << endl;

    set<string> kolcsonzott;
    for (const auto &adat : adatok) {
        if (adat.kod == 4) {
            kolcsonzott.insert(adat.tanulo);
        }
    }
    cout << "Aznap " << kolcsonzott.size()
         << " tanuló kölcsönzött a könyvtárban." << endl;

    set<string> ebedelt;
    for (const auto &adat : adatok) {
        if (adat.kod == 3) {
            ebedelt.insert(adat.tanulo);
        }
    }
    cout << ((kolcsonzott > ebedelt) ? "Többen voltak, mint a menzán."
                                     : "Nem voltak többen, mint a menzán.")
         << endl;
}

void feladat6() {
    cout << "6. feladat" << endl;

    set<string> bent;
    for (const auto &adat : adatok) {
        if (adat.kod == 1) {
            if (adat.ora == 10 && adat.perc > 45) {
                break;
            }
            bent.insert(adat.tanulo);
        } else if (adat.kod == 2) {
            bent.erase(adat.tanulo);
        }
    }

    cout << "Az érintett tanulók:" << endl;
    for (const auto &adat : adatok) {
        for (const auto &tanulo : bent) {
            if (adat.kod == 1 && adat.ora == 10 && adat.perc > 50 &&
                adat.tanulo == tanulo) {
                cout << tanulo << " ";
            }
        }
    }
    cout << endl;
}

void feladat7() {
    cout << "7. feladat" << endl;

    string tanulo;
    cout << "Egy tanuló azonosítója=";
    cin >> tanulo;

    int erkez = -1, tavoz = -1;

    for (const auto &adat : adatok) {
        if (adat.kod == 1 && adat.tanulo == tanulo) {
            erkez = adat.ora * 60 + adat.perc;
            break;
        }
    }

    if (erkez == -1) {
        cout << "Ilyen azonosítójú tanuló aznap nem volt az iskolában." << endl;
        return;
    }

    for (int i = adatok.size() - 1; i >= 0; --i) {
        if (adatok.at(i).kod == 2 && adatok.at(i).tanulo == tanulo) {
            tavoz = adatok.at(i).ora * 60 + adatok.at(i).perc;
            break;
        }
    }

    int eltelt = tavoz - erkez;

    cout << "A tanuló érkezése és távozása között " << floor(eltelt / 60)
         << " óra " << eltelt % 60 << " perc telt el." << endl;
}

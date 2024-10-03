#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Adat {
    string nev;
    int honap;
    int nap;
    int sorszam;
    int hossz_min;
    string cim;
    string eszkozok;
};

vector<Adat> adatok;

void feladat1();
void feladat2();
void feladat3();
void feladat4();
void feladat5();
void feladat6();
void feladat7();
void feladat8();
void feladat9();

int main() {
    feladat1();
    feladat2();
    feladat3();
    feladat4();
    feladat5();
    feladat6();
    feladat7();
    feladat8();
    feladat9();

    return 0;
}

void feladat1() {
    ifstream infile("eloadasok.txt");
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    for (string line; getline(infile, line);) {
        Adat a;
        istringstream iss(line);
        getline(iss, a.nev, '\t');
        iss >> a.honap >> a.nap >> a.sorszam >> a.hossz_min;
        getline(iss >> ws, a.cim, '\t');
        getline(iss >> ws, a.eszkozok);

        adatok.push_back(a);
    }

    infile.close();
}

void feladat2() {
    cout << endl << "2. feladat" << endl;

    int nap = 100;  // current
    int napok = -1; // max

    for (const auto &adat : adatok) {
        if (adat.nap < nap) {
            nap = adat.nap;
        }
        if (adat.nap > napok) {
            napok = adat.nap;
        }
    }

    while (nap <= napok) {
        cout << "november " << nap << "." << endl;

        vector<Adat> a;
        for (const auto &adat : adatok) {
            if (adat.nap == nap) {
                a.push_back(adat);
            }
        }

        sort(a.begin(), a.end(), [](const Adat &a, const Adat &b) {
            return a.sorszam < b.sorszam;
        });

        for (const auto &adat : a) {
            cout << "\t" << adat.nev << ": " << adat.cim << endl;
        }

        nap++;
    }
}

void feladat3() {
    cout << endl << "3. feladat" << endl;

    int nap = 100;  // current
    int napok = -1; // max

    for (const auto &adat : adatok) {
        if (adat.nap < nap) {
            nap = adat.nap;
        }
        if (adat.nap > napok) {
            napok = adat.nap;
        }
    }

    for (; nap <= napok; nap++) {
        int percek = 0;
        for (const auto &adat : adatok) {
            if (adat.nap == nap) {
                percek += adat.hossz_min;
            }
        }
        cout << nap - 4 << ". nap: " << floor(percek / 60) << ":"
             << (percek % 60 < 10 ? "0" : "") << percek % 60 << endl;
    }
}

void feladat4() {
    cout << endl << "4. feladat" << endl;

    int max = -1;
    for (const auto &adat : adatok) {
        if (adat.nap == 6) {
            if (adat.hossz_min > max) {
                max = adat.hossz_min;
            }
        }
    }

    for (const auto &adat : adatok) {
        if (adat.nap == 6) {
            if (adat.hossz_min == max) {
                cout << adat.nev << " - " << adat.hossz_min << " perc" << endl;
            }
        }
    }
}

void feladat5() {
    cout << endl << "5. feladat" << endl;

    int nap = 100;  // current
    int napok = -1; // max

    for (const auto &adat : adatok) {
        if (adat.nap < nap) {
            nap = adat.nap;
        }
        if (adat.nap > napok) {
            napok = adat.nap;
        }
    }

    int ido;

    for (; nap <= napok; nap++) {
        ido = 480; // 8:00 percekben
        bool ebed = false;
        for (const auto &adat : adatok) {
            if (adat.nap == nap) {
                if (ido >= 720 && !ebed) { // 12:00 percekben
                    ido += 60;             // ebedszunet
                    ebed = true;
                }
                ido += adat.hossz_min + 20;
            }
        }
        cout << "november " << nap << ".: " << floor(ido / 60) << ":"
             << (ido % 60 < 10 ? "0" : "") << ido % 60 << endl;
    }
}

void feladat6() {
    cout << endl << "6. feladat" << endl;
    int nap = 100; // current
    for (const auto &adat : adatok) {
        if (adat.nap < nap) {
            nap = adat.nap;
        }
    }

    vector<Adat> a;
    for (const auto &adat : adatok) {
        if (adat.nap == nap + 2) {
            a.push_back(adat);
        }
    }

    sort(a.begin(), a.end(),
         [](const Adat &a, const Adat &b) { return a.sorszam < b.sorszam; });

    int ido = 480; // 8:00
    for (const auto &adat : a) {
        if (ido >= 720) {
            cout << "A harmadik napon az ebedszunet " << floor(ido / 60) << ":"
                 << (ido % 60 < 10 ? "0" : "") << ido % 60 << "-kor kezdodik."
                 << endl;
            break;
        }
        ido += adat.hossz_min + 20;
    }
}

void feladat7() {
    cout << endl << "7. feladat" << endl;

    struct Eloado {
        string nev;
        int n;
    };

    vector<Eloado> eloadok;

    for (const auto &adat : adatok) {
        bool found = false;

        for (auto &eloado : eloadok) {
            if (eloado.nev == adat.nev) {
                eloado.n++;
                found = true;
                break;
            }
        }

        if (!found) {
            eloadok.emplace_back(adat.nev, 1);
        }
    }

    for (const auto &eloado : eloadok) {
        cout << eloado.nev << " - ";
        if (eloado.n == 1) {
            cout << "Nem talaltam egyezo neveket." << endl;
        } else {
            cout << eloado.n << endl;
        }
    }
}

void feladat8() {
    cout << endl << "8. feladat" << endl;

    int nap, ora, perc;
    cout << "Nap: ";
    cin >> nap;
    if (nap < 5 || nap > 8) {
        cout << "Helytelen forma" << endl;
        return;
    }
    cout << "Ora: ";
    cin >> ora;
    if (ora < 0 || ora > 23) {
        cout << "Helytelen forma" << endl;
        return;
    }
    cout << "Perc: ";
    cin >> perc;
    if (perc < 0 || perc > 59) {
        cout << "Helytelen forma" << endl;
        return;
    }

    int percek = ora * 60 + perc;

    if (percek < 480) {
        cout << "Meg nem kezdodott el" << endl;
        return;
    }

    vector<Adat> a;
    for (const auto &adat : adatok) {
        if (adat.nap == nap) {
            a.push_back(adat);
        }
    }

    sort(a.begin(), a.end(),
         [](const Adat &a, const Adat &b) { return a.sorszam < b.sorszam; });

    int ido = 480; // 8:00 percekben
    int ebed_kezd = -1, ebed_veg = -1;
    int vita_kezd = -1, vita_veg = -1;
    int eloadas_kezd = -1, eloadas_veg = -1;
    bool ebed = false;
    for (const auto &adat : adatok) {
        if (adat.nap == nap) {
            if (ido >= 720 && !ebed) { // 12:00 percekben
                ebed_kezd = ido;
                ido += 60;
                ebed_veg = ido;
                ebed = true;
            }
            eloadas_kezd = ido;
            ido += adat.hossz_min;
            eloadas_veg = ido;
            if (percek >= eloadas_kezd && percek <= eloadas_veg) {
                cout << "Eloadas" << endl;
                return;
            }

            vita_kezd = ido;
            ido += 20;
            vita_veg = ido;
            if (percek > vita_kezd && percek <= vita_veg) {
                cout << "Vita" << endl;
                return;
            }
        }
    }

    if (percek > ido) {
        cout << "Mar veget ert" << endl;
        return;
    } else if (percek > ebed_kezd && percek < ebed_veg) {
        cout << "Ebedszunet" << endl;
        return;
    }
}

void feladat9() {
    ofstream outfile("idorend.txt");

    int nap = 100;  // current
    int napok = -1; // max

    for (const auto &adat : adatok) {
        if (adat.nap < nap) {
            nap = adat.nap;
        }
        if (adat.nap > napok) {
            napok = adat.nap;
        }
    }

    while (nap <= napok) {
        outfile << "november " << nap << "." << endl;

        int ido = 480;

        vector<Adat> a;
        for (const auto &adat : adatok) {
            if (adat.nap == nap) {
                a.push_back(adat);
            }
        }

        sort(a.begin(), a.end(), [](const Adat &a, const Adat &b) {
            return a.sorszam < b.sorszam;
        });

        bool ebed = false;
        for (const auto &adat : a) {
            int start;
            if (ido >= 720 && !ebed) {
                start = ido;
                ido += 60; // ebed
                ebed = true;
                outfile << floor(start / 60) << ":"
                        << (start % 60 < 10 ? "0" : "") << start % 60 << "-"
                        << floor(ido / 60) << ":" << (ido % 60 < 10 ? "0" : "")
                        << ido % 60 << " Ebed" << endl;
            }
            start = ido;
            ido += adat.hossz_min;
            outfile << floor(start / 60) << ":" << (start % 60 < 10 ? "0" : "")
                    << start % 60 << "-" << floor(ido / 60) << ":"
                    << (ido % 60 < 10 ? "0" : "") << ido % 60 << " " << adat.nev
                    << ": " << adat.cim << " " << "(" << adat.eszkozok << ")"
                    << endl;
            start = ido;
            ido += 20; // vita
            outfile << floor(start / 60) << ":" << (start % 60 < 10 ? "0" : "")
                    << start % 60 << "-" << floor(ido / 60) << ":"
                    << (ido % 60 < 10 ? "0" : "") << ido % 60 << " Vita"
                    << endl;
        }
        outfile << "\n";

        nap++;
    }

    outfile.close();
}

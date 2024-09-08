#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct adat {
    string telepules;
    int ora, perc;
    string szel;
    int ho;
};

vector<adat> adatok;

void feladat1();
void feladat2();
void feladat3();
void feladat4();
void feladat5();
void feladat6();

int main() {
    feladat1();
    feladat2();
    feladat3();
    feladat4();
    feladat5();
    feladat6();

    return 0;
}

void feladat1() {
    ifstream infile("tavirathu13.txt");
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    adat a;
    string ido;
    while (infile >> a.telepules >> ido >> a.szel >> a.ho) {
        a.ora = stoi(ido.substr(0, 2));
        a.perc = stoi(ido.substr(2, 2));
        adatok.push_back(a);
    }

    infile.close();
}

void feladat2() {
    cout << "2. feladat" << endl;

    string kod;
    cout << "Adja meg egy település kódját! Település: ";
    cin >> kod;

    for (int i = adatok.size() - 1; i >= 0; --i) {
        if (adatok[i].telepules == kod) {
            cout << "Az utolsó mérési adat a megadott településről "
                 << (adatok[i].ora < 10 ? "0" : "") << adatok[i].ora << ":"
                 << (adatok[i].perc < 10 ? "0" : "") << adatok[i].perc
                 << "-kor érkezett." << endl;
            break;
        }
    }
}

void feladat3() {
    cout << "3. feladat" << endl;

    int min = 100;
    int max = -1;

    for (const auto &adat : adatok) {
        if (adat.ho < min) {
            min = adat.ho;
        }
        if (adat.ho > max) {
            max = adat.ho;
        }
    }

    for (const auto &adat : adatok) {
        if (adat.ho == min) {
            cout << "A legalacsonyabb hőmérséklet: " << adat.telepules << " "
                 << (adat.ora < 10 ? "0" : "") << adat.ora << ":"
                 << (adat.perc < 10 ? "0" : "") << adat.perc << " " << adat.ho
                 << " fok." << endl;
            break;
        }
    }
    for (const auto &adat : adatok) {
        if (adat.ho == max) {
            cout << "A legmagasabb hőmérséklet: " << adat.telepules << " "
                 << (adat.ora < 10 ? "0" : "") << adat.ora << ":"
                 << (adat.perc < 10 ? "0" : "") << adat.perc << " " << adat.ho
                 << " fok." << endl;
            break;
        }
    }
}

void feladat4() {
    cout << "4. feladat" << endl;

    bool szelcsendes = true;

    for (const auto &adat : adatok) {
        if (adat.szel == "00000") {
            szelcsendes = false;
            cout << adat.telepules << " " << (adat.ora < 10 ? "0" : "")
                 << adat.ora << ":" << (adat.perc < 10 ? "0" : "") << adat.perc
                 << endl;
        }
    }

    if (szelcsendes) {
        cout << "Nem volt szélcsend a mérések idején." << endl;
    }
}

void feladat5() {
    cout << "5. feladat" << endl;

    set<string> telepulesek;
    for (const auto &adat : adatok) {
        telepulesek.insert(adat.telepules);
    }

    for (const auto &telepules : telepulesek) {
        cout << telepules << " ";

        vector<adat> hok;
        for (const auto &adat : adatok) {
            if (adat.telepules == telepules &&
                (adat.ora == 1 || adat.ora == 7 || adat.ora == 13 ||
                 adat.ora == 19)) {

                hok.push_back(adat);
            }
        }

        bool egy = false, het = false, tizenharom = false, tizenkilenc = false;
        for (const auto &adat : hok) {
            if (adat.ora == 1) {
                egy = true;
            } else if (adat.ora == 7) {
                het = true;
            } else if (adat.ora == 13) {
                tizenharom = true;
            } else if (adat.ora == 19) {
                tizenkilenc = true;
            }
        }

        if (egy && het && tizenharom && tizenkilenc) {
            int ho_sum = 0;
            for (const auto &adat : hok) {
                ho_sum += adat.ho;
            }

            double kozep_ho = static_cast<double>(ho_sum) / hok.size();

            cout << "Középhőmérséklet: " << round(kozep_ho) << "; ";
        } else {
            cout << "NA; ";
        }

        int min = 100, max = -1;
        for (const auto &adat : adatok) {
            if (adat.telepules == telepules) {
                if (adat.ho < min) {
                    min = adat.ho;
                }
                if (adat.ho > max) {
                    max = adat.ho;
                }
            }
        }

        cout << "Hőmérséklet-ingadozás: " << max - min << endl;
    }
}

void feladat6() {
    cout << "6. feladat" << endl;

    set<string> telepulesek;
    for (const auto &adat : adatok) {
        telepulesek.insert(adat.telepules);
    }

    for (const auto &telepules : telepulesek) {
        ofstream outfile(telepules + ".txt");
        if (!outfile.is_open()) {
            cout << "Nem sikerult megnyitni a fajlt!" << endl;
            return;
        }

        outfile << telepules << endl;

        for (const auto &adat : adatok) {
            if (adat.telepules == telepules) {
                outfile << (adat.ora < 10 ? "0" : "") << adat.ora << ":"
                        << (adat.perc < 10 ? "0" : "") << adat.perc << " ";

                int erosseg = stoi(adat.szel.substr(3, 2));
                for (int i = 0; i < erosseg; ++i) {
                    outfile << "#";
                }
                outfile << endl;
            }
        }

        outfile.close();
    }
    cout << "A fájlok elkészültek." << endl;
}

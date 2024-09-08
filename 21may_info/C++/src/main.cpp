#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<int> adatok;
int input;

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
    cout << "1. feladat" << endl;

    ifstream infile("melyseg.txt");
    if (!infile.is_open()) {
        cout << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    int i;
    while (infile >> i) {
        adatok.push_back(i);
    }

    infile.close();

    cout << "A fájl adatainak száma: " << adatok.size() << endl;
}

void feladat2() {
    cout << endl;
    cout << "2. feladat" << endl;

    cout << "Adjon meg egy távolságértéket! ";
    cin >> input;
    input--; // 1-es index

    cout << "Ezen a helyen a felszín " << adatok[input] << " méter mélyen van."
         << endl;
}

void feladat3() {
    cout << endl;
    cout << "3. feladat" << endl;

    int nullak = 0;
    for (const auto &adat : adatok) {
        if (adat == 0) {
            nullak++;
        }
    }

    cout << "Az érintetlen terület aránya "
         << ((round((double)nullak / adatok.size() * 10000.0) / 100)) << "%."
         << endl;
}

void feladat4() {
    ofstream outfile("godrok.txt");
    if (!outfile.is_open()) {
        cout << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    int elso;
    for (elso = 0; adatok[elso] == 0; ++elso)
        ;

    int len = adatok.size();
    for (int i = elso; i < len; ++i) {
        if (adatok[i] == 0) {
            while (adatok[i + 1] == 0) {
                i++;
            }
            outfile << endl;
        } else {
            outfile << adatok[i] << " ";
        }
    }

    outfile.close();
}

void feladat5() {
    cout << endl;
    cout << "5. feladat" << endl;

    int godrok = 0;

    int len = adatok.size();
    for (int i = 1; i < len; ++i) {
        if (adatok[i - 1] == 0 && adatok[i] != 0) {
            godrok++;
        }
    }

    cout << "A gödrök száma: " << godrok << endl;
}

void feladat6() {
    cout << endl;
    cout << "6. feladat" << endl;

    if (adatok[input] == 0) {
        cout << "Az adott helyen nincs gödör." << endl;
        return;
    }

    int kezd = input;
    int veg = input;

    {
        cout << "a)" << endl;

        int len = adatok.size();

        while (kezd >= 0 && adatok[kezd - 2] != 0) {
            kezd--;
        }
        while (veg < len && adatok[veg] != 0) {
            veg++;
        }

        cout << "A gödör kezdete: " << kezd << " méter, a gödör vége: " << veg
             << " méter." << endl;
    }

    {
        cout << "b)" << endl;

        int max = -1;

        for (int i = kezd - 1; i <= veg; ++i) {
            if (adatok[i] > max) {
                max = adatok[i];
            }
        }

        bool folyamatos = true;

        for (int i = kezd - 1; adatok[i] != max; ++i) {
            if (adatok[i] > adatok[i + 1] && adatok[i + 1] != max) {
                folyamatos = false;
                break;
            }
        }

        for (int i = veg; adatok[i] != max; --i) {
            if (adatok[i] < adatok[i - 1] && adatok[i - 1] != max) {
                folyamatos = false;
                break;
            }
        }

        cout << (folyamatos ? "Folyamatosan mélyül."
                            : "Nem mélyül folyamatosan.")
             << endl;
    }

    {
        cout << "c)" << endl;

        int max = -1;
        for (int i = kezd - 1; i <= veg; ++i) {
            if (adatok[i] > max) {
                max = adatok[i];
            }
        }

        cout << "A legnagyobb mélysége " << max << " méter." << endl;
    }

    {
        cout << "d)" << endl;

        int ter = 0;
        for (int i = kezd - 1; i <= veg; ++i) {
            ter += adatok[i];
        }

        ter *= 10;

        cout << "A térfogata " << ter << " m^3." << endl;
    }

    {
        cout << "e)" << endl;

        int viz = 0;
        // idk why this is not inclusive, but it is not
        for (int i = kezd - 1; i < veg; ++i) {
            viz += adatok[i] - 1;
        }

        viz *= 10;

        cout << "A vízmennyiség " << viz << " m^3." << endl;
    }
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> osvenyek;
vector<int> dobasok;

int osveny_input, jatekosok;

void feladat1();
void feladat2();
void feladat3();
void feladat4();

int main() {
    feladat1();
    feladat2();
    feladat3();
    feladat4();
    
    return 0;
}


void feladat1() {
    ifstream infile1("dobasok.txt");
    if (!infile1.is_open()) {
        cerr << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    int dobas;
    while (infile1 >> dobas) {
        dobasok.push_back(dobas);
    }

    infile1.close();
    
    ifstream infile2("osvenyek.txt");
    if (!infile2.is_open()) {
        cerr << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }
    
    string osveny;
    while (infile2 >> osveny) {
        osvenyek.push_back(osveny);
    }

    infile2.close();
}

void feladat2() {
    cout << "2. feladat" << endl;
    cout << "A dobások száma: " << dobasok.size() << endl;
    cout << "Az ösvények száma: " << osvenyek.size() << endl;

    cout << endl;
}

void feladat3() {
    cout << "3. feladat" << endl;

    int max = -1;
    for (const auto &osveny : osvenyek) {
        if ((int)osveny.length() > max) {
            max = osveny.length();
        }
    }

    for (size_t i = 0; i < osvenyek.size(); ++i) {
        if ((int)osvenyek[i].length() == max) {
            // egyes index
            cout << "Az egyik leghosszabb a(z) " << i + 1 << ". ösvény, hossza: " << max << endl << endl;
            return;
        }
    }
}

void feladat4() {
    cout << "4. feladat" << endl;

    do {
        cout << "Adja meg egy ösvény sorszámát! ";
        cin >> osveny_input;
    } while (osveny_input < 1 || osveny_input > (int)osvenyek.size() + 1);
    osveny_input--; // egyes index
    do {
        cout << "Adja meg a játékosok számát! ";
        cin >> jatekosok;
    } while (jatekosok < 2 || jatekosok > 5);

    cout << endl;
}
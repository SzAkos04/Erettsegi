#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#define SOROK 360
#define OSZLOPOK 640

struct Pixel {
    int r, g, b;
};

vector<Pixel> pixelek;

void feladat1();
void feladat2();
void feladat3();
void feladat4();
bool hatar(int sor, int elteres);
void feladat6();

int main() {
    feladat1();
    feladat2();
    feladat3();
    feladat4();
    feladat6();

    return 0;
}

void feladat1() {
    ifstream infile("kep.txt");
    if (!infile.is_open()) {
        cerr << "Nem sikerult megnyitni a fajlt!" << endl;
        return;
    }

    Pixel p;
    while (infile >> p.r >> p.g >> p.b) {
        pixelek.push_back(p);
    }

    infile.close();
}

void feladat2() {
    cout << endl << "2. feladat" << endl;
    int sor, oszlop;
    cout << "Kérem egy képpont adatait!" << endl;
    cout << "Sor: ";
    cin >> sor;
    sor--; // 1-es index
    cout << "Oszlop: ";
    cin >> oszlop;
    oszlop--; // 1-es index

    Pixel p = pixelek.at(sor * OSZLOPOK + oszlop);
    cout << "A képpont színe RGB(" << p.r << "," << p.g << "," << p.b << ")"
         << endl;
}

void feladat3() {
    cout << endl << "3. feladat" << endl;
    int n = 0;
    for (const auto &pixel : pixelek) {
        if (pixel.r + pixel.g + pixel.b > 600) {
            n++;
        }
    }
    cout << "A világos képpontok száma: " << n << endl;
}

void feladat4() {
    cout << endl << "4. feladat" << endl;

    int min = 255 * 3;
    for (const auto &pixel : pixelek) {
        if (pixel.r + pixel.g + pixel.b < min) {
            min = pixel.r + pixel.g + pixel.b;
        }
    }
    cout << "A legsötétebb pont RGB összege: " << min << endl;

    cout << "A legsötétebb pixelek színe:" << endl;
    for (const auto &pixel : pixelek) {
        if (pixel.r + pixel.g + pixel.b == min) {
            cout << "RGB(" << pixel.r << "," << pixel.g << "," << pixel.b << ")"
                 << endl;
        }
    }
}

bool hatar(int sor, int elteres) {
    sor--; // 1-es index
    for (int i = 0; i < OSZLOPOK - 1; i++) {
        Pixel p1 = pixelek.at(sor * OSZLOPOK + i);
        Pixel p2 = pixelek.at(sor * OSZLOPOK + i + 1);
        if (abs(p1.b - p2.b) > elteres) {
            return true;
        }
    }
    return false;
}

void feladat6() {
    cout << endl << "6. feladat" << endl;

    int fent = 1;
    while (!hatar(fent, 10)) {
        fent++;
    }
    cout << "A felhő legfelső sora: " << fent << endl;
    int lent = SOROK;
    while (!hatar(lent, 10)) {
        lent--;
    }
    cout << "A felhő legalsó sora: " << lent << endl;
}

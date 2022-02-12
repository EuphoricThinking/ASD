//
// Created by heheszek on 12.02.2022.
//
#include <iostream>
#include <vector>
#include <cmath>

using std::cout;
using std::endl;
using std::cin;
using std::pair;
using std::vector;

using std::make_pair;
using std::max;
using zadanie = pair<int, int>;
using std::abs;

using polecenia = vector<zadanie>;
using wierzchołki = vector<int>;
using odleglosc = vector<int>;
using macierz = vector<vector<int>>;



void inicjujWierzcholki(int ileElementow, wierzchołki &w) {
    for (int i = 0; i < ileElementow + 1; i++) {
        w.push_back(-1);
    }
}

void inicjujGlebokosc(int ileElementow, odleglosc &w) {
    for (int i = 0; i < ileElementow + 1; i++) {
        w.push_back(-1);
    }
}

void printRes(int &liczbaPolanek, int &liczbaPolecen,
              wierzchołki &rodzic, wierzchołki &prawy,
              wierzchołki &lewy, polecenia &pol) {
    cout << liczbaPolanek << endl;

    for (int i = 0; i < liczbaPolanek + 1; i++) {
        cout  << lewy[i] << " " << prawy[i] << endl;
    }
    cout << "\n\n";

    for (int i = 0; i < liczbaPolanek + 1; i++) {
        cout << "r " << rodzic[i] << endl;
    }

    cout << liczbaPolecen << endl;
    for (int i = 0; i < liczbaPolecen; i++) {
        zadanie p = pol[i];

        cout << p.first << " " << p.second << endl;
    }
}

void wczytajWejsceStworzTablice(int &liczbaPolanek, int &liczbaPolecen,
                                wierzchołki &rodzic, wierzchołki &prawy,
                                wierzchołki &lewy, polecenia &pol) {

    cin >> liczbaPolanek;
    inicjujWierzcholki(liczbaPolanek + 1, rodzic);
    inicjujWierzcholki(liczbaPolanek + 1, prawy);
    inicjujWierzcholki(liczbaPolanek + 1, lewy);

    int prawe_dziecko;
    int lewe_dziecko;
    rodzic[1] = 1;
    for (int i = 1; i < liczbaPolanek + 1; i++) {
        cin >> lewe_dziecko >> prawe_dziecko;
        prawy[i] = prawe_dziecko;
        lewy[i] = lewe_dziecko;

        if (prawe_dziecko != -1) {
            rodzic[prawe_dziecko] = i;
        }

        if (lewe_dziecko != -1) {
            rodzic[lewe_dziecko] = i;
        }
    }

    cin >> liczbaPolecen;
    int skad;
    int dokad;

    for (int i = 0; i < liczbaPolecen; i++) {
        cin >> skad >> dokad;
        pol.push_back(make_pair(skad, dokad));
    }
}

void wyznaczGlebokosc(const wierzchołki& prawy, const wierzchołki& lewy,
                      odleglosc& glebokosc, int akt_gl, int nr_wierzcholka) {
    if (nr_wierzcholka != -1) {
        glebokosc[nr_wierzcholka] = akt_gl;
        wyznaczGlebokosc(prawy, lewy, glebokosc, akt_gl + 1,
                             prawy[nr_wierzcholka]);
        wyznaczGlebokosc(prawy, lewy, glebokosc, akt_gl + 1,
                         lewy[nr_wierzcholka]);
    }
}

void printVec(const vector<int>& v) {
    cout << "gl";
    for (int i: v) {
        cout << " "  << i;
    }
    cout << endl;
}
int main() {
    polecenia pol;
    wierzchołki rodzic;
    wierzchołki prawy;
    wierzchołki lewy;
    int liczbaPolanek;
    int liczbaPolecen;

    wczytajWejsceStworzTablice(liczbaPolanek, liczbaPolecen, rodzic, prawy,
                               lewy, pol);
    printRes(liczbaPolanek, liczbaPolecen, rodzic, prawy,
             lewy, pol);

    odleglosc glebokosc(liczbaPolanek + 1, -1);
    wyznaczGlebokosc(prawy, lewy, glebokosc, 0, 1);
    printVec(glebokosc);
}

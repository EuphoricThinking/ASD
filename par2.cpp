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

typedef struct odlWierzch {
    int odl;
    int wierzch;
} odlWierzch;

using polecenia = vector<zadanie>;
using wierzchołki = vector<int>;
using odleglosc = vector<int>;
using macierz = vector<vector<int>>;
using wykaz_odlWierzch = vector<odlWierzch>;



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

odlWierzch porownajNajdalszeWierzcholki(odlWierzch kand1, odlWierzch kand2) {
    if (kand1.odl > kand2.odl) {
        return kand1;
    }

    return kand2;
}

odlWierzch stworzOdlWierzch(int odl, int wierzch) {
    odlWierzch nowy;
    nowy.odl = odl;
    nowy.wierzch = wierzch;

    return nowy;
}

odlWierzch wyznaczGlebokoscOrazNajdalszyDol(const wierzchołki& prawy, const wierzchołki& lewy,
                                            odleglosc& glebokosc, int akt_gl, int nr_wierzcholka,
                                            wykaz_odlWierzch& najdalszyDol) {
    if (nr_wierzcholka != -1) {
        glebokosc[nr_wierzcholka] = akt_gl;

        odlWierzch prawyNajd = wyznaczGlebokoscOrazNajdalszyDol(prawy, lewy,
                                                                glebokosc,
                                                                akt_gl + 1,
                                                                prawy[nr_wierzcholka],
                                                                najdalszyDol);
        odlWierzch lewyNajd = wyznaczGlebokoscOrazNajdalszyDol(prawy, lewy,
                                                               glebokosc,
                                                               akt_gl + 1,
                                                               lewy[nr_wierzcholka],
                                                               najdalszyDol);

        if (prawyNajd.odl == -1 && lewyNajd.odl == -1) {
            najdalszyDol[nr_wierzcholka] = stworzOdlWierzch(0, nr_wierzcholka);

            return stworzOdlWierzch(1, nr_wierzcholka);
        }
        else {
            odlWierzch najdalszy = porownajNajdalszeWierzcholki(prawyNajd, lewyNajd);
            najdalszyDol[nr_wierzcholka] = najdalszy;
            najdalszy.odl = najdalszy.odl + 1;

            return najdalszy;
        }
    }
    else {
        return stworzOdlWierzch(-1, -1);
    }
}

void printVec(const vector<int>& v) {
    cout << "gl";
    for (int i: v) {
        cout << " "  << i;
    }
    cout << endl;
}

void printOdlWierzch(const wykaz_odlWierzch & odlw) {
    for (odlWierzch ow: odlw) {
        cout << ow.wierzch << " gl: " << ow.odl << endl;
    }
}

int znajdzRodzenstwo(int dziecko, int rodzic, const wierzchołki & prawy,
                     const wierzchołki & lewy) {
    int praweD = prawy[rodzic];
    if (praweD != dziecko) return praweD;

    return lewy[rodzic];
}

void stworzNajdalszyGora(const wierzchołki & rodzice, const wierzchołki & prawy,
                         const wierzchołki & lewy, wykaz_odlWierzch & najdalszyGora,
                         const wykaz_odlWierzch & najdalszyDol, int nr_wierzcholka) {
    if (nr_wierzcholka == 1) {
        najdalszyGora[nr_wierzcholka] = stworzOdlWierzch(0, nr_wierzcholka);

        stworzNajdalszyGora(rodzice, prawy, lewy, najdalszyGora, najdalszyDol,
                            prawy[nr_wierzcholka]);
        stworzNajdalszyGora(rodzice, prawy, lewy, najdalszyGora, najdalszyDol,
                            lewy[nr_wierzcholka]);
    }
    else if (nr_wierzcholka != -1) {
        int rodzic = rodzice[nr_wierzcholka];
        int rodzenstwo = znajdzRodzenstwo(nr_wierzcholka, rodzic, prawy, lewy);
        odlWierzch odlegloscRodzenstwoDol = (rodzenstwo == -1) ?
                                         stworzOdlWierzch(-1, -1) :
                                         stworzOdlWierzch(
                                                 najdalszyDol[rodzenstwo].odl + 2,
                                                 najdalszyDol[rodzenstwo].wierzch);

        odlWierzch odlegloscRodzicGora = stworzOdlWierzch(najdalszyGora[rodzic].odl + 1,
                                                          najdalszyGora[rodzic].wierzch);

        najdalszyGora[nr_wierzcholka] = porownajNajdalszeWierzcholki(odlegloscRodzenstwoDol,
                                                     odlegloscRodzicGora);

        stworzNajdalszyGora(rodzice, prawy, lewy, najdalszyGora, najdalszyDol,
                            prawy[nr_wierzcholka]);
        stworzNajdalszyGora(rodzice, prawy, lewy, najdalszyGora, najdalszyDol,
                            lewy[nr_wierzcholka]);
    }
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
    wykaz_odlWierzch najdalszyDol(liczbaPolanek + 1);
    odlWierzch najdalszy = wyznaczGlebokoscOrazNajdalszyDol(prawy, lewy,
                                                            glebokosc, 0, 1,
                                                            najdalszyDol);
    printVec(glebokosc);
    printOdlWierzch(najdalszyDol);

    wykaz_odlWierzch najdalszyGora(liczbaPolanek + 1);
    stworzNajdalszyGora(rodzic, prawy, lewy, najdalszyGora, najdalszyDol, 1);
    cout << endl;
    printOdlWierzch(najdalszyGora);
}

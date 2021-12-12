//
// Created by heheszek on 12.12.2021.
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
using glebokiLisc = pair<int, int>;

using polecenia = vector<pair<int, int>>;
using wierzchołki = vector<int>;
using odleglosc = vector<int>;
using macierz = vector<vector<int>>;


void inicjujWierzcholki(int ileElementow, wierzchołki &w) {
    for (int i = 0; i < ileElementow + 1; i++) {
        w.push_back(-1);
    }
}

/*void inicjujPolecenia(int ileElementow, polecenia pol) {
    for (int i = 0; i < ileElementow; i++) {
        pol.push_back(make_pair(-1, -1));
    }
} */

void inicjujGlebokosc(int ileElementow, odleglosc &w) {
    for (int i = 0; i < ileElementow + 1; i++) {
        w.push_back(-1);
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
   // inicjujPolecenia(liczbaPolecen, pol);
    int skad;
    int dokad;

    for (int i = 0; i < liczbaPolecen; i++) {
        cin >> skad >> dokad;
        pol.push_back(make_pair(skad, dokad));
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
        pair<int, int> p = pol[i];

         cout << p.first << " " << p.second << endl;
    }
}

int znajdzGlebokosc(wierzchołki &lewy, wierzchołki &prawy, odleglosc &glebokosc,
            wierzchołki &najdalszeWPoddrzewie, int nrWierzcholka, int gl, odleglosc &odlegloscDol) {
            glebokosc[nrWierzcholka] = gl;

            if (lewy[nrWierzcholka] == -1 && prawy[nrWierzcholka] == -1) {
                najdalszeWPoddrzewie[nrWierzcholka] = nrWierzcholka;
                return -1;
            }

            int gLewy = -2;
            int gPrawy = -2;

            if (lewy[nrWierzcholka] != -1) {
                gLewy = znajdzGlebokosc(lewy, prawy, glebokosc, najdalszeWPoddrzewie,
                          lewy[nrWierzcholka], gl + 1, odlegloscDol);
            }

            if (prawy[nrWierzcholka] != -1) {
                gPrawy = znajdzGlebokosc(lewy, prawy, glebokosc, najdalszeWPoddrzewie,
                                         prawy[nrWierzcholka], gl + 1, odlegloscDol);
            }

            if (gLewy > gPrawy) {
                najdalszeWPoddrzewie[nrWierzcholka] =
                        najdalszeWPoddrzewie[lewy[nrWierzcholka]];
                odlegloscDol[nrWierzcholka] = gLewy;
            } else {
                najdalszeWPoddrzewie[nrWierzcholka] =
                        najdalszeWPoddrzewie[prawy[nrWierzcholka]];
                odlegloscDol[nrWierzcholka] = gPrawy;
            }

            return max(gLewy, gPrawy) + 1;
}

void odlegloscGora(int nrWierzcholka, wierzchołki &prawy, wierzchołki &lewy,
                   int odlegloscNajdalszeRodzic, wierzchołki &rodzic,
                   odleglosc &glebokosc, odleglosc &odlegloscDol,
                   odleglosc &najdalsze, wierzchołki &najdalszeWierzchołki,
                   bool czyPrawy, wierzchołki &najdalszyDol) {
    if (nrWierzcholka == -1) {
        return;
    }

    if (nrWierzcholka == 1) {
        int glPrawy = glebokosc[prawy[nrWierzcholka]];
        int glLewy = glebokosc[lewy[nrWierzcholka]];
        if (glLewy > glPrawy) {
            najdalsze[nrWierzcholka] = glLewy;
            najdalszeWierzchołki[nrWierzcholka] = lewy[nrWierzcholka];
        } else {
            najdalsze[nrWierzcholka] = glPrawy;
            najdalszeWierzchołki[nrWierzcholka] = prawy[nrWierzcholka];
        }

        odlegloscGora(prawy[nrWierzcholka], prawy, lewy, glLewy + 1,
                      rodzic, glebokosc, odlegloscDol, najdalsze, najdalszeWierzchołki, true, najdalszyDol);

        odlegloscGora(lewy[nrWierzcholka], prawy, lewy, glPrawy + 1,
                      rodzic, glebokosc, odlegloscDol, najdalsze, najdalszeWierzchołki, false, najdalszyDol);
    }    else {
        int rodzenstwo = (czyPrawy) ? lewy[rodzic[nrWierzcholka]] : prawy[rodzic[nrWierzcholka]];
        int odlRodzenstwo = odlegloscDol[rodzenstwo] + 2;
        int odlDol = odlegloscDol[nrWierzcholka];
        int rodzicWierzcholka = rodzic[nrWierzcholka];

        if (odlDol > odlegloscNajdalszeRodzic && odlDol > odlRodzenstwo) {
            najdalsze[nrWierzcholka] = odlDol;
            najdalszeWierzchołki[nrWierzcholka] = najdalszyDol[nrWierzcholka];
        } else if (odlRodzenstwo > odlDol && odlRodzenstwo > odlegloscNajdalszeRodzic) {
            najdalsze[nrWierzcholka] = odlRodzenstwo;
            najdalszeWierzchołki[nrWierzcholka] = najdalszyDol[rodzenstwo];
        } else {
            najdalsze[nrWierzcholka] = najdalsze[rodzicWierzcholka];
            najdalszeWierzchołki[nrWierzcholka] = najdalszeWierzchołki[rodzicWierzcholka];
        }

        odlegloscGora(prawy[nrWierzcholka], prawy, lewy, najdalsze[nrWierzcholka] + 1,
                      rodzic, glebokosc, odlegloscDol, najdalsze, najdalszeWierzchołki, true, najdalszyDol);

        odlegloscGora(lewy[nrWierzcholka], prawy, lewy, najdalsze[nrWierzcholka] + 1,
                      rodzic, glebokosc, odlegloscDol, najdalsze, najdalszeWierzchołki, false, najdalszyDol);
    }
}

void inicjalizujMacierz(int liczbaPolanek, macierz &m, int przodkowie) {

    for (int i = 0; i < liczbaPolanek + 1; i++) {
        vector<int> v;
        m.push_back(v);

        for (int j = 0; j < przodkowie + 1; j++) {
            m[i].push_back(-1);
        }
    }
}

void stworzJumpingPointers(int liczbaPolanek, int przodkowie, wierzchołki &rodzice,
                           macierz &jumps) {
    for (int i = 0; i < liczbaPolanek + 1; i++) {
        jumps[i][0] = rodzice[i];
    }

    for (int i = 0; i < liczbaPolanek + 1; i++) {
        for (int j = 1; j < przodkowie; j++) {
            jumps[i][j] = jumps[jumps[i][j - 1]][j - 1];
        }
    }
}

int skoczO_K(int k, int glebszy, macierz jumps, int przodkowie) {
    for (int i = 0; i < przodkowie; i++) {
        if (k & (1 << i)) {
            glebszy = jumps[glebszy][i];
        }
    }

    return glebszy;
}

int znajdzLCA(int w1, int w2, macierz jumps, int przodkowie) {
    for (int i = przodkowie - 1; i >= 0; i--) {
        if (jumps[w1][i] != jumps[w2][i]) {
            w1 = jumps[w1][i];
            w2 = jumps[w2][i];
        }
    }

    return jumps[w1][0];
}


int main(){
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

    odleglosc glebokosc;
    odleglosc odlegloscDol;
    odleglosc najdalsze;
    inicjujGlebokosc(liczbaPolanek, glebokosc);
    inicjujGlebokosc(liczbaPolanek, odlegloscDol);
    inicjujGlebokosc(liczbaPolanek, najdalsze);

    wierzchołki najdalszeWPoddrzewie;
    wierzchołki najdalszeWierzchołki;
    inicjujWierzcholki(liczbaPolanek, najdalszeWierzchołki);
    inicjujWierzcholki(liczbaPolanek, najdalszeWPoddrzewie);
    int bezuzyteczne = znajdzGlebokosc(lewy, prawy, glebokosc,
                                           najdalszeWPoddrzewie, 1,
                                           0, odlegloscDol);

    odlegloscGora(1, prawy, lewy, 0, rodzic, glebokosc, odlegloscDol,
            najdalsze, najdalszeWierzchołki,
            false, najdalszeWPoddrzewie);

    int liczbaPrzodkow = (int)ceil(log2(liczbaPolanek));

    return 0;
}

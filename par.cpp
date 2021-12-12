//
// Created by heheszek on 12.12.2021.
//

#include <iostream>
#include <vector>

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

void inicjujWierzcholki(int ileElementow, wierzchołki &w) {
    for (int i = 0; i < ileElementow; i++) {
        w.push_back(-1);
    }
}

/*void inicjujPolecenia(int ileElementow, polecenia pol) {
    for (int i = 0; i < ileElementow; i++) {
        pol.push_back(make_pair(-1, -1));
    }
} */

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

int znajdzGlebokosc(wierzchołki &lewy, wierzchołki &prawy, wierzchołki &glebokosc,
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

    return 0;
}

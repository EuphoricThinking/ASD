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

using polecenia = vector<pair<int, int>>;
using wierzchołki = vector<int>;

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

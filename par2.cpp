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

macierz stworzMacierz(int liczbaPolanek, int log) {
//    int log = 0;
//    while (1 << log < liczbaPolanek + 1) {
//        log++;
//    } //log++
//    cout << log << endl;
    macierz wynik;
    for (int i = 0; i < liczbaPolanek + 1; i++) {
        vector<int> k_przodkowie(log, 0);
        wynik.push_back(k_przodkowie);
    }

    return wynik;
}

macierz wyznaczK_przodkow(const wierzchołki & rodzice, int liczbaPolanek, int log) {
    macierz k_przodkowie = stworzMacierz(liczbaPolanek, log);

    for (int i = 1; i < liczbaPolanek + 1; i++) {
        k_przodkowie[i][0] = rodzice[i];
    }

    for (int i = 1; i < liczbaPolanek + 1; i++) {
        for (int j = 1; j < log; j++) {
            k_przodkowie[i][j] = k_przodkowie[ k_przodkowie[i][j - 1] ][j - 1];
        }
    }

    return k_przodkowie;
}

void printAncestors(macierz k_przodkowie) {
    int nodes = k_przodkowie.size();
    int log = k_przodkowie[0].size();

    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < log; j++) {
            cout << k_przodkowie[i][j] << " ";
        }

        cout << endl;
    }
}

int znajdzK_tegoPrzodka(const macierz & k_przodkowie, const odleglosc & glebokosc,
                        int nr_wierzcholka, int k, int log) {
    if (k > glebokosc[nr_wierzcholka]) return -1;

    for (int j = 0; j < log; j++) {
        if (k & ( 1 << j)) {
            nr_wierzcholka = k_przodkowie[nr_wierzcholka][j];
        }
    }

    return nr_wierzcholka;
}

int znajdzLCA(int a_wierzcholek, int b_wierzcholwek, const macierz & k_przodkowie,
              const odleglosc & glebokosc, int log) {
    if (glebokosc[a_wierzcholek] < glebokosc[b_wierzcholwek]) {
        int temp = a_wierzcholek;
        a_wierzcholek = b_wierzcholwek;
        b_wierzcholwek = temp;
    }

    int k = glebokosc[a_wierzcholek] - glebokosc[b_wierzcholwek];
    a_wierzcholek = znajdzK_tegoPrzodka(k_przodkowie, glebokosc, a_wierzcholek,
                                        k, log);

    if (a_wierzcholek == b_wierzcholwek) return a_wierzcholek;

    for (int i = 0; i < log; i++) {
        if (k_przodkowie[a_wierzcholek][i] != k_przodkowie[b_wierzcholwek][i]) {
            a_wierzcholek = k_przodkowie[a_wierzcholek][i];
            b_wierzcholwek = k_przodkowie[b_wierzcholwek][i];
        }
    }

    return k_przodkowie[a_wierzcholek][0];
}

int znajdzNizej(const macierz & k_przodkowie,
                 int odlegloscOdWierzcholka, odlWierzch najdalszy,
                 const odleglosc & glebokosc, int log) {
    int k = najdalszy.odl - odlegloscOdWierzcholka;
    return znajdzK_tegoPrzodka(k_przodkowie, glebokosc, najdalszy.wierzch,
                               k, log);
}

int znajdzPozaPoddrzewem(int nr_wierzcholka, odlWierzch najdalszy,
                         const macierz & k_przodkowie, const odleglosc & glebokosc,
                         int log, int odlegloscOdWierzcholka) {
    int lca = znajdzLCA(nr_wierzcholka, najdalszy.wierzch, k_przodkowie,
                        glebokosc, log);

    if (glebokosc[nr_wierzcholka] - glebokosc[lca] >= odlegloscOdWierzcholka) {
        return znajdzK_tegoPrzodka(k_przodkowie, glebokosc, nr_wierzcholka,
                                   odlegloscOdWierzcholka, log);
    }
    
    int bezOdWyjsciowegoDoLCA = odlegloscOdWierzcholka - (glebokosc[nr_wierzcholka] - glebokosc[lca]);
    int k = glebokosc[najdalszy.wierzch] - glebokosc[lca] - bezOdWyjsciowegoDoLCA;

    return znajdzK_tegoPrzodka(k_przodkowie, glebokosc, najdalszy.wierzch, k, log);
}

int obsluzJednoZapytanie(zadanie pol, const macierz & k_przodkowie,
                         const odleglosc & glebokosc, int log,
                         const wykaz_odlWierzch & najdalszeDol,
                         const wykaz_odlWierzch & najdalszeGora) {
    int skad = pol.first;
    int jakDaleko = pol.second;
    odlWierzch najdDol = najdalszeDol[skad];
    odlWierzch najdGora = najdalszeGora[skad];

    if (jakDaleko <= najdDol.odl) {
        return znajdzNizej(k_przodkowie, jakDaleko, najdDol, glebokosc, log);
    } else if (jakDaleko <= najdGora.odl) {
        return znajdzPozaPoddrzewem(skad, najdGora, k_przodkowie, glebokosc,
                                    log, jakDaleko);
    } else {
        return -1;
    }
}

void obsluzZapytania(const polecenia & pol, const macierz & k_przodkowie,
                     const odleglosc & glebokosc, int log,
                     const wykaz_odlWierzch & najdalszeDol,
                     const wykaz_odlWierzch & najdalszeGora) {
    int wynik;
    for (zadanie zad: pol) {
        wynik = obsluzJednoZapytanie(zad, k_przodkowie, glebokosc, log,
                                     najdalszeDol, najdalszeGora);
        cout << wynik << endl;
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

    int log = std::ceil(std::log2(liczbaPolanek + 1));
    macierz k_przodkowie = wyznaczK_przodkow(rodzic, liczbaPolanek, log);
    //cout << std::ceil(std::log2(8)) << endl;
    printAncestors(k_przodkowie);
    cout << "anc\n";
    int anc = znajdzK_tegoPrzodka(k_przodkowie, glebokosc, 8, 2, log);
    cout << anc << endl;

    int lca = znajdzLCA(4, 8, k_przodkowie, glebokosc, log);
    cout << "lca " << lca << endl;

    cout << "\n\nWYNIK\n\n";
    obsluzZapytania(pol, k_przodkowie, glebokosc, log, najdalszyDol, najdalszyGora);
}

//
// Created by heheszek on 13.02.2022.
//

#include <iostream>
#include <set>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::set;
using std::vector;
using std::pair;

using std::make_pair;
using std::lower_bound;

typedef struct {
    int left;
    int right;
    char col;
} paint;

using polecenia = vector<paint>;
using set_limits = set<pair<int, int>>;

const char WHITE = 'B';
const char BLACK = 'C';

paint createPaint(int l, int r, char c) {
    paint p;
    p.left = l;
    p.right = r;
    p.col = c;

    return p;
}

polecenia readInput(int &roadLength, int &numOfActions) {
    cin >> roadLength >> numOfActions;

    polecenia res;
    int l, r;
    char c;
    for (int i = 0; i < numOfActions; i++) {
        cin >> l >> r >> c;
        paint p = createPaint(l, r, c);

        res.push_back(p);
    }

    return res;
}

bool compareFirst(const pair<int, int> & p, int toComp) {
    return p.first < toComp;
}

bool compareSecond(const pair<int, int> & p, int toComp) {
    return p.second < toComp;
}

void findDelete(set_limits &whiteStore, const paint & toRecolor, int &whiteLength) {
    auto left_a = whiteStore.lower_bound(toRecolor.left, compareSecond);

}

void insertIntoSet(set_limits &whiteStore, const paint & toRecolor, int &whiteLength) {
    if (whiteStore.empty() && toRecolor.col == WHITE) {
        whiteStore.insert(make_pair(toRecolor.left, toRecolor.right));

        whiteLength = toRecolor.right - toRecolor.left + 1;
    } else if (toRecolor.col == BLACK) {

    }
}
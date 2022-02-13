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

typedef struct {
    int left;
    int right;
    char col;
} paint;

using polecenia = vector<paint>;

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
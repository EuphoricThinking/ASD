//
// Created by heheszek on 06.11.2021.
//
#include <iostream>
#include <vector>
#include <cmath>

namespace {
using std::cout;
using std::cin;
using std::endl;

using std::vector;

using sequence = vector<int>;
using matrix = vector <vector<int>>;
}

sequence readInput(int& howMany) {
    cin >> howMany;

    sequence result;
    int temp;
    for (int i = 0; i < howMany; i++) {
        cin >> temp;
        //cout << temp << endl;
        result.push_back(temp);
    }

    return result;
}

void printVector(int howMany, sequence &vec) {
    cout << "length: " << howMany << endl;
    for (int item: vec) {
        cout << item << " ";
    }
    cout << endl;
}

int fillMatrices(int length, sequence &sorted) {
    int right[length][length];
    int left[length][length];

    for (int i = 0; i < length; ++i) {
        left[i][i] = 1;
        right[i][i] = 1;

        //cout << "i: " << i;
        if (i < length - 1) {
            //cout << " i + 1: " << i+1;
            left[i][i + 1] = (sorted[i] < sorted[i + 1]);
            right[i][i + 1] = (sorted[i] < sorted[i + 1]);
        }
        //cout << endl;
    }

    /*for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            cout << left[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\n\n";

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; j++) {
            cout << right[i][j] << " ";
        }
        cout << endl;
    }*/

    long long modulo = pow(10.0, 9.0);

    int j;

    for (int d = 2; d < length; ++d) { //lenght
        for (int i = 0; i < length; ++i) {  //length
            //if (j - i >= 2) {
            j = i + d;
            //cout << "i: " << i << "j: " << j << endl;
            if (j < length) {
                left[i][j] = ((sorted[i] < sorted[i + 1]) * left[i + 1][j] +
                              (sorted[i] < sorted[j]) * right[i + 1][j]) %
                             modulo;

                right[i][j] = ((sorted[i] < sorted[j]) * left[i][j - 1] +
                               (sorted[j - 1] < sorted[j]) * right[i][j - 1]) %
                              modulo;
            }
           // }
        }
    }


    /*for (int i = 0; i < length; ++i) {
        left[i][i] = 1;
        right[i][i] = 1;
    }

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
                if (j - i == 1) {
                    left[i][j] = (sorted[i] < sorted[i + 1]);
                }
        }
    }

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (j - i == 1) {
                right[i][j] = (sorted[j - 1] < sorted[j]);
            }
        }
    }

    long long modulo = pow(10.0, 9.0);

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            if (j - i >= 2) {
                cout << "i: " << i << "j: " << j << endl;
                left[i][j] = ((sorted[i] < sorted[i + 1]) * left[i + 1][j] +
                              (sorted[i] < sorted[j]) * right[i + 1][j]) %
                             modulo;

                right[i][j] = ((sorted[i] < sorted[j]) * left[i][j - 1] +
                               (sorted[j - 1] < sorted[j]) * right[i][j - 1]) %
                              modulo;
            }
        }
    }*/
    //long long modulo = pow(10.0, 9.0);

/*    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (i == j) {
                left[i][j] = 1;
                right[i][j] = 1;
            }
            else if (j - i == 1) {
                left[i][j] = (sorted[i] < sorted[i+1]);
                right[i][j] = (sorted[j - 1] < sorted[j]);
            }
            else if (j - i > 1) {
                left[i][j] = ((sorted[i] < sorted[i + 1]) * left[i + 1][j] +
                              (sorted[i] < sorted[j]) * right[i + 1][j]) %
                             modulo;

                right[i][j] = ((sorted[i] < sorted[j]) * left[i][j - 1] +
                               (sorted[j - 1] < sorted[j]) * right[i][j - 1]) %
                              modulo;
            }
        }
    }*/

    /*for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            cout << left[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\n\n";

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; j++) {
            cout << right[i][j] << " ";
        }
        cout << endl;
    }

    cout << left[0][length - 1] << " " << right[0][length - 1] << endl;*/

    return (left[0][length - 1] + right[0][length - 1]*(length > 1))%modulo;
}

int main(void) {
    int length;
    sequence sorted = readInput(length);
    //cout << "here" << endl;

    int result = fillMatrices(length, sorted);
    cout << result << endl;

    return 0;
}
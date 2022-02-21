//
// Created by heheszek on 21.02.2022.
//

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::cin;
using std::endl;

using std::pair;
using std::vector;
using std::string;

using std::make_pair;

using vec_long = vector<long long>;

const int MAX_LEN = 1000000;
int dynamic[3][MAX_LEN];

const int EQUAL = 0;
const int DEC = 1;
const int INC = 2;

const int MONO = 2;

vec_long read_input(int & num_numbers) {
    cin >> num_numbers;

    vec_long res;

    long long partial;
    for (int i = 0; i < num_numbers; i++) {
        cin >> partial;
        res.push_back(partial);
    }

    return res;
}

void print_vec(vec_long v) {
    for (long long l: v) {
        cout << l << " ";
    }

    cout << endl;
}

bool same_monotonous_update_mono(int prev, int cur, int i) {
    if (prev < cur) {
        dynamic[MONO][i] = INC;
        if (dynamic[MONO][i - 1] == INC) return true;
        else return false;
    } else if (prev > cur) {
        dynamic[MONO][i] = DEC;
        if (dynamic[MONO][i - 1] == DEC) return true;
        else return false;
    } else {
        dynamic[MONO][i] = EQUAL;
        if (dynamic[MONO][i - 1] == EQUAL) return true;
        else return false;
    }
}

int fill_matrix(int num_numbers, const vec_long & sequence) {
    for (int i = 1; i < num_numbers; i++) {
        if (same_monotonous_update_mono())
    }
}

int main() {
    int num_numbers;
    vec_long sequence = read_input(num_numbers);
    cout << num_numbers << endl;
    print_vec(sequence);

    return 0;
}
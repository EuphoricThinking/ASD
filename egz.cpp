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

bool same_monotonous_update_mono(long long prev, long long cur, int i) {
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
    long long prev;
    long long cur;
    int mod_cur;
    int mod_prev;

    int sum_sequences = 0;
    for (int i = 1; i < num_numbers; i++) {
        prev = sequence[i - 1];
        cur = sequence[i];
        mod_cur = cur%2;
        mod_prev = prev%2;
        if (same_monotonous_update_mono(prev, cur, i)) {
            if (mod_cur == 1) {
                dynamic[0][i] = dynamic[1][i - 1];
                dynamic[1][i] = dynamic[0][i - 1] + 1;
                //sum_sequences += dynamic[0][i];
            } else {
                dynamic[1][i] = dynamic[1][i - 1];
                dynamic[0][i] = dynamic[0][i - 1] + 1;
                //sum_sequences += dynamic[0][i];
            }
        } else {
            if (mod_cur == 1) {
                if (mod_prev == 1) dynamic[0][i] = 1;
                else dynamic[1][i] = 1;
            } else { //mod_cur == 0
                if (mod_prev == 1) dynamic[1][i] = 1;
                else dynamic[0][i] = 1;
            }
        }

        sum_sequences += dynamic[0][i];
    }

    return sum_sequences;
}

void print_matrix(int num_numbers, const vec_long & v) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < num_numbers; j++) {
            cout << dynamic[i][j] << " ";
        }
        cout << endl;
    }

    print_vec(v);
}

int main() {
    int num_numbers;
    vec_long sequence = read_input(num_numbers);
    //cout << num_numbers << endl;
    //print_vec(sequence);

    int res = fill_matrix(num_numbers, sequence);
    cout << res << endl;
    print_matrix(num_numbers, sequence);

    return 0;
}
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

int main() {
    int num_numbers;
    vec_long sequence = read_input(num_numbers);
    cout << num_numbers << endl;
    print_vec(sequence);

    return 0;
}
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

vec_long print_vec(vec_long v) {
    for (long long l: v) {
        cout << l << " ";
    }

    cout << endl;
}

int main() {
    int num_numbers;
    vec_long sequence = read_input(num_numbers);
    print_vec(sequence);

    return 0;
}
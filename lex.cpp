//
// Created by heheszek on 06.01.2022.
//
#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

using std::pair;
using std::vector;
using std::string;

using std::make_pair;

using indexes = pair<int, int>;
using command = pair<indexes, indexes>;
using commands = vector<command>;

commands read_input(int &word_length, int &num_commands, string &word) {
    cin >> word_length >> num_commands >> word;

    commands result;
    int s1_l, s1_r, s2_l, s2_r;
    indexes sub1, sub2;
    for (int i = 0; i < num_commands; i++) {
        cin >> s1_l >> s1_r >> s2_l >> s2_r;
        sub1 = make_pair(s1_l, s1_r);
        sub2 = make_pair(s2_l, s2_r);
        result.push_back(make_pair(sub1, sub2));
    }

    return result;
}

void print_indexes(indexes ind) {
    cout << ind.first << " " << ind.second;
}

void print_pair_of_indexes(command com) {
    print_indexes(com.first);
    cout << " | ";
    print_indexes(com.second);
    cout << endl;
}

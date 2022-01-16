//
// Created by heheszek on 16.01.2022.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;

using std::pair;
using std::vector;
using std::string;

using std::make_pair;
using std::floor;
using std::log;
using std::pow;
using std::sort;

using indexes = pair<int, int>;
using command = pair<indexes, indexes>;
using commands = vector<command>;

const char SMALLER = '<';
const char GREATER = '>';
const char EQUAL = '=';

commands read_input(int &word_length, int &num_commands, string &word) {
    cin >> word_length >> num_commands >> word;

    commands result;
    int s1_l, s1_r, s2_l, s2_r;
    indexes sub1, sub2;
    for (int i = 0; i < num_commands; i++) {
        cin >> s1_l >> s1_r >> s2_l >> s2_r;
        sub1 = make_pair(s1_l - 1, s1_r - 1); //added -1
        sub2 = make_pair(s2_l - 1, s2_r - 1); //added -1
        result.push_back(make_pair(sub1, sub2));
    }

    return result;
}

void print_indexes(indexes ind) {
    cout << ind.first << " " << ind.second;
}

void force_szkopul(int length, string s, int coms, commands com) {
    cout << length<< "|" << coms << "|"<< s << "&";
    for (command c: com) {
        cout << c.first.first << "," << c.first.second << "|" <<
             c.second.first << "," << c.second.second << "%";
    }
}
void print_pair_of_indexes(command &com) {
    print_indexes(com.first);
    cout << " | ";
    print_indexes(com.second);
    cout << endl;
}

void print_commands(commands coms) {
    for (command &cm: coms) {
        print_pair_of_indexes(cm);
    }
}

void print_input(int word_length, int num_commands, string s, commands com) {
    cout << word_length << " " << num_commands << "\n" << s << "\n";
    print_commands(com);
}
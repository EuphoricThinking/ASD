//
// Created by heheszek on 28.01.2022.
//
#include <iostream>
#include <vector>
#include <tuple>
#include <set>

using std::cout;
using std::cin;
using std::endl;

using std::vector;
using std::tuple;
using std::set;
using std::pair;

using std::make_tuple;
using std::get;

using command = tuple<char, int, int>;
using list_of_commands = vector<command>;
using ixes = set<int>;
using interval = pair<int, int>;
using set_of_intervals = set<interval>;


list_of_commands read_input(int &U_range, int &num_commmands) {
    cin >> U_range >> num_commmands;

    list_of_commands result;
    char temp_char;
    int temp_left;
    int temp_right;

    for (int i = 0; i < num_commmands; i++) {
        cin >> temp_char >> temp_left >> temp_right;
        result.push_back(make_tuple(temp_char, temp_left, temp_right));
    }

    return result;
}

void print_commands(list_of_commands &coms) {
    for (command com: coms) {
        cout << get<0>(com) << " " << get<1>(com) << " " << get<2>(com) << endl;
    }
}

void print_input(int U_range, int num_commands, list_of_commands &coms) {
    cout << U_range << " " << num_commands << endl;
    print_commands(coms);
}

void add_interval
int main() {
    int U_range;
    int num_commands;
    list_of_commands commands = read_input(U_range, num_commands);
    print_input(U_range, num_commands, commands);

    int num_outside_U;
    ixes prefixes;
    ixes suffixes;
    set_of_intervals current_intervals;
}



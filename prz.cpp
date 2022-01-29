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
using std::make_pair;
using std::min;

using ixes = set<int>;
using interval = pair<int, int>;
using set_of_intervals = set<interval>;

using command = pair<char, interval >;
using list_of_commands = vector<command>;

const char ADD = '+';

list_of_commands read_input(int &U_range, int &num_commmands) {
    cin >> U_range >> num_commmands;

    list_of_commands result;
    char temp_char;
    int temp_left;
    int temp_right;

    for (int i = 0; i < num_commmands; i++) {
        cin >> temp_char >> temp_left >> temp_right;
        result.push_back(make_pair(temp_char, make_pair(temp_left, temp_right)));
    }

    return result;
}

void print_interval(interval inter) {
    cout << inter.first << " " << inter.second << endl;
}
void print_commands(list_of_commands &coms) {
    for (command com: coms) {
        cout << com.first << " ";
        print_interval(com.second);
    }
}

void print_input(int U_range, int num_commands, list_of_commands &coms) {
    cout << U_range << " " << num_commands << endl;
    print_commands(coms);
}

void add_interval(interval inter, set_of_intervals &current, ixes &prefix,
                  ixes &suffix) {
    if (current.insert(inter).second) {
        if (inter.first == 1) {
            prefix.insert(inter.second);
        } else {
            suffix.insert(inter.first);
        }

        int max_pref = *(prefix.end()--);
        int min_suff = *suffix.begin();

        cout << min(0, min_suff - max_pref + 1) << endl;
    }
}

void remove_interval(interval inter, set_of_intervals &current, ixes &prefix,
                     ixes &suffix, int U_range) {
    if (current.erase(inter) == 1) {
        if (inter.first == 1) {
            prefix.erase(inter.second);
        } else {
            suffix.erase(inter.first);
        }

        if (!current.empty()) {
            int max_pref = *(prefix.end()--);
            int min_suff = *suffix.begin();

            cout << min(0, min_suff - max_pref + 1);
        } else {
            cout << U_range << endl;
        }
    }
}

void execute_commands(list_of_commands &coms, set_of_intervals &current, ixes &prefix,
                      ixes &suffix, int U_range) {
    for (command com: coms) {
        if (com.first == ADD) {
            add_interval(com.second, current, prefix, suffix);
        } else {
            remove_interval(com.second, current, prefix, suffix, U_range);
        }
    }
}

int main() {
    int U_range;
    int num_commands;
    list_of_commands commands = read_input(U_range, num_commands);
    print_input(U_range, num_commands, commands);

    ixes preffix;
    ixes suffix;
    set_of_intervals current_intervals;

    execute_commands(commands, current_intervals, preffix, suffix, U_range);
}



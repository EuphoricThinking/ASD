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
using ixes_track = pair<ixes, int>;

using command = pair<char, interval >;
using list_of_commands = vector<command>;



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

void add_interval(interval inter, set_of_intervals &current, ixes_track &prefix,
                  ixes_track &suffix, int &num_outside) {
    if (current.insert(inter).second) {
        if (inter.first == 1) {
            if (prefix.second < inter.second) {
                prefix.second = inter.second;
                prefix.first.insert(inter.second);
            }
        } else {
            if (suffix.second > inter.first) {
                suffix.second = inter.first;
                suffix.first.insert(inter.first);
            }
        }

        cout << min(0, suffix.second - prefix.second) << endl;
    }
}

int main() {
    int U_range;
    int num_commands;
    list_of_commands commands = read_input(U_range, num_commands);
    print_input(U_range, num_commands, commands);

    int num_outside_U;
    ixes pref_pre;
    ixes suff_pre;
    set_of_intervals current_intervals;

    ixes_track prefixes = make_pair(pref_pre, 0);
    ixes_track suffixes = make_pair(suff_pre, 0);


}



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
using std::max;

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

void force_szkopul(int U_range, int num_commands, list_of_commands &coms) {
    cout << U_range << "|" << num_commands << "[";
    for (command com:coms) {
        cout << com.first <<"*"<<com.second.first << ":"<<com.second.second<<"&";
    }
}

void print_ixes(ixes &ix) {
    for (int i: ix) {
        cout << i << " ";
    }
    cout << endl;
}

void mess(std::string message) {
    cout << message << endl;
}

void add_interval(interval inter, set_of_intervals &current, ixes &prefix,
                  ixes &suffix) {
    if (current.insert(inter).second) {
        if (inter.first == 1) {
        //    cout << "s" << inter.second << endl;
            prefix.insert(inter.second);
        } else {
            suffix.insert(inter.first);
        }

        //print_interval(inter);
//        cout << "add p " << *(--prefix.end()) << endl;
//        cout << "add i " << *(it) << endl;
//        cout << "add rp " << *(prefix.rbegin()) << endl;
//        cout << "add s " << *(suffix.begin()) << endl;
//        if (prefix.empty()) {
//            cout << *suffix.begin() - 1<< endl;
//        } else if (suffix.empty()) {
//            cout << U_range - *(--prefix.end()) << endl;
//        } else {
//            int max_pref = *(--prefix.end());
//            int min_suff = *suffix.begin();
//
//            cout << max(0, min_suff - max_pref - 1) << endl;
//        }
    }
}

void print_num_outisde(set_of_intervals &current, ixes &prefix,
                       ixes &suffix, int U_range) {
    //cout << "here ";
    if (current.empty()) {
        //     mess("empty");
        cout << U_range << endl;
    } else if (prefix.empty()) {
        //   mess("pref empty");
        cout << *suffix.begin() - 1 << endl;
    } else if (suffix.empty()) {
        //   mess("suff empty");
        cout << U_range - *(--prefix.end()) << endl;
    } else {
        //   mess("full");
        int max_pref = *(--prefix.end());
        int min_suff = *suffix.begin();
        //cout << max_pref << " p " << min_suff << endl;
        cout << max(0, min_suff - max_pref - 1) << endl;
    }
}

void remove_interval(interval inter, set_of_intervals &current, ixes &prefix,
                     ixes &suffix) {
    if (current.erase(inter) == 1) {
        if (inter.first == 1) {
            prefix.erase(inter.second);
        } else {
            suffix.erase(inter.first);
        }

//        mess("rem\npref");
//        print_ixes(prefix);
//        mess("suff");
//        print_ixes(suffix);
    }
}

void execute_commands(list_of_commands &coms, set_of_intervals &current, ixes &prefix,
                      ixes &suffix, int U_range) {
    int counter = 0;
    for (command com: coms) {
        //cout << "com: " << counter << endl;
       // print_interval(com.second);
        if (com.first == ADD) {
            add_interval(com.second, current, prefix, suffix);
        } else {
            remove_interval(com.second, current, prefix, suffix);
        }

        print_num_outisde(current, prefix, suffix, U_range);
        counter++;
    }
}

int main() {
    int U_range;
    int num_commands;
    list_of_commands commands = read_input(U_range, num_commands);
   // print_input(U_range, num_commands, commands);
    //force_szkopul(U_range, num_commands, commands);

    ixes preffix;
    ixes suffix;
    set_of_intervals current_intervals;

    execute_commands(commands, current_intervals, preffix, suffix, U_range);
}



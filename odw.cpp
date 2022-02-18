//
// Created by heheszek on 18.02.2022.
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
using command = pair<int, int>;
using commands = vector<command>>;
using vec_int = vector<int>;
using vec_bool = vector<bool>;

string read_input(int & string_length, int & num_commands, commands & com) {
    string word;
    cin >> string_length >> num_commands >> word;

    int left;
    int right;
    for (int i = 0; i < num_commands; i++) {
        cin >> left >> right;
        com.push_back(make_pair(left, right));
    }

    return word;
}

void fill_data(command com, vec_int & positions, vec_bool & flipped) {
    positions[com.first] = com.second;
    positions[com.second] = com.first;

    flipped[com.first] = true;
    flipped[com.second] = true;
}

void execute_commands(commands & coms, vec_int & positions, vec_bool & flipped) {
    for (command c: coms) {
        fill_data(c, positions, flipped);
    }
}

void incr_or_decr(int & index, int half) {
    if (index < half) index++;
    else index--;
}

void incr_decr(int & index, int half, int left_visited) {
    if (index == half) {
        if (!left_visited) index--;
        else index++;
    } else incr_or_decr(index, half);
}

void print_output(vec_int & positions, vec_bool & flipped, int string_length,
                  string word) {
    vec_bool visited(string_length + 1, false);

    int outer_index = 0;
    int inner_index = 0;
    int count = 0;
    int half;
    int range;
    while (outer_index < string_length) {
        if (!flipped[outer_index]) {
            cout << word[outer_index];
            outer_index++;
        } else {
            range = positions[outer_index] - outer_index + 1;
            half = range/2;
            inner_index = outer_index;

            while (count < range) {
                if (inner_index == 0) {
                    break;
                }

                if (flipped[inner_index]) {
                    if (!visited[flipped[inner_index]]) {
                        inner_index = flipped[inner_index];
                        cout << word[inner_index];
                        visited[inner_index] = true;
                        incr_decr(inner_index, half, visited[inner_index - 1]);
                    } else {

                    }
                }
            }
            count = 0;
        }
    }
}
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
using commands = vector<command>;
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

void print_pair(command c) {
    cout << c.first << " " << c.second << endl;
}

void print_commands(commands com) {
    for (command c: com) {
        print_pair(c);
    }
}

void print_data(string word, int string_length, int num_commands, commands com ){
    cout << string_length << " " << num_commands << "\n" << word << endl;
    print_commands(com);
}

void fill_data(command com, vec_int & positions, vec_bool & flipped) {
    positions[com.first - 1] = com.second - 1;
    positions[com.second - 1] = com.first - 1;

    flipped[com.first - 1] = true;
    flipped[com.second - 1] = true;
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

void new_incr_decr(int & index, vec_bool visited, int half) {
    if (index == half) {
        if (!visited[index - 1]) index--;
        else index++;
    } else {
        if (index < half) {
            if (!visited[index + 1]) index++;
            else index--;
        } else {
            if (!visited[index] - 1) index--;
            else index++;
        }
    }
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
        //cout << word[outer_index] << " out " << outer_index << endl;
        if (!flipped[outer_index]) {
            cout << word[outer_index];
            outer_index++;
        } else {
            range = positions[outer_index] - outer_index + 1;
            half = range/2 + outer_index;
            //cout << "\nhalf " << half << " range " << range << endl;
            inner_index = outer_index;
            outer_index = positions[outer_index] + 1;

            while (count < range) {
                //cout << "\nout inn" << inner_index << word[inner_index] <<  endl;
                //cout << count << endl;
                //cout << inner_index << endl;
                if (inner_index == -1) {
                //    cout << "zero";
                    break;
                }

                if (flipped[inner_index]) {
                    if (!visited[positions[inner_index]]) {
                        inner_index = positions[inner_index];
           //             cout << " inner " << inner_index;
           //             cout << "\ninner index not visited " << word[inner_index] << inner_index << endl;
                        cout << word[inner_index];
                        visited[inner_index] = true;
                        //incr_decr(inner_index, half, visited[inner_index - 1]);
                        new_incr_decr(inner_index, visited, half);
                    } else {
           //             cout << "visited " << inner_index << word[inner_index] << inner_index << endl;
                        cout << word[inner_index];
                        visited[inner_index] = true;
                        inner_index = positions[inner_index];
                        //incr_decr(inner_index, half, visited[inner_index - 1]);
                        new_incr_decr(inner_index, visited, half);
                    }
                } else {
                    cout << word[inner_index];
                    visited[inner_index] = true;
                    //incr_decr(inner_index, half, visited[inner_index - 1]);
                    new_incr_decr(inner_index, visited, half);
                }

                count++;
            }

            count = 0;
        }
    }

    cout << endl;
}

int main() {
    int string_length;
    int num_commands;
    commands com;
    string word = read_input(string_length, num_commands, com);
    //print_data(word, string_length, num_commands, com);

    vec_int positions(string_length + 1, 0);
    vec_bool flipped(string_length + 1, false);

    execute_commands(com, positions, flipped);

//    for (bool b: flipped) cout << b << " ";
//    cout << endl;
//    for (int i: positions) cout << i << " ";
//    cout << endl;

    print_output(positions, flipped, string_length, word);

    return 0;
}
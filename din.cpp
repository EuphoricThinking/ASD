//
// Created by heheszek on 29.12.2021.
//
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using std::cout;
using std::cin;
using std::endl;
using std::make_tuple;
using std::get;

using std::tuple;
using std::vector;
using std::string;

using command = tuple<char, int, int, int>;
using commands = vector<command>;

string read_input(int &word_length, int &num_commands, commands &com) {
    string dna_code;
    cin >> word_length >> num_commands >> dna_code;
    cout << word_length << " " << num_commands << "\n" << dna_code << endl;

    char type_of_command;
    int temp_index1;
    int temp_index2;
    int temp_index3;
    for (int i = 0; i < num_commands; i++) {
        cin >> type_of_command;
        command to_insert;
        if (type_of_command == 'P') {
            cin >> temp_index1 >> temp_index2 >> temp_index3;
            to_insert = make_tuple(type_of_command, temp_index1, temp_index2,
                                   temp_index3);
        } else {
            cin >> temp_index1 >> temp_index2;
            to_insert = make_tuple(type_of_command, temp_index1, temp_index2,
                                   -1);
        }
        com.push_back(to_insert);
    }

    return dna_code;
}

void print_commands(commands com) {
    for (commands::iterator iter = com.begin(); iter != com.end(); iter++) {
        cout << get<0>(*iter) << " " << get<1>(*iter) << " "
            << get<2>(*iter) << " " << get<3>(*iter) << endl;
    }
}

int main(void) {
    int word_length;
    int num_commands;
    commands com;
    string dna = read_input(word_length, num_commands, com);
    print_commands(com);
}
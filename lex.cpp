//
// Created by heheszek on 06.01.2022.
//
#include <iostream>
#include <vector>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

using std::pair;
using std::vector;
using std::string;

using std::make_pair;
using std::floor;
using std::log;

using indexes = pair<int, int>;
using command = pair<indexes, indexes>;
using commands = vector<command>;

using index_in_word = int;
using sorting_pack = pair<index_in_word, indexes>;
using sorter = vector<vector<vector<sorting_pack>>>;
using dbf = vector<vector<int>>;
using temp_indexes = vector<indexes>;

const int MAX_LENGTH = 300000;
const int NUM_LETTERS = 26;

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

void print_commands(commands coms) {
    for (command &cm: coms) {
        print_pair_of_indexes(cm);
    }
}

void print_input(int word_length, int num_commands, string s, commands com) {
    cout << word_length << " " << num_commands << "\n" << s << "\n";
    print_commands(com);
}

sorter initialize_sorter(int word_length) {
    sorter result;

    for (int i = 0; i < word_length; i++) {
        vector<vector<sorting_pack>> v;
        result.push_back(v);
        for (int j = 0; j < word_length; j++) {
            vector<sorting_pack> vs;
            result[i].push_back(vs);
        }
    }

    return result;
}

dbf create_dbf(int word_length, int floor_log_length){
    dbf result;

    for (int i = 0; i < word_length; i++) {
        vector<int> v;
        result.push_back(v);

        for (int j = 0; j < floor_log_length; j++) {
            //probably TODO
        }
    }

    return result;
}

dbf fill_dbf_table(int word_length, string s) {
    int floor_log_length = (int)floor(log(word_length));
    dbf result = create_dbf(word_length, floor_log_length);
    temp_indexes temp_to_sort;

}

int main() {
    int word_length, num_commands;
    string word;
    commands com = read_input(word_length, num_commands, word);
    print_input(word_length, num_commands, word, com);
}

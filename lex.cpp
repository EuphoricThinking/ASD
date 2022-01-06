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
using std::pow;

using indexes = pair<int, int>;
using command = pair<indexes, indexes>;
using commands = vector<command>;

using index_in_word = int;
using sorting_pack = pair<index_in_word, indexes>;
using sorter = vector<vector<vector<sorting_pack>>>;
using dbf = vector<vector<int>>;
using temp_indexes = vector<sorting_pack>;

const int MAX_LENGTH = 300000;
const int NUM_LETTERS = 26;
const int A_POSITION = 96;

const int SMALLER = -1;
const int EQUAL = 0;
const int GREATER = 1;

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
            result[i].push_back(0);
        }
    }

    return result;
}

int get_alphabet_index(char c) {
/*    cout << "enter get" << endl;
    cout << c << endl;
    cout << int(c) << endl;
    cout << int(c) - A_POSITION << endl; */
    return int(c) - A_POSITION;
}

void initialize_dbf(dbf &table, int word_length, string s) {
 //   cout << "wlength: " << word_length << endl;
    for (int i = 0; i < word_length; i++) {
 //       cout << "i " << i << endl;
        table[i][0] = get_alphabet_index(s[i]);
    }
}

void radix_sort(sorter &sorted, temp_indexes temp) {
    for (sorting_pack sp: temp) {
        indexes coordinates = sp.second;
        sorted[coordinates.first][coordinates.second].push_back(sp);
    }
}

void clear_sorter(sorter &sorted) {
    for (vector<vector<sorting_pack>> &outside_vs: sorted) {
        for (vector<sorting_pack> &inside_vs: outside_vs) {
            inside_vs.clear();
        }
    }
}

void assign_number_to_dbf(dbf &table, const sorter &sorted, int word_length,
                          int power_index) {
    int counter = 1;

    for (int i = 0; i < word_length; i++) {
        for (int j = 0; j < word_length; j++) {
            if (!sorted[i][j].empty()) {
                for (sorting_pack sp: sorted[i][j]) {
                    int index = sp.first;

                    table[index][power_index] = counter;
                }

                counter++;
            }
        }
    }
}

void print_dbf(dbf table) {
    for (vector<int> v: table) {
        for (int i: v) {
            cout << i << " ";
        }
        cout << "\n";
    }
}

void print_sorting_pack(sorting_pack sp) {
    cout << "i: " << sp.first << " | ";
    print_indexes(sp.second);
    cout << endl;
}

void print_sorter(sorter sorted, int word_length) {
    for (int i = 0; i < word_length; i++) {
        cout << "S " << i << endl;
        for (int j = 0; j < word_length; j++) {
            if (!sorted[i][j].empty()) {
                for (sorting_pack sp: sorted[i][j]) {
                    print_sorting_pack(sp);
                }
            }
        }
    }
}

void print_temp(temp_indexes temp) {
    for (sorting_pack sp: temp) {
        print_sorting_pack(sp);
    }
}

dbf fill_dbf_table(int word_length, string s) {
    int floor_log_length = (int)floor(log2(word_length));
    cout << "FUCK " << floor_log_length << endl;
    dbf result = create_dbf(word_length, floor_log_length + 1);
   // cout << "dbl created" << endl;
    sorter sorted = initialize_sorter(word_length);
   // cout << "sorter created" << endl;
    initialize_dbf(result, word_length, s);
    cout << "dbf initialized" << endl;
    temp_indexes temp_to_sort;
    indexes indexes_to_sort;
    sorting_pack index_and_pair_of_indexes;
    int limit = word_length;

    for (int j = 1; j < floor_log_length + 1; j++) {
        int pow_j = pow(2, j - 1);
      //  for (int i = 0; i < word_length; i++) {
      //  cout << "POW " << pow_j << endl;
        //for (int i = 0; i + pow_j < word_length; i++) {
        for (int i = 0; i + pow_j < limit; i++) {
       //     cout << "i " << i << endl;
        //    cout << i + pow_j << endl;
      //      cout << "pow_j " << pow_j << endl;
            indexes_to_sort = make_pair(result[i][j - 1],
                                        result[i + pow(2, j - 1)][j - 1]);
            index_and_pair_of_indexes = make_pair(i, indexes_to_sort);
            temp_to_sort.push_back(index_and_pair_of_indexes);
        //    cout << i << endl;
        }
        limit -= pow_j;
        
        cout << " j " << j << endl;
        cout << "temp" << endl;
        print_temp(temp_to_sort);
        cout << "BEF" << endl;
        print_sorter(sorted, word_length);

        radix_sort(sorted, temp_to_sort);

        cout << "RADIX1" << endl;
        print_sorter(sorted, word_length);
        cout << "RADIX2" << endl;

        assign_number_to_dbf(result, sorted, word_length, j);

        clear_sorter(sorted);
        temp_to_sort.clear();

        cout << "AFT clean" << endl;
        print_sorter(sorted, word_length);
        cout << "DONE" << endl;
    }

    return result;
}

indexes get_dbf_indexes(indexes from_raw_array, const dbf &table) {
    int left = from_raw_array.first;
    int right = from_raw_array.second;
    int k = (int)floor(log(right - left + 1));
    int right_index_row_dbf = right - pow(2, k) + 1;

    return make_pair(table[left][k], table[right_index_row_dbf][k]);
}

int compare_indexes(indexes sub1, indexes sub2) {
    if (sub1 == sub2) {
        return EQUAL;
    } else if (sub1 < sub2) {
        return SMALLER;
    } else {
        return GREATER;
    }
}

int compare_subwords_in_command(command com, const dbf &table) {
    indexes sub1 = com.first;
    indexes sub2 = com.second;
    int sub1_length = sub1.second - sub1.first;
    int sub2_length = sub2.second - sub2.first;
    bool equal_length = false;
    bool first_longer = false;

    if ((sub1_length) > (sub2_length)) {
        sub1 = make_pair(sub1.first, sub1.first + sub2_length);
        first_longer = true;
    } else if (sub1_length < sub2_length) {
        sub2 = make_pair(sub2.first, sub2.first + sub1_length);
    } else {
        equal_length = true;
    }

    indexes dbf1 = get_dbf_indexes(sub1, table);
    indexes dbf2 = get_dbf_indexes(sub2, table);
    int comparison = compare_indexes(dbf1, dbf2);

    if (equal_length) {
        return comparison;
    } else if (!first_longer) {
        if (comparison == EQUAL) {
            return SMALLER;
        } else {
            return comparison;
        }
    } else {
        if (comparison == EQUAL) {
            return GREATER;
        } else {
            return comparison;
        }
    }
}

void print_result(int result) {
    if (result == EQUAL) {
        cout << "=" << "\n";
    } else if (result == SMALLER) {
        cout << "<" << "\n";
    } else {
        cout << ">" << "\n";
    }
}

void evaluate_commands_final(commands com, dbf table, int num_commands) {
    int result;
    for (int i = 0; i < num_commands; i++) {
        result = compare_subwords_in_command(com[i], table);
        print_result(result);
    }
}

int main() {
    int word_length, num_commands;
    string word;
    commands com = read_input(word_length, num_commands, word);
    print_input(word_length, num_commands, word, com);

    dbf table = fill_dbf_table(word_length, word);
    cout <<  "after dbl" << endl;
    print_dbf(table);
    evaluate_commands_final(com, table, num_commands);

    return 0;
}

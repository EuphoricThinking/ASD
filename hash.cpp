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
using std::min;

using indexes = pair<int, int>;
using command = pair<indexes, indexes>;
using commands = vector<command>;

using vec_int = vector<int>;

const char SMALLER = '<';
const char GREATER = '>';
const char EQUAL = '=';

const int SCALE_LETTERS = 96;
const int BASE = 27;
const int MODULO = 740000;

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

int value_of_a_letter(char c) {
    return (int)c - SCALE_LETTERS;
}

vec_int calculate_powers(int word_length) {
    vec_int powers;
    powers.push_back(1);
    int new_power;

    for (int i = 1; i < word_length; i++) {
        new_power = (powers[i - 1]*BASE)%MODULO;
        powers.push_back(new_power);
    }

    return powers;
}

//prefixes
vec_int calculate_hash_table(string &word, int word_length) {

    vec_int hash_table;
    hash_table.push_back(value_of_a_letter(word[0]));
    cout << BASE*MODULO << endl;
    int new_hash;
    for (int i = 1; i < word_length; i++) {
        new_hash = (hash_table[i - 1]*BASE + value_of_a_letter(word[i]))%MODULO;
        hash_table.push_back(new_hash);
    }

    return hash_table;
}

int calculate_hash_value(int i, int j, const vec_int &hash_table, const vec_int &powers) {
    int current_power = j - i + 1;
    return (hash_table[j] - hash_table[i]*powers[current_power])%MODULO;
}

int find_longest_common_prefix(command com, vec_int &powers, vec_int &hash_table) {
    indexes s1 = com.first;
    indexes s2 = com.second;
    int s1_l = s1.first;
    int s1_r = s1.second;
    int s2_l = s2.first;
    int s2_r = s2.second;

    //using only indexes, thus we have l = 0;
    int l = 0;
    int r = min(s1_r - s1_l + 1, s2_r - s1_l + 1);
    int mid;
    int hash_s1;
    int hash_s2;
    while (l < r) {
        mid = (l + r)/2;
        hash_s1 = calculate_hash_value(s1_l, s1_l + mid - 1, hash_table, powers);
        hash_s2 = calculate_hash_value(s2_l, s2_l + mid - 1, hash_table, powers);

        if (hash_s1 == hash_s2) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    if (l == r) {
        return -1;
    } else {
        return l;
    }
}

int main() {
    int word_length, num_commands;
    string word;
    commands com = read_input(word_length, num_commands, word);

    vec_int hash_table = calculate_hash_table(word, word_length);
    vec_int powers = calculate_powers(word_length);

    return 0;
}
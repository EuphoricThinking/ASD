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

int find_longest_common_prefix(const command &com, const vec_int &powers, const vec_int &hash_table) {
    indexes s1 = com.first;
    indexes s2 = com.second;
    int s1_l = s1.first;
    int s1_r = s1.second;
    int s2_l = s2.first;
    int s2_r = s2.second;

    //using only indexes, thus we have l = 0;
    int l = 0;
    int r = min(s1_r - s1_l + 1, s2_r - s1_l + 1);
    cout << "s1_l " << s1_l << " s1_r " << s1_r << " s2_l " << s2_l <<
        " s2_r " << s2_r << " r " << r << endl;
    int mid;
    int hash_s1;
    int hash_s2;
    while (l < r) {
        mid = (l + r)/2;
        cout << "l " << l << " | r " << r << " | mid " << mid << endl;
        hash_s1 = calculate_hash_value(s1_l, s1_l + mid - 1, hash_table, powers);
        hash_s2 = calculate_hash_value(s2_l, s2_l + mid - 1, hash_table, powers);
        cout << "s1_l, s1_l + mid - 1 : " << s1_l << " " << s1_l + mid - 1;
        cout << "s2_l, s2_l + mid - 1 : " << s2_l << " " << s2_l + mid - 1;

        if (hash_s1 == hash_s2) {
            cout << "UP" << endl;
            l = mid + 1;
        } else {
            r = mid;
        }
    }

 /*   if (l == r) {
        return -1;
    } else {
        return l;
    }*/
    return l;
}

void print_result(const string &word, int ind1, int ind2, int len1, int len2) {
    int val1 = value_of_a_letter(word[ind1]);
    int val2 = value_of_a_letter(word[ind2]);
    if ( val1 < val2) {
        cout << SMALLER << "\n";
    }
    else if (val1 > val2){
        cout << GREATER << "\n";
    } else {
        if (len1 == len2) cout << EQUAL << "\n";
        else if (len1 < len2) cout << SMALLER << "\n";
        else cout << GREATER << "\n";
    }
}

void compare_subwords(const string &word, const vec_int &powers, const vec_int &hash_table,
                      const command &com) {
    int index_first_different = find_longest_common_prefix(com, powers, hash_table);
    int len1 = com.first.second - com.first.first;
    int len2 = com.second.second - com.second.first;
    cout << "\nL: " << index_first_different << "\n\n";

/*    if (index_first_different == -1) {
        if (len1 == len2) cout << EQUAL << "\n";
        else if (len1 < len2) cout << SMALLER << endl;
        else cout << GREATER << endl;
    }
    else {*/
        print_result(word, com.first.first + index_first_different,
                     com.second.first + index_first_different , len1, len2); //-1 from index
 //   }
}

void execute_commands(const string &word, const vec_int &powers, const vec_int &hash_table,
                      const commands &coms) {
    for (command com: coms) {
        cout << "NEW\n\n" << endl;
        compare_subwords(word, powers, hash_table, com);
        cout << "\n\n";
    }
}

int main() {
    //freopen("lex_test1.in","r",stdin);
    int word_length, num_commands;
    string word;
    commands com = read_input(word_length, num_commands, word);
    print_input(word_length, num_commands, word, com);

    vec_int hash_table = calculate_hash_table(word, word_length);
    vec_int powers = calculate_powers(word_length);
    execute_commands(word, powers, hash_table, com);

    return 0;
}
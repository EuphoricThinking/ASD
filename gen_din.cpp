//
// Created by heheszek on 16.02.2022.
//

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;
using std::make_tuple;
using std::make_pair;
using std::get;
using std::max;


using std::tuple;
using std::vector;
using std::string;
using std::pair;

using command = tuple<char, int, int, int>;
using commands = vector<command>;
using interval = pair<int, int>;


string read_input(int &word_length, int &num_commands, commands &com) {
    string dna_code;
    cin >> word_length >> num_commands >> dna_code;
    // cout << word_length << " " << num_commands << "\n" << dna_code << endl;

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

class gen_test {
private:
    string dna;
public:
    void O(int l, int r) {
        _reverse(l, r);
    }

    void P(int l, int r, int to) {
        _translocate(l, r, to);
    }

    void N(int l, int r) {
        int res = _get_max(l, r);
        cout << res << endl;
    }

    void execute_commands (commands com, int num_commands) {
        _execute_commands(com, num_commands);
    }

    gen_test(string s) : dna(s) {};

private:
    void _reverse(int l, int r) {
        char tempL;
        l = l - 1;
        r = r - 1l;
        while(l < r) {
            tempL = dna[l];
            dna[l] = dna[r];
            dna[r] = tempL;

            l++;
            r--;
        }
    }

    void _translocate(int l, int r, int to) {
        string to_locate = dna.substr(l, r - l + 1);
        std::stringstream ss;
        ss << dna.substr(0, l - 1) << dna.substr(l - 1, r) << dna.substr(r);
        dna = ss.str();
    }

    int _get_max(int l, int r) {
        int max_r = 1;
        int cur_res = dna[l-1];
        int max_cur = 1;
        for (int i = l; i < r; i++) {
            if (dna[i] == cur_res) {
                max_cur++;

                max_r = max(max_cur, max_r);
            } else {
                cur_res = dna[i];
                max_cur = 1;
            }
        }

        return max_r;
    }

void _execute_commands(commands com, int num_commands) {
    for (int i = 0; i < num_commands; i++) {
        command to_execute = com[i];

        char type_command = get<0>(to_execute);
        int j = get<1>(to_execute);
        int k = get<2>(to_execute);
        int l = get<3>(to_execute);

        if (type_command == 'O') {
            _reverse(j, k);
        } else if (type_command == 'P') {
            _translocate(j, k, l);
        } else {
            // cout << "bef" << endl;  //TODO prints out
            //_print_tree(root, 0);
            //cout <<"\nN\n" << endl;
            int result = _get_max(j, k);
            // cout << "aft" << endl;
            // _print_tree(root, 0);
//                cout << "\n\n";
            //  cout << "!!!" << result << "???";
            cout << result << endl;
        }
        //_print_sequence(root);
    }
}
};

int main(void) {
    int word_length;
    int num_commands;
    commands com;
    string dna = read_input(word_length, num_commands, com);
//    cout << word_length << "|" << num_commands;
    //  print_commands(com);

    gen_test result(dna);
//    result.print_tree(); //TODO prints out
//    cout << "\n";
    result.execute_commands(com, num_commands);

    return 0;
}
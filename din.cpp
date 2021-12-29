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
using std::make_pair;
using std::get;


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

class DNAzer {
public:
    void insert(char res, int index) {
        root = _insert(root, res, index);
    }

private:
    struct Node {
        char residue;
        int lef_count;
        int height;

        char adjacent_residue;
        int max_sequence;
        interval begend;
        int end;

        struct Node *left;
        struct Node *right;
        struct Node *parent;
        Node (char _residue): residue(_residue), lef_count(0), left(NULL),
            right(NULL), parent(NULL) {}
    };
    struct Node *root = NULL;

    int _count_left_nodes(Node* cur) {
        return (cur != NULL ? cur->lef_count : 0);
    }

    Node* _insert(Node* current, char res, int index) {
        if (current == NULL) {
            return new Node(res);
        }

        if (current->lef_count <= _count_left_nodes(current)) {
            current->left = _insert(current->left, res, index);
        } else {
            current->right = _insert(current->right, res,
                                     index - _count_left_nodes(current->left) - 1);
        }

        return current;
    }
};

int main(void) {
    int word_length;
    int num_commands;
    commands com;
    string dna = read_input(word_length, num_commands, com);
    print_commands(com);
}
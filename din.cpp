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

    void insert_sequence(string seq, int seq_length) {
        for (int i = 0; i < seq_length; i++) {
            insert(seq[i], i);
        }
    }

    void print_sequence() {
        _print_sequence(root);
        cout << endl;
    }

    void print_tree() {
        _print_tree(root);
    }

private:
    struct Node {
        char residue;
        int count;
        int height;

        char adjacent_residue;
        int max_sequence;
        interval begend;
        int end;

        struct Node *left;
        struct Node *right;
        struct Node *parent;
        Node (char _residue): residue(_residue), count(1), left(NULL),
                              right(NULL), parent(NULL) {}
    };
    struct Node *root = NULL;

    int _count_nodes(Node* cur) {
        return (cur != NULL ? cur->count : 0);
    }

    char _return_residue(Node* current) {
        return current->residue;
    }

    void _update(Node* current) {
        if (current != NULL) {
            current->count = 1 + _count_nodes(current->left) +
                    _count_nodes(current->right);
        }
    }

    Node* _insert(Node* current, char res, int index) {
        if (current == NULL) {
            return new Node(res);
        }

        int left_nodes = _count_nodes(current->left);
        //cout << "index: " << index << " count: " << current->count << endl;
        if (index <= left_nodes) {
           // cout << "here" << endl;
            current->left = _insert(current->left, res, index);
        } else {
            current->right = _insert(current->right, res,
                                     index - left_nodes - 1);
        }

//bez update wsadza odwrotnie
        _update(current);
        return current;
    }

    void _print_sequence(Node* current) {
        if (current != NULL) {
            _print_sequence(current->left);
            cout << _return_residue(current);
            _print_sequence(current->right);
        }
    }

    void _print_tree(Node* current) {
        if (current != NULL) {
            _print_tree(current->left);
            cout << current->residue << " " << current->count << endl;
            _print_tree(current->right);
        }
    }
};

int main(void) {
    int word_length;
    int num_commands;
    commands com;
    string dna = read_input(word_length, num_commands, com);
    print_commands(com);

    DNAzer result;
    result.insert_sequence(dna, word_length);
    result.print_sequence();
    //result.print_tree();
    result.insert('j', 3);
    result.insert('k', 3);
    result.insert('f', 5);
    result.insert('p', 5);
    result.print_tree();
}
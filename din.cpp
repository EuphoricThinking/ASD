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
        _print_tree(root, 0);
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
                              right(NULL), parent(NULL), height(0) {}
    };
    struct Node *root = NULL;

    int _count_nodes(Node* cur) {
        return (cur != NULL ? cur->count : 0);
    }

    char _get_residue(Node* current) {
        return current->residue;
    }

    int _get_height(Node* current) {
        return (current != NULL ? current->height : -1);  //:0
    }

    void _update_height(Node* current) {
        current->height = 1 + max(_get_height(current->left),
                                  _get_height(current->right));
    }

    int _get_balance(Node* cur) {
        return _get_height(cur->left) - _get_height(cur->right);
    }

    void _update(Node* current) {
        if (current != NULL) {
            Node* left_child = current->left;
            Node* right_child = current->right;

            current->count = 1 + _count_nodes(left_child) +
                    _count_nodes(right_child);
            //current->height = 1 + max(_get_height(left_child),
            //                    _get_height(right_child));
            _update_height(current);
        }
    }

    //left child of a left child //left_left
    Node* _right_rotate(Node* cur_root) {
        Node* first_level_right_son = cur_root->left->right;
        Node* first_level = cur_root->left;

        cur_root->left = first_level_right_son;
        first_level->right = cur_root;

        cout << " right " << cur_root->residue << endl;
        //_update_height(cur_root);
        //_update_height(first_level);
        _update(cur_root);
        _update(first_level);
        return first_level;
    }

    //right child of a right child//right right
    Node* _left_rotate(Node *cur_root) {
        Node* first_level = cur_root->right;
        Node* first_level_left_son = first_level->left;

        cur_root->right = first_level_left_son;
        first_level->left = cur_root;

        cout << " left " << cur_root->residue << endl;
        //_update_height(cur_root);
        //_update_height(first_level);
        _update(cur_root);
        _update(first_level);
        return first_level;
    }

    Node* _left_right(Node* cur_root) {
        cout << " left right " << cur_root->residue << endl;
        cur_root->left = _left_rotate(cur_root->left);
        return _right_rotate(cur_root);
    }

    Node* _right_left(Node* cur_root) {
        cout << " right left " << cur_root->residue << endl;
        cur_root->right = _right_rotate(cur_root->right);
        return _left_rotate(cur_root);
    }

    Node* _insert(Node* current, char res, int index) {
        if (current == NULL) {
            return new Node(res);
        }

        int left_nodes = _count_nodes(current->left);
        cout << "index: " << index << " count: " << current->count << " res " << current->residue << endl;
        if (index <= left_nodes) {
           // cout << "here" << endl;
            current->left = _insert(current->left, res, index);
        } else {
            current->right = _insert(current->right, res,
                                     index - left_nodes - 1);
        }

//bez update wsadza odwrotnie
        _update(current);

        int balance = _get_balance(current);
        cout << " balance " << balance << " " << current->residue << endl;

        if (balance > 1) {
            Node* left_child = current->left;
            /*Node* right_child = current->right;
            int left_height = _get_height(left_child);
            int right_height = _get_height(right_child);*/

            if (_get_balance(left_child) >= 0) {
                cout << " lb " << _get_balance(left_child) << " higher right " << endl;
                return _right_rotate(current);
            } else {
                cout << " lb " << _get_balance(left_child) << " higher left " << endl;
                return _left_right(current);
            }
        } else if (balance < -1) {
            Node* right_child = current->right;

            if (_get_balance(right_child) <= 0) {
                cout << " rb " << _get_balance(right_child) << " higher left " << endl;
                return _left_rotate(current);
            } else {
                cout << " rb " << _get_balance(right_child) << " higher right " << endl;
                return _right_left(current);
            }
        }

        cout << "exit " << current->residue << endl;
        return current;
    }

    void _print_sequence(Node* current) {
        if (current != NULL) {
            _print_sequence(current->left);
            cout << _get_residue(current);
            _print_sequence(current->right);
        }
    }

    void _print_tree(Node* current, int h) {
        if (current != NULL) {
            _print_tree(current->left, h + 1);
            cout << current->residue << " count " << current->count <<
                " height " << current->height << " h " << h << endl;
            _print_tree(current->right, h + 1);
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
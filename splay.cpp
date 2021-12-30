//
// Created by heheszek on 29.12.2021.
//

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
        root = _insert(root, res, index - 1, NULL, NULL); //without -1
    }

    void insert_sequence(string seq, int seq_length) {
        for (int i = 0; i < seq_length; i++) {
            insert(seq[i], i + 1); //without +1
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
        //int height;
        bool if_left;

        char adjacent_residue;
        int max_sequence;
        interval begend;
        int end;

        struct Node *left;
        struct Node *right;
        struct Node *parent;
        Node (char _residue, bool child_side): residue(_residue), count(1), left(NULL),
                              right(NULL), parent(NULL), if_left(child_side) {}
    };
    struct Node *root = NULL;

    int _count_nodes(Node* cur) {
        return (cur != NULL ? cur->count : 0);
    }

    char _get_residue(Node* current) {
        return current->residue;
    }

    //left child of a left child //left_left
    Node* _right_rotate(Node* cur_root) {
        Node* first_level_right_son = cur_root->left->right;
        Node* first_level = cur_root->left;

        cur_root->left = first_level_right_son;
        first_level->right = cur_root;

        first_level->parent = cur_root->parent;
        cur_root->parent = first_level;
        first_level->if_left = cur_root->if_left;
        cur_root->if_left = false;

        if (first_level->parent != NULL) {
            if (first_level->if_left) {
                first_level->parent->left = first_level;
            } else {
                first_level->parent->right = first_level;
            }
        }

        cout << " right " << cur_root->residue << endl;

        return first_level;
    }

    //right child of a right child//right right
    Node* _left_rotate(Node *cur_root) {
        Node* first_level = cur_root->right;
        Node* first_level_left_son = first_level->left;
       // Node* cur_parent = cur_root->parent;

        cur_root->right = first_level_left_son;
        first_level->left = cur_root;

        first_level->parent = cur_root->parent;
        cur_root->parent = first_level;
        first_level->if_left = cur_root->if_left;
        cur_root->if_left = true;

        if (first_level->parent != NULL) {
            if (first_level->if_left) {
                first_level->parent->left = first_level;
            } else {
                first_level->parent->right = first_level;
            }
        }

        cout << " left " << cur_root->residue << endl;

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

    Node* _insert(Node* current, char res, int index, Node* parent, bool child_side) {
        if (current == NULL) {
            Node* newborn = new Node(res, child_side);
            newborn->parent = parent;
            //return new Node(res);
            return newborn;
        }

        int left_nodes = _count_nodes(current->left);
        //cout << "index: " << index << " count: " << current->count << " res " << current->residue << endl;
        if (index <= left_nodes) {
            // cout << "here" << endl;
            current->left = _insert(current->left, res, index, current, true);
        } else {
            current->right = _insert(current->right, res,
                                     index - left_nodes - 1, current, false);
        }

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
                  " h " << h << endl;
            _print_tree(current->right, h + 1);
        }
    }

    Node* _search_index(Node* cur, int index) {
        Node* left_child = cur->left;
        Node* right_child = cur->right;

        if (left_child == NULL && right_child == NULL) {
            return cur;
        }

        if (index <= _count_nodes(left_child)) {
            return _search_index(left_child, index);
        } else if (index == _count_nodes(cur)) {
            cout << "found " << cur->residue << endl;
            return cur;
        } else {
            return _search_index(right_child, index - 1 -
                _count_nodes(left_child));
        }
    }

    Node* local_splay(Node* cur) {
        if (cur != NULL) {
        if (root->left == cur) {
            return _right_rotate(root);
        } else if (root->right == cur) {
            return _left_rotate(root);
        }

        Node* grandpa = cur->parent->parent;
        if (cur->if_left && cur->parent->if_left) {
            cur->parent = _right_rotate(grandpa);
            //cur = _right_rotate(cur->parent);
            return _right_rotate(cur->parent);
            //return cur;
        } else if ((!cur->if_left) && (!cur->parent->if_left)) {
            cur->parent = _left_rotate(cur->parent->parent);
            //cur = _left_rotate(cur->parent);
            //return cur;
            return _left_rotate(cur->parent);
        } else if ((!cur->if_left) && cur->parent->if_left) {
            return _left_right(grandpa);
        } else if (cur->if_left && (!cur->parent->if_left)) {
            return _right_left(grandpa);
        }
    }
    }

    void _splay(Node* to_root) {
        while (to_root != root) {

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
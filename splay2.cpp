//
// Created by heheszek on 30.12.2021.
//

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

    void splay(int index) {
        _splay(index);
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


    void _left_right(Node* cur_root) {
        cout << " left right " << cur_root->residue << endl;
        _left_rotate(cur_root->left);
    }

    void _right_left(Node* cur_root) {
        cout << " right left " << cur_root->residue << endl;
        _right_rotate(cur_root->right);
    }

    void _update(Node* current) {
        if (current != NULL) {
            Node* left_child = current->left;
            Node* right_child = current->right;

            current->count = 1 + _count_nodes(left_child) +
                             _count_nodes(right_child);
            //current->height = 1 + max(_get_height(left_child),
            //                    _get_height(right_child));
            //_update_height(current);
        }
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

        _update(current);

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
                 " h " << h << " if_left " << current->if_left << endl;
            _print_tree(current->right, h + 1);
        }
    }

    Node* _search_index(Node* cur, int index) {
        Node* left_child = cur->left;
        Node* right_child = cur->right;

        if (left_child == NULL && right_child == NULL) {
            return cur;
        }

        cout << "imhere" << endl;
        if (index <= _count_nodes(left_child)) {
            return _search_index(left_child, index);
        } else if ((index == (_count_nodes(left_child) + 1))
                || index == 0) {
            cout << "found " << cur->residue << endl;
            return cur;
        } else {
            return _search_index(right_child, index - 1 -
                                              _count_nodes(left_child));
        }
    }

    void _right_rotate(Node* cur_root) {
        /*Node* first_level_right_son = cur_root->left->right;
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

        cout << " right " << cur_root->residue << endl;*/
        Node* first_level = cur_root->left;

        if (first_level) {
            cur_root->left = first_level->right;
            if (first_level->right) {
                cur_root->left->if_left = 1;
                first_level->right->parent = cur_root;
            }
            first_level->parent = cur_root->parent;
            first_level->if_left = cur_root->if_left;
            //cur_root->if_left = 0;
        }

        if (!cur_root->parent) root = first_level;
        else if (cur_root->if_left) cur_root->parent->left = first_level;
        else cur_root->parent->right = first_level;

        if (first_level) {
            first_level->right = cur_root;
            cur_root->if_left = 0;
        }

        cur_root->parent = first_level;
    }

    //right child of a right child//right right
    void _left_rotate(Node *cur_root) {
        /*Node* first_level = cur_root->right;
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

        cout << " left " << cur_root->residue << endl;*/
        Node* first_level = cur_root->right;

        if (first_level) {
            cur_root->right = first_level->left;
            if (first_level->left) {
                cur_root->right->if_left = 0;
                first_level->left->parent = cur_root;
            }
            first_level->parent = cur_root->parent;
            first_level->if_left = cur_root->if_left;
            //cur_root->if_left = 0;
        }

        if (!cur_root->parent) root = first_level;
        else if (cur_root->if_left) cur_root->parent->left = first_level;
        else cur_root->parent->right = first_level;

        if (first_level) {
            first_level->left = cur_root;
            cur_root->if_left = 1;
        }

        cur_root->parent = first_level;
    }
    void _local_splay(Node* cur) {
        if (cur != NULL) {
            if (root->left == cur) {
                _right_rotate(cur->parent);
            } else if (root->right == cur) {
                _left_rotate(cur->parent);
            }

            Node* grandpa = cur->parent->parent;
            if (cur->if_left && cur->parent->if_left) {
                _right_rotate(grandpa);
                //cur = _right_rotate(cur->parent);
                _right_rotate(cur->parent);
                //return cur;
            } else if ((!cur->if_left) && (!cur->parent->if_left)) {
                _left_rotate(cur->parent->parent);
                //cur = _left_rotate(cur->parent);
                //return cur;
                _left_rotate(cur->parent);
            } else if ((!cur->if_left) && cur->parent->if_left) {
                //_left_right(grandpa);
                _right_rotate(cur->parent);
                _left_rotate(cur->parent);
            } else if (cur->if_left && (!cur->parent->if_left)) {
                //_right_left(grandpa);
                _left_rotate(cur->parent);
                _right_rotate(cur->parent);
            }
        }
    }


    void _splay(int index) {
        Node* to_root = _search_index(root, index);
        cout << to_root->residue << endl;
        while (to_root->parent) {
            if (to_root != NULL) {
                if (root->left == to_root) {
                    _right_rotate(to_root->parent);
                } else if (root->right == to_root) {
                    _left_rotate(to_root->parent);
                }

                Node* grandpa = to_root->parent->parent;
                if (to_root->if_left && to_root->parent->if_left) {
                    _right_rotate(grandpa);
                    //cur = _right_rotate(cur->parent);
                    _right_rotate(to_root->parent);
                    //return cur;
                } else if ((!to_root->if_left) && (!to_root->parent->if_left)) {
                    _left_rotate(to_root->parent->parent);
                    //cur = _left_rotate(cur->parent);
                    //return cur;
                    _left_rotate(to_root->parent);
                } else if ((!to_root->if_left) && to_root->parent->if_left) {
                    //_left_right(grandpa);
                    _right_rotate(to_root->parent);
                    _left_rotate(to_root->parent);
                } else if (to_root->if_left && (!to_root->parent->if_left)) {
                    //_right_left(grandpa);
                    _left_rotate(to_root->parent);
                    _right_rotate(to_root->parent);
                }
            }
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
    cout << "\n\n";
    result.splay(4);
    result.print_tree();
}
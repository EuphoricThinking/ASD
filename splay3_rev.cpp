//
// Created by heheszek on 16.02.2022.
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

void print_commands(commands com) {
    for (commands::iterator iter = com.begin(); iter != com.end(); iter++) {
        cout << get<0>(*iter) << "|" << get<1>(*iter) << "|"
             << get<2>(*iter) << "|" << get<3>(*iter) << "//";
    }
}

void print_command(command com) {
    cout << get<0>(com) << " " << get<1>(com) << " "
         << get<2>(com) << " " << get<3>(com) << endl;
}

class DNAzer {
public:
    void insert(char res, int index) {
        root = _insert(root, res, index - 1, NULL); //without -1
    }

    void insert_sequence(string seq, int seq_length) {
        for (int i = 0; i < seq_length; i++) {
            root = _insert(root, seq[i], i + 1, NULL); //without +1
            reverse = _insert(reverse, seq[seq_length - i - 1], i + 1, NULL);
        }
    }

    void print_sequence() {
        _print_sequence(root);
        cout << endl;
    }

    void print_both_sequences() {
        _print_sequence(root);
        cout << "\nREV\n";
        _print_sequence(reverse);
        cout << endl;
    }

//    void print_tree() {
//        _print_tree(root, 0);
//    }
//
//    void splay(int index) {
//        _splay(index, root);
//    }
//
//    void P(int l, int r, int k) {
//        _translocate(l, r, k);
//    }
//
//    void O(int l, int r) {
//        _reverse(l, r);
//    }
//
//    void N(int l, int r) {
//        cout << "\nN\n" << endl;
//        int result = _find_maximum_length(l, r);
//        cout << "Look at me bitch I'm here " << result << "\n";
//    }

    void execute_commands(commands com, int num_commands) {
        _execute_commands(com, num_commands);
    }

private:
    struct Node {
        char residue;
        int count;
        //int height;

        //   char max_adjacent_residue;
        int max_sequence_length;
        //   char last_residue;
        int prefix_length;
        int suffix_length;
        char prefix_residue;
        char suffix_residue;
        bool is_suffix_prefix_equal;

        struct Node *left;
        struct Node *right;
        struct Node *parent;

        Node(char _residue) : residue(_residue), count(1), left(NULL),
                              right(NULL), parent(NULL),
                // max_adjacent_residue(residue),
                // last_residue(residue),
                              max_sequence_length(1),
                              prefix_length(1),
                              suffix_length(1),
                              prefix_residue(residue),
                              suffix_residue(residue),
                              is_suffix_prefix_equal(true) {}
    };

    struct Node *root = NULL;
    struct Node *reverse = NULL;

    using triplet = tuple<Node *, Node *, Node *>;

    int _count_nodes(Node *cur) {
        return (cur != NULL ? cur->count : 0);
    }

    char _get_residue(Node *current) {
        return current->residue;
    }

    void _update(Node *current) {
        if (current != NULL) {
            Node *left_child = current->left;
            Node *right_child = current->right;

            current->count = 1 + _count_nodes(left_child) +
                             _count_nodes(right_child);
            _update_segment_length(current);
        }
    }

    int _max_of_three(int a, int b, int c) {
        return max(a, max(b, c));
    }

    void _update_segment_length(Node *cur_root) {
        if (cur_root != NULL) {
            Node *left_child = cur_root->left;
            Node *right_child = cur_root->right;

            if (!left_child && !right_child) {
                cur_root->max_sequence_length = 1;
                cur_root->prefix_length = 1;
                cur_root->suffix_length = 1;
                cur_root->prefix_residue = cur_root->residue;
                cur_root->suffix_residue = cur_root->residue;
                cur_root->is_suffix_prefix_equal = true;
            } else if (left_child && right_child) {

                if (left_child->suffix_residue == cur_root->residue
                    && right_child->prefix_residue ==
                       cur_root->residue) { //Wszystkie trzy zgadzają się

                    if (left_child->is_suffix_prefix_equal
                        && right_child->is_suffix_prefix_equal) {

                        cur_root->is_suffix_prefix_equal = true;
                        cur_root->max_sequence_length =
                                left_child->suffix_length +
                                right_child->prefix_length + 1;
                        cur_root->prefix_length = cur_root->max_sequence_length;
                        cur_root->suffix_length = cur_root->max_sequence_length;
                        cur_root->prefix_residue = cur_root->residue;
                        cur_root->suffix_residue = cur_root->residue;
                    } else if (left_child->is_suffix_prefix_equal) { //cały lewy, korzeń, prefiks prawego | osobno sufiks prawego
                        cur_root->is_suffix_prefix_equal = false;
                        cur_root->prefix_length = left_child->suffix_length + 1
                                                  + right_child->prefix_length;
                        cur_root->prefix_residue = cur_root->residue;
                        cur_root->suffix_length = right_child->suffix_length;
                        cur_root->suffix_residue = right_child->suffix_residue;
                        cur_root->max_sequence_length = max(
                                cur_root->prefix_length,
                                right_child->max_sequence_length);
                    } else if (right_child->is_suffix_prefix_equal) { //ososbno prefiks lwewgo | sufiks lewego + korzeń + prefiksosufiks prawegp
                        cur_root->is_suffix_prefix_equal = false;
                        cur_root->suffix_length = right_child->prefix_length + 1
                                                  + left_child->suffix_length;
                        cur_root->suffix_residue = cur_root->residue;
                        cur_root->prefix_length = left_child->prefix_length;
                        cur_root->prefix_residue = left_child->prefix_residue;
                        cur_root->max_sequence_length = max(
                                left_child->max_sequence_length,
                                cur_root->suffix_length);
                    } else { //osobno prefiks lewego | sufiks lewego + korzeń + prefiks prawego | osobono sufiks praweo
                        cur_root->is_suffix_prefix_equal = false;
                        cur_root->prefix_length = left_child->prefix_length;
                        cur_root->prefix_residue = left_child->prefix_residue;
                        cur_root->suffix_length = right_child->suffix_length;
                        cur_root->suffix_residue = right_child->suffix_residue;
                        int middle = left_child->suffix_length + 1 +
                                     right_child->prefix_length;
                        cur_root->max_sequence_length =
                                _max_of_three(left_child->max_sequence_length,
                                              middle,
                                              right_child->max_sequence_length);
                    }
                } else if (left_child->suffix_residue ==
                           cur_root->residue) { //zgadza się lewt
                    cur_root->is_suffix_prefix_equal = false;

                    if (left_child->is_suffix_prefix_equal) { //cały lewy + korzeń | prefiks prawego | sufiks prawego
                        cur_root->prefix_residue = cur_root->residue;
                        cur_root->prefix_length = left_child->suffix_length + 1;
                        cur_root->suffix_residue = right_child->suffix_residue;
                        cur_root->suffix_length = right_child->suffix_length;
                        cur_root->max_sequence_length =
                                max(cur_root->prefix_length,
                                    right_child->max_sequence_length);
                    } else { // prefiks lewego | sufiks lewego + korzeń | prefiks prawego | sufiks lewego
                        cur_root->prefix_length = left_child->prefix_length;
                        cur_root->prefix_residue = left_child->prefix_residue;
                        cur_root->suffix_length = right_child->suffix_length;
                        cur_root->suffix_residue = right_child->suffix_residue;
                        int middle = left_child->suffix_length + 1;
                        cur_root->max_sequence_length =
                                _max_of_three(left_child->max_sequence_length,
                                              middle,
                                              right_child->max_sequence_length);
                    }
                } else if (right_child->prefix_residue ==
                           cur_root->residue) { //zgadza się prawy
                    cur_root->is_suffix_prefix_equal = false;

                    if (right_child->is_suffix_prefix_equal) {  //prefiks lewego | sufiks lewego | korzeń + cały prawy
                        cur_root->suffix_length =
                                right_child->prefix_length + 1;
                        cur_root->suffix_residue = cur_root->residue;
                        cur_root->prefix_length = left_child->prefix_length;
                        cur_root->prefix_residue = left_child->prefix_residue;
                        cur_root->max_sequence_length =
                                max(cur_root->suffix_length,
                                    left_child->max_sequence_length);
                    } else {  // prefiks lewego | sufiks lewego | korzeń + prefiks orawego | sufiks prawego
                        cur_root->prefix_length = left_child->prefix_length;
                        cur_root->prefix_residue = left_child->prefix_residue;
                        cur_root->suffix_length = right_child->suffix_length;
                        cur_root->suffix_residue = right_child->suffix_residue;
                        int middle = right_child->prefix_length + 1;
                        cur_root->max_sequence_length =
                                _max_of_three(left_child->max_sequence_length,
                                              middle,
                                              right_child->max_sequence_length);
                    }
                } else { //żaden nie zgasza się
                    cur_root->is_suffix_prefix_equal = false;
                    cur_root->prefix_length = left_child->prefix_length;
                    cur_root->prefix_residue = left_child->prefix_residue;
                    cur_root->suffix_length = right_child->suffix_length;
                    cur_root->suffix_residue = right_child->suffix_residue;
                    cur_root->max_sequence_length =
                            max(left_child->max_sequence_length,
                                right_child->max_sequence_length);
                }
            } else if (left_child) { //istnieje tylko lewy

                if (left_child->suffix_residue ==
                    cur_root->residue) { //zgadza się lewy

                    if (left_child->is_suffix_prefix_equal) { //całość
                        cur_root->is_suffix_prefix_equal = true;
                        cur_root->prefix_length = left_child->suffix_length + 1;
                        cur_root->prefix_residue = cur_root->residue;
                        cur_root->suffix_length = cur_root->prefix_length;
                        cur_root->suffix_residue = cur_root->residue;
                        cur_root->max_sequence_length = cur_root->prefix_length;
                    } else {  //prefiks lewego | sufiks lewego + korzeń
                        cur_root->is_suffix_prefix_equal = false;
                        cur_root->suffix_length = left_child->suffix_length + 1;
                        cur_root->suffix_residue = cur_root->residue;
                        cur_root->prefix_length = left_child->prefix_length;
                        cur_root->prefix_residue = left_child->prefix_residue;
                        cur_root->max_sequence_length =
                                max(left_child->max_sequence_length,
                                    cur_root->suffix_length);
                    }
                } else {  //nie zgadza się lewy
                    cur_root->is_suffix_prefix_equal = false;
                    cur_root->suffix_length = 1;
                    cur_root->suffix_residue = cur_root->residue;
                    cur_root->prefix_length = left_child->prefix_length;
                    cur_root->prefix_residue = left_child->prefix_residue;
                    cur_root->max_sequence_length = left_child->max_sequence_length;
                }
            } else if (right_child) { //istnieje tylko prawy

                if (right_child->prefix_residue ==
                    cur_root->residue) { //zgadza się prawy

                    if (right_child->is_suffix_prefix_equal) { //całość
                        cur_root->is_suffix_prefix_equal = true;
                        cur_root->suffix_length =
                                right_child->suffix_length + 1;
                        cur_root->suffix_residue = cur_root->residue;
                        cur_root->prefix_length = cur_root->suffix_length;
                        cur_root->prefix_residue = cur_root->suffix_residue;
                        cur_root->max_sequence_length = cur_root->prefix_length;
                    } else { //korzeń + prefiks prawego | sufiks prawego
                        cur_root->is_suffix_prefix_equal = false;
                        cur_root->prefix_length =
                                right_child->prefix_length + 1;
                        cur_root->prefix_residue = cur_root->residue;
                        cur_root->suffix_length = right_child->suffix_length;
                        cur_root->suffix_residue = right_child->suffix_residue;
                        cur_root->max_sequence_length =
                                max(cur_root->prefix_length,
                                    right_child->max_sequence_length);
                    }
                } else { //nie zgadza się prawy; korzeń | prefiks prawego | sufiks lewego
                    cur_root->is_suffix_prefix_equal = false;
                    cur_root->prefix_length = 1;
                    cur_root->prefix_residue = cur_root->residue;
                    cur_root->suffix_length = right_child->suffix_length;
                    cur_root->suffix_residue = right_child->suffix_residue;
                    cur_root->max_sequence_length = right_child->max_sequence_length;
                }
            }
        }
    }


    Node* _insert(Node* current, char res, int index, Node* parent) {
        if (current == NULL) {
            Node* newborn = new Node(res);
            newborn->parent = parent;
            //return new Node(res);
            return newborn;
        }

        int left_nodes = _count_nodes(current->left);
//        cout << "index: " << index << " count: " << current->count << " res " << current->residue << endl;
        if (index <= left_nodes) {
            // cout << "here" << endl;
            current->left = _insert(current->left, res, index, current);
        } else {
            current->right = _insert(current->right, res,
                                     index - left_nodes - 1, current);
        }

        _update(current);
        //       _update_segment_length(current);

        return current;
    }

    void _left_rotate(Node* cur, bool is_root) {
        Node* right_child = cur->right;

        if (right_child) {
            cur->right = right_child->left;
            if (right_child->left) right_child->left->parent = cur;
            right_child->parent = cur->parent;
        }

        //if (!cur->parent) root = right_child;
        if (!cur->parent) {
            if (is_root) root = right_child;
            else reverse = right_child;
        }
        else if (cur == cur->parent->left) cur->parent->left = right_child;
        else cur->parent->right = right_child;

        if (right_child) right_child->left = cur;

        cur->parent = right_child;
    }

    void _right_rotate(Node* cur, bool is_root) {
        Node* left_child = cur->left;

        if (left_child) {
            cur->left = left_child->right;
            if (left_child->right) left_child->right->parent = cur;
            left_child->parent = cur->parent;
        }

        if (!cur->parent) {
            if (is_root) root = left_child;
            else reverse = left_child;
        }
        else if (cur == cur->parent->left) cur->parent->left = left_child;
        else cur->parent->right = left_child;

        if (left_child) left_child->right = cur;

        cur->parent = left_child;
    }
    void _print_sequence(Node* current) {
        if (current != NULL) {
            _print_sequence(current->left);
            cout << _get_residue(current);
            _print_sequence(current->right);
        }
    }

    void _print_sequence_with_indexes() {
            cout << "r " << _count_nodes(root) << endl;
            _print_sequence(root);
            cout << endl;
            for (int i = 1; i <= _count_nodes(root)/10; i++) {
                for (int j = 1; j < 10; j++ ) {
                    cout << j;
                }
                cout << 1;
            }
            cout << endl; //TODO wise tests
            for (int i = 0; i <= _count_nodes(root)/10; i++) {
                cout << i;
                for (int j = 1; j < 10; j++) {
                    cout << " ";
                }
            }
            cout << "\n\n";
    }

    void _execute_commands(commands com, int num_commands) {
        for (int i = 0; i < num_commands; i++) {
            command to_execute = com[i];

            char type_command = get<0>(to_execute);
            int j = get<1>(to_execute);
            int k = get<2>(to_execute);
            int l = get<3>(to_execute);

            //print_command(to_execute);
            if (type_command == 'O') {
     //           _reverse(j, k);
            } else if (type_command == 'P') {
      //          _translocate(j, k, l);
            } else {
                // cout << "bef" << endl;  //TODO prints out
                //_print_tree(root, 0);
                //cout <<"\nN\n" << endl;
      //          int result = _find_maximum_length(j, k); //TODO uncomment
                // cout << "aft" << endl;
                // _print_tree(root, 0);
//                cout << "\n\n";
                //  cout << "!!!" << result << "???";
       //         cout << result << endl;  //TODO uncomment
            }
        }
    }
};

int main() {
    int word_length;
    int num_commands;
    commands com;
    string dna = read_input(word_length, num_commands, com);
//    cout << word_length << "|" << num_commands;
    //  print_commands(com);

    DNAzer result;
    result.insert_sequence(dna, word_length);
//    result.print_tree(); //TODO prints out
//    cout << "\n";
    result.print_both_sequences();
    //result.execute_commands(com, num_commands);

    return 0;
}
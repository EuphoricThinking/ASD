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

class DNAzer {
public:
    void insert(char res, int index) {
        root = _insert(root, res, index - 1, NULL); //without -1
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
        _splay(index, root);
    }

    void P(int l, int r, int k) {
        _translocate(l, r, k);
    }

    void O(int l, int r) {
        _reverse(l, r);
    }

    void N(int l, int r) {
        int result = _find_maximum_length(l, r);
        cout << "Look at me bitch I'm here " << result << "\n";
    }

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
        Node (char _residue): residue(_residue), count(1), left(NULL),
                                               right(NULL), parent(NULL),
                                              // max_adjacent_residue(residue),
                                              // last_residue(residue),
                                               max_sequence_length(1),
                                               prefix_length(1),
                                               suffix_length(1),
                                               prefix_residue(residue),
                                               suffix_residue(residue),
                                               is_suffix_prefix_equal(true)

                                               {}
    };

    struct Node *root = NULL;

    using triplet = tuple<Node*, Node*, Node*>;

    int _count_nodes(Node* cur) {
        return (cur != NULL ? cur->count : 0);
    }

    char _get_residue(Node* current) {
        return current->residue;
    }

    void _update(Node* current) {
        if (current != NULL) {
            Node* left_child = current->left;
            Node* right_child = current->right;

            current->count = 1 + _count_nodes(left_child) +
                             _count_nodes(right_child);
            _update_segment_length(current);
            //current->height = 1 + max(_get_height(left_child),
            //                    _get_height(right_child));
            //_update_height(current);
        }
    }

    int _get_max_length(Node* cur) {
        return (cur != NULL ? cur->max_sequence_length : -1);
    }

    int _get_last_segment_length(Node* cur) {
        return (cur != NULL ? cur->prefix_length : -1);
    }

    void _print_seq_data(Node* cur) {
        cout << endl;
        cout << cur->residue << endl;
        cout << "max " << cur->max_sequence_length << "\n" <<
        " pref_res " << cur->prefix_residue << " length " << cur->prefix_length
        << "\nsuff_res " << cur->suffix_residue << " length " << cur->suffix_length
        << "\n\n";
    }

    //Previous version
    void _update_segment_length2(Node* cur_root) {
        if (cur_root != NULL) {
            Node *left_child = cur_root->left;
            Node *right_child = cur_root->right;

        /*    cout << "update segment cur " << cur_root->residue << endl;
            _print_tree(cur_root, 0);
            if (left_child) {
                cout << "left " << endl;
                _print_tree(left_child, 0);
                _print_seq_data(left_child);
            }
            if (right_child) {
                cout << "right" << endl;
                _print_tree(right_child, 0);
                _print_seq_data(right_child);
            }*/
            if ((!left_child) && (!right_child)) {
                cur_root->prefix_length = 1;
                cur_root->max_sequence_length = 1;
                cur_root->suffix_residue = cur_root->residue;
                cur_root->prefix_residue = cur_root->residue;
            }
            else if (!right_child) {
                if (cur_root->residue == left_child->suffix_residue) {
           //         cout << "(cur_root->residue == left_child->suffix_residue c " <<
          //          cur_root->residue << " left " << left_child->suffix_residue << endl;

                    cur_root->suffix_length =
                            left_child->suffix_length + 1;
                    if (left_child->is_suffix_prefix_equal) {
                        cur_root->prefix_length = left_child->prefix_length + 1;
                        cur_root->is_suffix_prefix_equal = true;
                    } else {
                        cur_root->prefix_length = left_child->prefix_length;
                    }
                }
                else {
                    cur_root->suffix_length = 1;
                    cur_root->is_suffix_prefix_equal = false;
                    cur_root->prefix_length = left_child->prefix_length;
                }

                cur_root->max_sequence_length = max(left_child->max_sequence_length,
                                                    cur_root->suffix_length);

                cur_root->prefix_residue = left_child->prefix_residue;
                cur_root->suffix_residue = cur_root->residue;
            }
            else if (!left_child) {
                if (cur_root->residue == right_child->prefix_residue) {
                    cur_root->prefix_length =
                            right_child->prefix_length + 1;
                    if (right_child->is_suffix_prefix_equal) {
                        cur_root->suffix_length = right_child->suffix_length + 1;
                        cur_root->is_suffix_prefix_equal = true;
                    } else {
                        cur_root->suffix_length = right_child->suffix_length;
                    }
                }
                else {
                    cur_root->prefix_length = 1;
                    cur_root->is_suffix_prefix_equal = false;
                    cur_root->suffix_length = right_child->suffix_length;
                }

                cur_root->max_sequence_length = max(right_child->max_sequence_length,
                                                    cur_root->prefix_length);

                cur_root->suffix_residue = right_child->suffix_residue;
                cur_root->prefix_residue = cur_root->residue;
            }
            else { //right_child && left_child
                int left_left = left_child->suffix_length;
                int right_right = right_child->prefix_length;
                //int left_middle = (left_child->last_residue_right == cur_root->residue ? left_left + 1

                if (left_child->suffix_residue == right_child->prefix_residue
                        && left_child->suffix_residue == cur_root->residue) { //merged
                    int new_length = left_left + right_right + 1;

                    int max_both = max(left_child->max_sequence_length,
                                       right_child->max_sequence_length);
                    cur_root->max_sequence_length = max(max_both, new_length);

                    if (left_child->is_suffix_prefix_equal &&
                        right_child->is_suffix_prefix_equal) {
                        cur_root->suffix_length = new_length;
                        cur_root->prefix_length = new_length;
                        cur_root->prefix_residue = left_child->prefix_residue;
                        cur_root->suffix_residue = right_child->suffix_residue;
                        cur_root->is_suffix_prefix_equal = true;
                    } else if (left_child->is_suffix_prefix_equal) {
                        cur_root->prefix_length = new_length;
                        cur_root->prefix_residue = left_child->prefix_residue;
                        cur_root->suffix_length = right_child->suffix_length;
                        cur_root->suffix_residue = right_child->suffix_residue;
                        cur_root->is_suffix_prefix_equal = false;
                    } else if (right_child->is_suffix_prefix_equal) {
                        cur_root->suffix_length = new_length;
                        cur_root->suffix_residue = right_child->suffix_residue;
                        cur_root->prefix_length = left_child->prefix_length;
                        cur_root->prefix_residue = left_child->prefix_residue;
                        cur_root->is_suffix_prefix_equal = false;
                    } else {
                        cur_root->prefix_length = left_child->prefix_length;
                        cur_root->suffix_length = right_child->suffix_length;
                        cur_root->prefix_residue = left_child->prefix_residue;
                        cur_root->suffix_residue = right_child->suffix_residue;
                        cur_root->is_suffix_prefix_equal = false;
                    }
                }
                else if (left_child->suffix_residue == cur_root->residue) {
                    int new_length = left_left + 1;  //we wont use it anymore

                    int max_both = max(left_child->max_sequence_length,
                                       right_child->max_sequence_length);
                    cur_root->max_sequence_length = max(max_both, new_length);

                    if (left_child->is_suffix_prefix_equal) {
                        cur_root->prefix_length = new_length;
                    } else {
                        cur_root->prefix_length = left_child->prefix_length;
                    }

                    cur_root->prefix_residue = left_child->prefix_residue;

                   // cur_root->prefix_length = left_child->prefix_length;
                    cur_root->suffix_length = right_child->suffix_length;
                   // cur_root->prefix_residue = left_child->prefix_residue;
                    cur_root->suffix_residue = right_child->suffix_residue;
                    cur_root->is_suffix_prefix_equal = false;
                }
                else if (right_child->prefix_residue == cur_root->residue) {
                    int new_length = right_right + 1;

                    int max_both = max(left_child->max_sequence_length,
                                       right_child->max_sequence_length);
                    cur_root->max_sequence_length = max(max_both, new_length);

                    if (right_child->is_suffix_prefix_equal) {
                        cur_root->suffix_length = new_length;
                    } else {
                        cur_root->suffix_length = right_child->suffix_length;
                    }

                    cur_root->suffix_residue = right_child->suffix_residue;

                    cur_root->prefix_residue = left_child->prefix_residue;
                    cur_root->prefix_length = left_child->prefix_length;
                    cur_root->is_suffix_prefix_equal = false;
                } else {
                    int max_segments = max(left_child->max_sequence_length,
                                           right_child->max_sequence_length);
                    cur_root->max_sequence_length = max_segments;

                    cur_root->prefix_length = left_child->prefix_length;
                    cur_root->prefix_residue = left_child->prefix_residue;
                    cur_root->suffix_length = right_child->suffix_length;
                    cur_root->suffix_residue = right_child->suffix_residue;
                    cur_root->is_suffix_prefix_equal = false;
                }
            }
        }
    }

    /*
     * char residue;
        int count;

        int max_sequence_length;
        int prefix_length;
        int suffix_length;
        char prefix_residue;
        char suffix_residue;
        bool is_suffix_prefix_equal;

        struct Node *left;
        struct Node *right;
        struct Node *parent;
     */
    void _update_segment_length(Node* cur_root) {
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
            }
            else if (left_child && right_child) {

                if (left_child->suffix_residue == cur_root->residue
                    && right_child->prefix_residue == cur_root->residue) { //Wszystkie trzy zgadzają się

                    if (left_child->is_suffix_prefix_equal
                        && right_child->is_suffix_prefix_equal) {

                        cur_root->is_suffix_prefix_equal = true;
                        cur_root->max_sequence_length =
                                left_child->prefix_length + right_child->prefix_length + 1;
                        cur_root->prefix_length = cur_root->max_sequence_length;
                        cur_root->suffix_length = cur_root->max_sequence_length;
                        cur_root->prefix_residue = cur_root->residue;
                        cur_root->suffix_residue = cur_root->residue;
                    }
                    else if (left_child->is_suffix_prefix_equal) { //cały lewy, korzeń, prefiks prawego
                        cur_root->is_suffix_prefix_equal = false;
                        cur_root->prefix_length = left_child->prefix_length + 1
                                + right_child->prefix_length;
                        cur_root->prefix_residue = cur_root->residue;
                        cur_root->suffix_length = right_child->suffix_length;
                        cur_root->suffix_residue = right_child->suffix_residue;
                        cur_root->max_sequence_length = max(cur_root->prefix_length,
                                                            cur_root->suffix_length);
                    }
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
        //cout << "index: " << index << " count: " << current->count << " res " << current->residue << endl;
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
                 " h " << h << " max " << current->max_sequence_length << endl;
            _print_tree(current->right, h + 1);
        }
    }

    Node* _search_index(Node* cur, int index) {
        Node* left_child = cur->left;
        Node* right_child = cur->right;

        if (left_child == NULL && right_child == NULL) {
            return cur;
        }

        //cout << "imhere" << endl;
        if (index <= _count_nodes(left_child)) {
            return _search_index(left_child, index);
        } else if ((index == (_count_nodes(left_child) + 1))
                || index == 0) {
        //    cout << "found " << cur->residue << endl;
            return cur;
        } else {
            return _search_index(right_child, index - 1 -
                                              _count_nodes(left_child));
        }
    }

    //void _update_segments_up
    void _right_rotate(Node* cur_root) {
        Node* first_level = cur_root->left;

        if (first_level) {
            cur_root->left = first_level->right;
            if (first_level->right) {
         //       cur_root->left->if_left = 0;
                first_level->right->parent = cur_root;
            }
            first_level->parent = cur_root->parent;
   //         first_level->if_left = cur_root->if_left;
            //cur_root->if_left = 0;
        }

        if (!cur_root->parent) root = first_level;
//        else if (cur_root->if_left) cur_root->parent->left = first_level;
        else if (cur_root->parent->left == cur_root) cur_root->parent->left = first_level;
        else cur_root->parent->right = first_level;

        if (first_level) {
            first_level->right = cur_root;
 //           cur_root->if_left = 0;
        }

        cur_root->parent = first_level;

        _update(cur_root);
  //      _update_segment_length(cur_root); //added
        _update(first_level);
 //       _update_segment_length(first_level); //added;
    }

    //right child of a right child//right right
    void _left_rotate(Node *cur_root) {
        Node* first_level = cur_root->right;

        if (first_level) {
            cur_root->right = first_level->left;
            if (first_level->left) {
  //              cur_root->right->if_left = 1;
                first_level->left->parent = cur_root;
            }
            first_level->parent = cur_root->parent;
   //         first_level->if_left = cur_root->if_left;
            //cur_root->if_left = 0;
        }

        if (!cur_root->parent) root = first_level;
//        else if (cur_root->if_left) cur_root->parent->left = first_level;
        else if (cur_root->parent->left == cur_root) cur_root->parent->left = first_level;
        else cur_root->parent->right = first_level;

        if (first_level) {
            first_level->left = cur_root;
   //         cur_root->if_left = 1;
        }

        cur_root->parent = first_level;
        _update(cur_root);
        _update(first_level);
    }



    Node* _splay(int index, Node* initial_root) {
        Node* to_root = _search_index(initial_root, index);
        //cout << to_root->residue << endl;
        while (to_root->parent) {
            Node* grandpa = to_root->parent->parent;
            Node* daddy = to_root->parent;
       /*     cout << "\n" << endl;
            _print_tree(to_root, 0);
            cout << "\nr to_root " << to_root->residue << endl;
            if (grandpa&&grandpa->parent) cout << "grandpa " << grandpa->parent->residue << endl;
            _print_tree(root, 0);
            cout << to_root->parent->residue << " dad " << daddy->residue << endl;
            cout << "\n"; */
            if (!grandpa) {
               // cout << "no grandpa" << endl;
                if (daddy->left == to_root) _right_rotate(daddy);
                else _left_rotate(daddy);
            } else if (daddy->left == to_root && grandpa->left == daddy) {
                //cout << "left left" << endl;
                _right_rotate(grandpa);
                _right_rotate(to_root->parent);
            } else if (daddy->right == to_root && grandpa->right == daddy) {
                //cout << "right right" << endl;
                _left_rotate(grandpa);
                _left_rotate(to_root->parent);
            } else if (daddy->left == to_root && grandpa->right == daddy) {
                //cout << "left right" << endl;
                _right_rotate(daddy);
                _left_rotate(to_root->parent);
            } else {
                _left_rotate(daddy);
                _right_rotate(to_root->parent);
            }
        }

 //       cout << "splay found: " << to_root->residue << " root " << root->residue << endl;

        return to_root;
    }

    triplet _split_into_three(int left, int right, Node* initial_root) {
        Node* left_middle = _splay(left, initial_root);

        Node* left_root = left_middle->left;
        //Node* middle_root = left_middle;
        //Node* right_root = NULL;

        if (left_root) {
            left_root->parent = NULL;
            left_middle->left = NULL;
            _update(left_middle);
        }
    //    _print_tree(left_middle, 0);

        //cout << "splay index " << right - left << endl;
        Node* middle_right = _splay(right - left + 1, left_middle);
    //    cout << "after middle_right" << endl;
        Node *right_root = middle_right->right;
        Node* middle_root = middle_right;
      //  _print_tree(middle_right,0);
        if (right_root) {
            right_root->parent = NULL;
            middle_right->right = NULL;
            _update(middle_right);
        }

        //cout << "can" << endl;
        /*
        cout << " l " << left_root->residue << " m " << middle_root->residue
            << " r " << right_root->residue << endl; */
        return make_tuple(left_root, middle_root, right_root);
    }

    Node* _join(Node* left_root, Node* middle_root, Node* right_root) {
        if (!left_root && !right_root) {
            return middle_root;
        } else if (!right_root) {
            Node* left_middle = _splay(1, middle_root);
            Node* left_right = _splay(_count_nodes(left_root), left_root);
            left_middle->left = left_right;
            left_right->parent = left_middle;
            _update(left_middle);

            return left_middle;
        } else if (!left_root) {
            Node* middle_right = _splay(_count_nodes(middle_root), middle_root);
            Node* right_left = _splay(1, right_root);
            middle_right->right = right_left;
            right_left->parent = middle_right;
            _update(middle_right);

            return middle_right;
        } else {
            Node* left_middle = _splay(1, middle_root);
            Node* left_right = _splay(_count_nodes(left_root), left_root);
            left_middle->left = left_right;
            left_right->parent = left_middle;
            _update(left_middle);

            Node* middle_right = _splay(_count_nodes(left_middle), left_middle);
            Node* right_left = _splay(1, right_root);
            middle_right->right = right_left;
            right_left->parent = middle_right;
            _update(middle_right);

            return middle_right;
        }
    }

    /*  shape  /   /   \    */
    void _translocate(int l, int r, int ins) {
  //      cout << "beftrans" << endl;
    //    _print_tree(root, 0);
        triplet three_roots = _split_into_three(l, r, root);
      //  cout << "trans" << endl;
        Node* left_root = get<0>(three_roots);
        Node* middle_root = get<1>(three_roots);
        Node* right_root = get<2>(three_roots);

      /*  _print_tree(left_root, 0);
        cout << "left \n";
        _print_tree(middle_root, 0);
        cout << "middle \n";
        _print_tree(right_root, 0);
        cout << "right \n"; */

      /*  Node* new_block;
        if (right_root) {
            cout << "NEW RIGHT" << endl;
            _print_tree(right_root,0);
            right_root->left = left_root;
            if (left_root) {
                left_root->parent = right_root;
            }
            _update(right_root);
            new_block = right_root;
        } else if (left_root) {
            cout << "NEW LEFT" << endl;
            new_block = left_root;
        } else {
            root = middle_root;
            return;
        } */
        Node* new_block = _join(left_root, right_root, NULL);

      //  cout << "\n\nnew block" << endl;
       // _print_tree(new_block,0);
        int merged_segment_length = _count_nodes(new_block);
        Node *to_insert = _splay(ins, new_block);

        /*cout << "toinsl" << endl;
        _print_tree(to_insert->left, 0);
        cout << "toins" << endl;
        _print_tree(to_insert,0); */

        if (ins != merged_segment_length + 1) {


            if (!to_insert->left) {
                middle_root->right = to_insert;

                to_insert->parent = middle_root;
                _update(middle_root);

                root = middle_root;
            } else {
                Node *left_attach = to_insert->left;
                to_insert->left = NULL;
                left_attach->parent = NULL;
                _update(to_insert);

                middle_root->right = to_insert;
                to_insert->parent = middle_root;
                _update(middle_root);

                Node *to_attach = _splay(1, middle_root);
                to_attach->left = left_attach;
                left_attach->parent = to_attach;
                _update(to_attach);

                root = to_attach;
            }
        } else {
            Node *to_attach = _splay(1, middle_root);
            to_attach->left = to_insert;
            to_insert->parent = to_attach;
            _update(to_attach);
            root = to_attach;
        }


//        if (left_root == NULL && right_root) {
//            Node* rightmost = _splay(right_root->count, right_root);
//            rightmost->right = middle_root;
//            middle_root->parent = rightmost;
//            _update(rightmost);
//            root = rightmost;
//        } else if (left_root && !right_root) {
//            Node* leftmost_middle = _splay(1, middle_root);
//            leftmost_middle->left = left_root;
//            left_root->parent = leftmost_middle;
//            _update(leftmost_middle);
//            root = leftmost_middle;
//        } else if (!left_root && !right_root) {
//            root = middle_root;
//        } else {  //left_root && right_root
//            right_root->left = left_root;
//            left_root->parent = right_root;
//            _update(right_root);
//
//            Node* rightmost = _splay(right_root->count, right_root);
//
//        }
    }

    void _swap(Node* cur) {
        if (cur != NULL) {
            Node *temp = cur->left;
            cur->left = cur->right;
            cur->right = temp;
        }
    }

    void _swap_top_down(Node* cur) {
        if (cur != NULL) {
            _swap(cur);
            _swap_top_down(cur->left);
           // _swap(cur);
            _swap_top_down(cur->right);
         //   _update_segment_length(cur);  //TODO change to update
            _update(cur);
        }
    }

    /* shape / /\ */
    void _reverse(int l, int r) {
        triplet three_roots = _split_into_three(l, r, root);

        Node* left_root = get<0>(three_roots);
        Node* middle_root = get<1>(three_roots);
        Node* right_root = get<2>(three_roots);

    //    cout << "is it here" << endl;
       /* if (left_root && right_root) {
            cout << "REVERSE " << left_root->residue << " "
                 << middle_root->residue
                 << right_root->residue << endl;
        }*/

    //    cout << "swbeg" << endl;
        _swap_top_down(middle_root);
      //  cout << "swaft" << endl;

        Node* final_root = _join(left_root, middle_root, right_root);
        root = final_root;
    }

    /* shape /   /\ */
    int _find_maximum_length(int l, int r) {
 //       cout << "BFRE" << endl;
   //     _print_tree(root, 0);
        triplet three_roots = _split_into_three(l, r, root);
   //     cout << "truplets found " << endl;
        Node* left_root = get<0>(three_roots);
        Node* interval_root = get<1>(three_roots);
        Node* right_root = get<2>(three_roots);
     /*   cout << left_root->residue << " " << interval_root->residue << endl;
        _print_tree(left_root, 0);
        cout << "interval" << endl;
        _print_tree(interval_root, 0);
*/
        int result = interval_root->max_sequence_length;
        Node* final_root = _join(left_root, interval_root, right_root);
        root = final_root;

     /*   if (!left_root) cout << "noleft" << endl;
        if (!right_root) cout << "noright" << endl;
        if (!interval_root) cout << "nomid" << endl; */
      //  cout << left_root->residue << " " << interval_root->residue << " " << right_root->residue << endl;
/*        cout << "=========================================================================" << endl;
        _print_tree(root, 0);
        _print_seq_data(root);*/

        return result;
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
                int result = _find_maximum_length(j, k);
               // cout << "aft" << endl;
               // _print_tree(root, 0);
//                cout << "\n\n";
              //  cout << "!!!" << result << "???";
              cout << result << endl;
            }
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

    DNAzer result;
    result.insert_sequence(dna, word_length);
//    result.print_tree(); //TODO prints out
//    cout << "\n";
    result.execute_commands(com, num_commands);
/*   result.insert_sequence(dna, word_length);
    result.print_sequence();
    //result.print_tree();
    result.insert('j', 3);
    result.insert('k', 3);
    result.insert('f', 5);
    result.insert('p', 5);
    result.print_tree();
    cout << "\n\n";
    result.splay(1);
    result.print_tree();
    cout << "\n\n";
    result.P(3, 5, 7);
    result.print_tree();
    cout << "\n\n";
    result.O(6, 9);
    result.print_tree();
    cout << "\n\n";
    result.N(2, 9);
    result.print_tree();
    result.insert('f', 3);
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    result.print_tree();
    result.N(2, 9);
    result.print_tree();
    result.insert('f', 3);
    result.N(2, 4);
    result.print_tree();*/
}
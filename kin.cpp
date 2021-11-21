//
// Created by heheszek on 17.11.2021.
//
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::stringstream;
using std::string;

using std::vector;

using perm = vector<int>;
using matrix = vector<vector<int>>;

perm read(int &num_perm, int &k) {
    cin >> num_perm >> k;
    cin.ignore();

    perm result;
    int temp;
    string read_perm;
    getline(cin, read_perm);
    stringstream numbers(read_perm);

    while(numbers >> temp) {
        result.push_back(temp);
    }

    return result;
}

void print_vector(perm v) {
    for (perm::iterator it = v.begin(); it != v.end(); it++) {
        cout << *it << ' ';
    }

    cout << '\n';
}

int parent(int node) {
    return node/2;
}

int left_child(int node) {
    return node*2;
}

int right_child(int node) {
    return (node*2) + 1;
}

bool whether_left_child(int node) {
    if (node%2 == 0) {
        return true;
    }
    else {
        return false;
    }
}

/*matrix initialize_matrix(int num_perm) {
    matrix result;

    for (int i = 0; i < num_perm; i++) {
        cout << "here " << i << " " << num_perm << endl;
        result[i][0] = 1;
        result[i][1] = 1;
    }

    return result;
}*/

void clear_tree(int length, int tree[]) {
    for (int i = 0; i < length; i++) {
        tree[i] = 0;
    }
}

void initialize_tree(int num_of_perm) {
    int length = num_of_perm*2 + 1;
    int tree[length];

    clear_tree(length, tree);
}

void insert_leaf(int tree[], int number, int num_perm, int value) {
    int index = num_perm + number - 1;
    tree[index] = value;
   // cout << index << " index " << tree[index];
}

void fill_tree(int tree[], matrix sums, int length, int l) {
    int end = length*2 + 1;
    for (int i = length; i < end; i++) {
        tree[i] = sums[i - length][l];
    }
}

int number_of_leaves(int num_per) {
    int power = ceil(log2(num_per));
    return (int)pow(2, power);
}

int sum_leaves(int tree[], int current_value, int leaves, int num_perm) {
   // cout << leaves << " c " << current_value << endl;
    int left = leaves + current_value;
    int right = leaves + num_perm - 1;

    if (left > right) {
        return 0;
    }

    //std::cout << left << " f " << right << endl;
    int sum = 0;
    int power = pow(10, 9);

   /* cout << "INTERESTING LEAVES: " << left << " TO " << right << endl;
    for(int i = left; i <= right; ++i) {
        cout << tree[i] << " ";
    } */
    //cout << endl;
    if (left != right) {
        sum = tree[left] + tree[right];
        //cout << "s " << sum << endl;
    }
    else {
        sum += tree[left];
    }

    while (parent(left) != parent(right)) {
   //     cout << left << " " << right << endl;
        if(whether_left_child(left)) {
            sum += tree[left + 1]%power;
            sum = sum%power;
        }

        if (!whether_left_child(right)) {
            sum += tree[right - 1]%power;
            sum = sum%power;
        }

        left = parent(left);
        right = parent(right);
    }

    //cout << sum << endl;
    return sum;
}

/*int give_final_sum(int summed, int num_perm, int k) {
    int sum = 0;
    int power = pow(10, 9);

    for (int i = 1; i < num_perm; i++) {
        sum += summed[i][k]%power;
    }

    return sum;
}*/
void add_to_parents(int tree[], int index) {
    int mommy;
    int power = pow(10, 9);
    int value = tree[index]%power;


    while (index != 1) {
        mommy = parent(index);
        tree[mommy] += value;
        tree[mommy] = tree[mommy]%power;
        index = mommy;
    }
}

int num_inversions(int num_perm, int k, perm permvec) {
    if (num_perm == 1 && k == 1) return 1;

    int sums[num_perm][k + 1];

    for (int i = 0; i < num_perm; i++) {
        sums[i][0] = 0;
        sums[i][1] = 1;
    }

    int leaves = number_of_leaves(num_perm);
    //matrix sums = initialize_matrix(num_perm);
    int tree_length = leaves*2;
    int tree[tree_length];
    //clear_tree(tree_length, tree);

    for (int l = 2; l < k + 1; l++) {
        clear_tree(tree_length, tree);
        //insert_leaf(tree, permvec[0], num_perm, 1);
        // tree[leaves] is the first leaf
//        tree[leaves + permvec[0] - 1] = 1;
//        add_to_parents(tree, leaves + permvec[0] - 1);

        for (int i = 0; i < num_perm; i++) {
         //   cout << "i: " << i << "l: " << l << endl;
            sums[i][l] = sum_leaves(tree, permvec[i], leaves, num_perm);
            //cout << "SUMS " << i << "." << l << ": " << sums[i][l] << endl;
            //insert_leaf(tree, permvec[i], num_perm, sums[i][l-1]);
            tree[leaves + permvec[i] - 1] = sums[i][l - 1];
            add_to_parents(tree, leaves + permvec[i] - 1);
        }

   /*     for (int k = 0; k < tree_length; k++) {
            cout << tree[k] << " ";
        }
        cout << endl;
        for (int a = 0; a < num_perm; a++) {
            for (int b = 0; b < k + 1; b++) {
                cout << sums[a][b] << " ";
            }
        cout << endl;
        }*/

    }


    int sum = 0;
    int power = pow(10, 9);

    for (int i = 0; i < num_perm; i++) {
      //  cout << i <<": " << sums[i][k] << endl;
        sum += sums[i][k]%power;
        sum = sum%power;
    }
    //int result = give_final_sum(sums, num_perm, k);

    return sum;
}

int main(void) {
    int length;
    int k;

    //cout << ceil(log2(4));
    perm permutation = read(length, k);
    //print_vector(permutation);
    int result = num_inversions(length, k, permutation);
    cout << result << endl;

    return 0;
}
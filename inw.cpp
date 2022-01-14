//
// Created by heheszek on 14.01.2022.
//
#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

using std::vector;

using vec_int = vector<int>;

vec_int read_input(int &num_nodes) {
    cin >> num_nodes;

    int node;
    vec_int result;
    for (int i = 0; i < num_nodes; i++) {
        cin >> node;
        result.push_back(node);
    }

    return result;
}

void print_vector(vec_int &inv) {
    for (int i: inv) {
        cout << i << " ";
    }

    cout << endl;
}

vec_int find_limits(vec_int &inversion, int num_nodes) {
    int max = inversion[0];

    vec_int limits;
    for (int i = 1; i < num_nodes; i++) {
        int current_node = inversion[i];
        if (max == i - 1) {
            limits.push_back(i);
        }
        if (current_node > max) {
            max = current_node;
        }
    }

    return limits;
}

int size(int start, int end) {
    return end - start;
}

void print_range(int range, int start) {
    for (int i = start; i < start + range; i++) {
        cout << i << " ";
    }

    cout << endl;
}

void print_row(int range, int start) {
    cout << range << " ";
    print_range(range, start);
}

void print_result(vec_int found_limits) {
    int num_limits = found_limits.size();

    for (int i = 0; i < num_limits - 1; i++) {
        int range = size(found_limits[i], found_limits[i + 1]);
        print_row(range, found_limits[i]);
    }
}

int main() {
    int num_nodes;
    vec_int inversion = read_input(num_nodes);
    cout << num_nodes << endl;
    print_vector(inversion);

    vec_int limits = find_limits(inversion, num_nodes);
    print_result(limits);

    return 0;
}
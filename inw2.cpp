//
// Created by heheszek on 29.01.2022.
//
#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

using std::vector;

using vec_int = vector<int>;

vec_int read_input_find_components(int &num_nodes) {
    cin >> num_nodes;

    vec_int components;
    int cur_node;
    cin >> cur_node;
    if (cur_node == 1) {
        components.push_back(1);
    }
    cout << cur_node << endl;
    int max = cur_node;
    for (int i = 1; i < num_nodes; i++) {
        cin >> cur_node;
        cout << cur_node << " max: " << max << " i: " << i << endl;
        if (max == i) {
            components.push_back(cur_node);
        }

        if (max < cur_node) {
            max = cur_node;
        }
    }

    return components;
}

void print_components(vec_int &components) {
    cout << "components\n";
    for (int i: components) {
        cout << i << " ";
    }

    cout << endl;
}

void print_content_of_components(int beg, int end) {
    cout << end - beg;
    for (int i = beg; i < end; i++) {
        cout << " " << i;
    }
    cout << endl;
}

void print_result_components(vec_int &components, int num_nodes) {
    int comp_lenght = components.size();

    cout << "l " << comp_lenght + 1 << endl;

    if (!components.empty()) {
        int prev = 1;
        int beg = 0;
        if (components[0] == 1) {
            cout << "1 1\n";
            beg = 1;
        }

        for (int i = beg; i < comp_lenght; i++) {
            print_content_of_components(prev, components[i]);
            prev = components[i];
        }

        print_content_of_components(prev, num_nodes + 1);
    } else {
        cout << 1;
        for (int i = 1; i <= num_nodes; i++) {
            cout << " " << i;
        }

        cout << endl;
    }
}

int main() {
    int num_nodes;
    vec_int components = read_input_find_components(num_nodes);
    print_components(components);
    print_result_components(components, num_nodes);
}
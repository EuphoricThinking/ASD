//
// Created by heheszek on 29.01.2022.
//
#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

using std::vector;
using std::pair;

using std::make_pair;

using data = pair<int, int>;
using vec_int = vector<data>;

vec_int read_input_find_components(int &num_nodes) {
    cin >> num_nodes;

    vec_int components;
    int cur_node;
    cin >> cur_node;
    int comp_size = 0;
    if (cur_node == 1) {
        components.push_back(make_pair(1, 1));
        comp_size++;
    }
//    cout << cur_node << endl;
    int max = cur_node;
    int counter = 1;
    for (int i = 1; i < num_nodes; i++) {
        cin >> cur_node;
        //cout << cur_node << " max: " << max << " i: " << i << endl;
        counter++;
        //cout << "c " << counter << " cur: " << cur_node << endl;
        if (max == i) {
            //components.push_back(make_pair(cur_node, -1));

            if (comp_size == 0) {
                components.push_back(make_pair(cur_node, counter - 1));
            } else {
                data &prev = components[comp_size - 1];
 //               cout << "count " << counter << endl;
                prev = make_pair(prev.first, counter - 1);
 //               cout << "here " << prev.first << " " << prev.second << endl;
                components.push_back(make_pair(cur_node, counter - 1));
            }

            comp_size++;
            counter = 1;
        }

        if (max < cur_node) {
            max = cur_node;
        }
    }

    data &last = components[components.size() - 1];
    last = make_pair(last.first, counter);

    return components;
}

void print_components(vec_int &components) {
    cout << "components\n";
    for (data i: components) {
        cout << i.first << " dist: " << i.second << endl;
    }
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

    //cout << "l " << comp_lenght + 1 << endl;

    if (comp_lenght != 0) {
        if (components[0].first != 1) {
            cout << comp_lenght + 1 << endl;
            print_content_of_components(1, components[0].first);
        } else {
            cout << comp_lenght << endl;
        }

        data prev;
        for (int i = 0; i < comp_lenght; i++) {
            prev = components[i];
            print_content_of_components(prev.first - prev.second + 1, prev.first + 1);
        }
    } else {
        cout << 1 << endl;
        for (int i = 1; i <= num_nodes; i++) {
            cout << " " << i;
        }

        cout << endl;
    }
}

int main() {
    int num_nodes;
    vec_int components = read_input_find_components(num_nodes);
    //print_components(components);
    print_result_components(components, num_nodes);
}
//
// Created by heheszek on 30.01.2022.
//

//
// Created by heheszek on 29.01.2022.
//
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;

using std::vector;
using std::pair;

using std::make_pair;

using data = vector<int>;
using vec_int = vector<data>;

vec_int read_input_find_components(int &num_nodes) {
    cin >> num_nodes;

    vec_int components;
    int cur_node;
    cin >> cur_node;
    int comp_size = 1;
//    if (cur_node == 1) {
//        data v{1};
//        components.push_back(v);
//        comp_size++;
//    }
//    cout << cur_node << endl;
    data v{cur_node};
    components.push_back(v);

    int max = cur_node;
    for (int i = 1; i < num_nodes; i++) {
        cin >> cur_node;
        //cout << cur_node << " max: " << max << " i: " << i << endl;
        //cout << "c " << counter << " cur: " << cur_node << endl;
        if (max == i) {
            data v{cur_node};
            components.push_back(v);
            comp_size++;
        } else {
            data &prev = components[comp_size - 1];
            prev.push_back(cur_node);
        }

        if (max < cur_node) {
            max = cur_node;
        }
    }

//    data &last = components[components.size() - 1];
//    last = make_pair(last.first, counter);

    return components;
}

//void print_components(vec_int &components) {
//    cout << "components\n";
//    for (data i: components) {
//        cout << i.first << " dist: " << i.second << endl;
//    }
//}

//void print_content_of_components(int beg, int end) {
//    cout << end - beg;
//    for (int i = beg; i < end; i++) {
//        cout << " " << i;
//    }
//    cout << endl;
//}

void print_content_of_a_component(data &v) {
    cout << v.size();
    std::sort(v.begin(), v.end());
    for (int i: v) {
        cout << " " << i;
    }

    cout << endl;
}

void print_result_components(vec_int &components, int num_nodes) {
    int comp_lenght = components.size();

    //cout << "l " << comp_lenght + 1 << endl;

//    if (comp_lenght != 0) {
//        if (components[0].first != 1) {
//            cout << comp_lenght + 1 << endl;
//            print_content_of_components(1, components[0].first);
//        } else {
//            cout << comp_lenght << endl;
//        }
//
//        data prev;
//        for (int i = 0; i < comp_lenght; i++) {
//            prev = components[i];
//            print_content_of_components(prev.first - prev.second + 1, prev.first + 1);
//        }
//    } else {
//        cout << 1 << endl;
//        for (int i = 1; i <= num_nodes; i++) {
//            cout << " " << i;
//        }
//
//        cout << endl;
//    }
    cout << comp_lenght << endl;
    for (data v: components) {
        print_content_of_a_component(v);
    }
}

int main() {
    int num_nodes;
    vec_int components = read_input_find_components(num_nodes);
    //print_components(components);
    print_result_components(components, num_nodes);
}
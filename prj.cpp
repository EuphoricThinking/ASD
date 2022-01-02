//
// Created by heheszek on 02.01.2022.
//
#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>


using std::pair;
using std:: vector;
using std::unordered_map;
using std::priority_queue;

using std:: make_pair;
using std::endl;
using std::cout;
using std::cin;
using std::greater;

using outcoming = vector<int>;
using weights = pair<int, int>;
using num_outcoming = int;
using node_number = int;
using dependency = pair<outcoming, num_outcoming>;
using node_data = unordered_map<node_number, dependency>;
using topo_queue = priority_queue<weights, vector<int>, greater<>>;

topo_queue read_input(int &num_projects, int &num_dependencies, node_data &nodes,
                      int &required_projects) {
    cin >> num_projects >> num_dependencies >> required_projects;

    int num_programmers;
    topo_queue results;
    for (int i = 0; i < num_projects; i++) {
        cin >> num_programmers;
        weights new_weight = make_pair(nu)
    }
}

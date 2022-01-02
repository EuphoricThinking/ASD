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
using std::tuple;

using std:: make_pair;
using std::make_tuple;
using std::endl;
using std::cout;
using std::cin;
using std::greater;
using std::get;
using std::tie;

using outcoming = vector<int>;
using weights = pair<int, int>;
using num_incoming = int;
using node_number = int;
using num_employers = int;
using node_data = tuple<num_employers, outcoming, num_incoming>;
using node_containter = vector<node_data>;
using topo_queue = priority_queue<weights, vector<weights>, greater<>>;

node_containter read_input(int &num_projects, int &num_dependencies,
                      int &required_projects) {
    cin >> num_projects >> num_dependencies >> required_projects;

    int num_programmers;
    node_containter nodes;
    for (int i = 0; i < num_projects; i++) {
        cin >> num_programmers;
        outcoming o;
        node_data new_data = make_tuple(num_programmers, o, 0);
        nodes.push_back(new_data);
    }

    int from_node;
    int to_node;

    for (int i = 0; i < num_dependencies; i++) {
        cin >> from_node >> to_node;

        num_incoming &referenced_inputs = get<2>(nodes[to_node - 1]);
        outcoming &outcomes = get<1>(nodes[from_node - 1]);

        referenced_inputs++;
        outcomes.push_back(to_node);
    }

    return nodes;
}

void print_vector(vector<int> vc) {
    for (vector<int>::iterator iter = vc.begin(); iter != vc.end(); iter++) {
        cout << *iter << " ";
    }
}

void print_node_container(node_containter ndc, int num_prj) {
    for (int i = 0; i < num_prj; i++) {
        int programmers = get<0>(ndc[i]);
        outcoming outs = get<1>(ndc[i]);
        int ins = get<2>(ndc[i]);

        cout << i + 1 << " programmers: " << programmers << " | deps : ";
        print_vector(outs);
        cout << " | ins: " << ins << endl;
    }
    cout << endl;
}
void print_data(int num_prj, int num_dep, int k, node_containter ndc) {
    cout << num_prj << " " << num_dep << " " << k << endl;
    print_node_container(ndc, num_prj);
}

topo_queue create_queue(node_containter nodes, int num_prj) {
    topo_queue result;

    for (int i = 0; i < num_prj; i++) {
        node_data current = nodes[i];
        int ins = get<2>(current);

        if (ins == 0) {
            int programmers = get<0>(current);
            weights new_weight = make_pair(programmers, i + 1);
            result.push(new_weight);
        }
    }

    return result;
}

void print_queue(topo_queue tq) {
    while (!tq.empty()) {
        weights wg = tq.top();
        cout << "weight: " << wg.first << " number: " << wg.second << endl;
        tq.pop();
    }
}

int find_programmers(topo_queue &tq, int k, node_containter &nodes) {
    int counter_popped = 0;
    int max_num_programmers = 0;

    weights node;
    int programmers;
    int node_number;

    while (counter_popped != k) {//(counter_popped != k && !(tq.empty())) {
        node = tq.top();
        tq.pop();
        counter_popped++;

        programmers = node.first;
        node_number = node.second;

        if (programmers > max_num_programmers) {
            max_num_programmers = programmers;
        }

        node_data info = nodes[node_number - 1];
        outcoming &outs = get<1>(info);
        int inputs = get<2>(info);

        for (outcoming::iterator iter = outs.begin(); iter != outs.end(); iter++) {
            int adjacent_number = (*iter) - 1;
            node_data adjacent_tuple = nodes[adjacent_number];
            int &adjacent_inputs = get<2>(adjacent_tuple);
            adjacent_inputs--;

            if (adjacent_inputs == 0) {
               int employers = get<0>(adjacent_tuple);
               weights new_weight = make_pair(employers, *iter);
               tq.push(new_weight);
            }
        }
    }

    return max_num_programmers;
}

int main(void) {
    int num_projects, num_dependencies, k;
    node_containter nodes = read_input(num_projects, num_dependencies, k);
    //print_data(num_projects, num_dependencies, k, nodes);

    topo_queue no_inputs = create_queue(nodes, num_projects);
    //print_queue(no_inputs);
    int result = find_programmers(no_inputs, k, nodes);
    cout << result << endl;
}
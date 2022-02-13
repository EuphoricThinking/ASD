//
// Created by heheszek on 13.02.2022.
//
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::make_tuple;
using std::make_pair;
using std::get;
using std::max;

using std::vector;
using std::tuple;
using std::pair;

using alarm_values = std::unordered_set<int>;
using powerbank_value = int;
using junction_number = int;
using adjacent_junctions = vector<int>;
using distance = int;
//using adjacent_and_powerbanks = tuple<adjacent_junctions, powerbank_value>;
using adjacent_and_powerbanks = pair<adjacent_junctions, powerbank_value>;
using tracks = std::unordered_map<junction_number, adjacent_and_powerbanks>;
using available_power = vector<int>;
using path = vector<int>;
using chargers = vector<int>;
using std::queue;
using trackiter = tracks::iterator;
using iter_0 = pair<trackiter, int>;

void insert_into_map(int road_in, int road_out, tracks & junctions) {
    auto found_junction = junctions.find(road_in);

    if (found_junction == junctions.end()) {
        adjacent_junctions adj;
        adj.push_back(road_out);
        adjacent_and_powerbanks adj_pow = make_pair(adj, -1);
        junctions.insert(make_pair(road_in, adj_pow));
    } else {
        adjacent_and_powerbanks & adj_pow = found_junction->second;
        adjacent_junctions & adj = adj_pow.first;
        adj.push_back(road_out);
    }
}

alarm_values read_data(tracks &junctions, int &capacity, int &cost,
                       int &disallowed, int &num_of_junctions, int &num_of_roads,
                       available_power &powerbanks) {
    cin >> capacity >> cost >> disallowed;

    int forbidden_val;
    alarm_values set_of_forbidden;

    for (int i = 0; i < disallowed; i++) {
        cin >> forbidden_val;
        set_of_forbidden.insert(forbidden_val);
    }

    cin >> num_of_junctions >> num_of_roads;

    int road_in;
    int road_out;

    for (int i = 0; i < num_of_roads; i++) {
        cin >> road_in >> road_out;

        insert_into_map(road_in, road_out, junctions);
        insert_into_map(road_out, road_in, junctions);
    }

    int power_value;
    for (int i = 0; i < num_of_junctions; i++) {
        cin >> power_value;
        powerbanks.push_back(power_value);
    }

    return set_of_forbidden;
}

void assign_powerbank_value(tracks & junctions, int junction_num, int val) {
    auto junc_iter = junctions.find(junction_num);
    adjacent_and_powerbanks & adj_pow = junc_iter->second;
    adj_pow.second = val;
}

iter_0 push_into_queue_without_0(queue<int> & levels, tracks & junctions, int num_junc) {
    auto found_junc = junctions.find(num_junc);
    adjacent_junctions adj_junc = found_junc->second.first;
    uint64_t size = adj_junc.size();
    for (uint64_t i = size - 1; i >= 0; i++) {
        levels.push(adj_junc[i]);
    }

    if (size >= 1) return make_pair(found_junc, adj_junc[0]);
    else return make_pair(found_junc, -1);
}

void assign_distance(trackiter iter, int dist) {
    adjacent_and_powerbanks & adj_pow
}

void find_shortest_path_assign_powerbank_values(tracks & junctions,
                                                int num_junctions,
                                                available_power powerbanks) {
    assign_powerbank_value(junctions, 1, powerbanks[0]);
    int distance = 1;
    vector<bool> visited(num_junctions + 1, false);
    visited[1] = true;
    queue<int> levels_queued;
    bool found = false;

    int next_level = push_into_queue_without_0(levels_queued, junctions, 1);
    int temp_level;
    while (!levels_queued.empty()) {
        int next_junc = levels_queued.front();
        levels_queued.pop();
        temp_level = push_into_queue_without_0(levels_queued, )

    }
}
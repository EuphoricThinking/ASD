//
// Created by heheszek on 13.02.2022.
//
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>

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


iter_0 push_into_queue_without_0(queue<int> & levels, tracks & junctions, int num_junc,
                                 vector<int> & preceding) {
    auto found_junc = junctions.find(num_junc);
    adjacent_junctions adj_junc = found_junc->second.first;
    uint64_t size = adj_junc.size();
    for (uint64_t i = size - 1; i >= 0; i++) {
        levels.push(adj_junc[i]);

        if (preceding[adj_junc[i]] == -1) {
            preceding[adj_junc[i]] = num_junc;
        }
    }

    if (size >= 1) return make_pair(found_junc, adj_junc[0]);
    else return make_pair(found_junc, -1);
}

void assign_powerbank_value(trackiter & iter, int val) {
    adjacent_and_powerbanks & adj_pow = iter->second;
    adj_pow.second = val;
}

vector<int> find_shortest_path_assign_powerbank_values(tracks & junctions,
                                                int num_junctions,
                                                available_power powerbanks) {
    queue<int> levels_queued;
    vector<int> preceding(num_junctions + 1, -1);
    preceding[1] = 1;
    iter_0 init = push_into_queue_without_0(levels_queued, junctions, 1, preceding);
    assign_powerbank_value(init.first, powerbanks[0]);
    vector<bool> visited(num_junctions + 1, false);
    visited[1] = true;

    int next_level = init.second;
    int distance = 1;
    iter_0 temp_level;

    while (!levels_queued.empty()) {
        int next_junc = levels_queued.front();
        levels_queued.pop();

        if (!visited[next_junc]) {
            visited[next_junc] = true;
            temp_level = push_into_queue_without_0(levels_queued, junctions,
                                                   next_junc, preceding);

            if (next_level == next_junc) {
                if (temp_level.second != -1) next_level = temp_level.second;
                else next_level = -1;

                distance++;
            } else if (next_level == -1) {
                if (temp_level.second != -1) next_level = temp_level.second;
            }

            assign_powerbank_value(temp_level.first, powerbanks[distance]);
        }
    }

    vector<int> shortest_path;
    shortest_path.push_back(num_junctions);
    int cur = num_junctions;

    while (cur != 1) {
        shortest_path.push_back(preceding[cur]);
        cur = preceding[cur];
    }

    std::reverse(shortest_path.begin(), shortest_path.end());

    return shortest_path;
}
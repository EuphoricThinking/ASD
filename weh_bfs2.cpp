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


void log(const char* message) {
    cout << message << endl;
}

void print_vec(const vector<int> & v) {
    for (int i: v) {
        cout << i << " ";
    }
    cout << endl;
}

void print_map(const tracks & junctions) {
    for (const auto & junction : junctions) {
        cout << junction.first << ": ";
        print_vec(junction.second.first);
        cout << junction.second.second << "\n\n";
    }
}

void print_set(const std::unordered_set<int> & unrds) {
    for (const auto & val: unrds) {
        cout << val << " ";
    }

    cout << endl;
}

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
        //cout << "roads " << i << endl;
        insert_into_map(road_in, road_out, junctions);
        insert_into_map(road_out, road_in, junctions);
    }

    int power_value;
    for (int i = 0; i < num_of_junctions; i++) {
        cin >> power_value;
        //cout << "pow " << power_value << " " << i << endl;
        powerbanks.push_back(power_value);
    }

    return set_of_forbidden;
}


iter_0 push_into_queue_without_0(queue<int> & levels, tracks & junctions, int num_junc,
                                 vector<int> & preceding,
                                 const vector<bool> & visited) {
    auto found_junc = junctions.find(num_junc);
    adjacent_junctions adj_junc = found_junc->second.first;
    int size = (int)adj_junc.size();

    int first_not_visited = 0;
    for (int i = 0; i < size; i++) {
        if (!visited[adj_junc[i]]) {
            first_not_visited = i;
            break;
        }
    }

    for (int i = size - 1; i >= first_not_visited; i--) {
        levels.push(adj_junc[i]);
        if (preceding[adj_junc[i]] == -1) {
            preceding[adj_junc[i]] = num_junc;
        }
    }
    log("after all");
    if (size >= 1) return make_pair(found_junc, adj_junc[first_not_visited]);
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
    vector<bool> visited(num_junctions + 1, false);
    visited[1] = true;

    iter_0 init = push_into_queue_without_0(levels_queued, junctions, 1, preceding,
                                            visited);
    assign_powerbank_value(init.first, powerbanks[0]);

    int next_level = init.second;
    int distance = 1;
    iter_0 temp_level;
    log("after first");
    while (!levels_queued.empty()) {
        int next_junc = levels_queued.front();
        levels_queued.pop();

        if (!visited[next_junc]) {
            cout << next_junc << " next_level: " << next_level << " dist: " << distance << endl;
            visited[next_junc] = true;
            temp_level = push_into_queue_without_0(levels_queued, junctions,
                                                   next_junc, preceding, visited);
            log("ass");
            assign_powerbank_value(temp_level.first, powerbanks[distance]);
            log("died");
            if (next_level == next_junc) {
                if (temp_level.second != -1) next_level = temp_level.second;
                else next_level = -1;

                distance++;
            } else if (next_level == -1) {
                if (temp_level.second != -1) next_level = temp_level.second;
            }
        }
    }
    log("after while");
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

int main() {
    int capacity;
    int cost;
    int disallowed;
    int num_junctions;
    int num_roads;

    tracks junctions;
    available_power powerbanks;

    alarm_values forbidden = read_data(junctions, capacity, cost, disallowed,
                                       num_junctions, num_roads, powerbanks);

    //print_vec(powerbanks);
    //print_set(forbidden);
    //print_map(junctions);
    print_map(junctions);

    vector<int> shortest_path = find_shortest_path_assign_powerbank_values(junctions,
                                                                           num_junctions,
                                                                           powerbanks);

    print_map(junctions);
    print_vec(shortest_path);

    return 0;
}
//
// Created by heheszek on 14.02.2022.
//
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

const int MAX_ROW = 1002;
const int MAX_COL = 5002;
int if_previous_charged[MAX_ROW][MAX_COL]; //[path_length][capacity + 1];
//przejdź po kolumnach, by znaleźć największe
//wysstarczy znac numer kolumny - zawsze przejedzam o +1 wzgledem sciezki
int previous_coordinates[MAX_ROW][MAX_COL];
int last_charging[MAX_COL];


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


void push_into_queue(queue<int> & levels, tracks & junctions, int num_junc,
                     vector<int> & preceding,
                     vector<bool> & visited,
                     vector<int> & distances,
                     const available_power & powerbanks) {
    auto found_junc = junctions.find(num_junc);
    //adjacent_junctions adj_junc = found_junc->second.first;
    adjacent_and_powerbanks & adj_pow = found_junc->second;
    adjacent_junctions adj_junc = adj_pow.first;
    adj_pow.second = powerbanks[distances[num_junc]];

    int size = (int)adj_junc.size();

    for (int i = 0; i < size; i++) {
        if (!visited[adj_junc[i]]){
            levels.push(adj_junc[i]);
            preceding[adj_junc[i]] = num_junc;
            distances[adj_junc[i]] = distances[num_junc] + 1;
            visited[adj_junc[i]] = true;
        }
    }
}

void assign_powerbank_value(trackiter & iter, int val) {
    adjacent_and_powerbanks & adj_pow = iter->second;
    adj_pow.second = val;
}

vector<int> find_shortest_path_assign_powerbank_values(tracks & junctions,
                                                       int num_junctions,
                                                       const available_power & powerbanks) {
    queue<int> levels_queued;
    vector<int> preceding(num_junctions + 1, -1);
    preceding[1] = 1;
    vector<bool> visited(num_junctions + 1, false);
    visited[1] = true;
    vector<int> distances(num_junctions + 1, -1);
    distances[1] = 0;

    push_into_queue(levels_queued, junctions, 1, preceding, visited, distances,
                    powerbanks);
    //   int shortest_distance = 0;//-1;//0;
    //log("after first");
    //int found_dist = 0; //0;  //TODO -1 powoduje runtime error
//    int shortest_distance = -1;
    while (!levels_queued.empty()) {
        int next_junc = levels_queued.front();
        levels_queued.pop();
//        shortest_distance = 0;

        //cout << next_junc << " next_level: " << next_level << " dist: " << distance << endl;
        push_into_queue(levels_queued, junctions, next_junc, preceding, visited, distances,
                        powerbanks);
        //log("ass");
        //        if (next_junc == num_junctions) shortest_distance = distances[next_junc];      //found_dist = distance;  //TODO tested outside with -1, there's something wrong
    }
    //log("after while");
    //cout << found_dist << endl;
    // TODO: SPRAWDZIĆ CZY JEST POŁACZENIE W OGÓLE OD 1 DO NUM_JUNCTIONS (czy visited = true)++
    if (!visited[num_junctions]) return vector<int>(1, -1);
    int shortest_distance = distances[num_junctions];
//    cout << shortest_distance << endl;
    vector<int> shortest_path(shortest_distance + 1, -1);
    int cur = num_junctions;
//    shortest_path.push_back(num_junctions);
//
//    while (cur != 1) {
//        shortest_path.push_back(preceding[cur]);
//        cur = preceding[cur];
//    }
//
//    std::reverse(shortest_path.begin(), shortest_path.end());

/*
 * found changed to 0, but when it's the case?
 */
    shortest_path[shortest_distance] = num_junctions; //TODO THIS PART CAUSES RUNTIME ERROR
    for (int i = shortest_distance - 1; i >= 0; i--) {
//        cout << i <<  endl;
        shortest_path[i] = preceding[cur];
        cur = preceding[cur];
    }

    return shortest_path;
}

/*
 * End of BFS
 */

bool is_charging_possible(int available_power, int cur_cap, int capacity, const alarm_values & forbidden_values) {
    cur_cap += available_power;
    if (cur_cap <= capacity
    && forbidden_values.find(cur_cap) == forbidden_values.end()) return true;
    return false;
}

int give_power(const tracks & junctions, int cur_junc) {
    adjacent_and_powerbanks adj_pow = junctions.find(cur_junc)->second;
    return adj_pow.second;
}

void fill_one_cell(int cur_cap, int cur_pos, int cost, int from, bool from_charging) {
    int new_capacity = cur_cap - cost;
    if (new_capacity >= 0) {
        previous_coordinates[cur_pos + 1][new_capacity] = from;
        if (from_charging) if_previous_charged[cur_pos + 1][new_capacity] = 1;
    }
}
void fill_next_row(int cur_pos, int cur_cap, int capacity, const alarm_values & forbidden,
                   const tracks & junctions, int cost, int cur_junc) {
    fill_one_cell(cur_cap, cur_pos, cost, cur_cap, false);

    int available_power = give_power(junctions, cur_junc);
    if (is_charging_possible(available_power, cur_cap, capacity,
                             forbidden)) {
        int new_capacity = cur_cap + available_power;
        fill_one_cell(new_capacity, cur_pos, cost, cur_cap, true);
//        if_previous_charged[cur_pos + 1][new_capacity] = 1;


    }
}

int find_max_row(int path_length, int capacity) {
    int max_cap = -1;
    for (int j = capacity; j >= 0; j--) {
        if (previous_coordinates[path_length - 1][j] != -1
            && j > max_cap) {
            max_cap = j;
            break;
        }
    }

    return max_cap;
}

void find_chargers(int max_cap, vector<int> & chargers, int path_length,
                   const vector<int> & shortest) {
    int i = path_length - 1;
    int j = max_cap;

    while (i != 0) {
        if (if_previous_charged[i][j]) chargers.push_back(shortest[i - 1]);

        j = previous_coordinates[i][j];
        i--;
    }
}

void print_matrix(int path_length, int capacity) {
    for (int i = 0; i < path_length; i++) {
        for (int j = 0; j < capacity + 1; j++) {
            cout << previous_coordinates[i][j] << "|" << if_previous_charged[i][j] << " ";
        }
        cout << endl;
    }
}

bool if_possible_short_path(const tracks & junctions, const path & shortest,
                          int capacity, int & max_score, const alarm_values & forbidden_values,
                          int cost, vector<int> & chargers) {
    int path_length = shortest.size();

    for (int i = 0; i < path_length; i++) {
        for (int j = 0; j < capacity + 1; j++) {
            if_previous_charged[i][j] = 0;
            previous_coordinates[i][j] = -1;
            last_charging[j] = -1;
        }
    }

    fill_next_row(0, capacity, capacity, forbidden_values, junctions, cost,
                  shortest[0]);

    for (int i = 1; i < path_length - 1; i++) {
        for (int j = 0; j < capacity + 1; j++) {
            if (previous_coordinates[i][j] != -1) {
                fill_next_row(i, j, capacity, forbidden_values, junctions, cost,
                              shortest[i]);
            }
        }
    }

    print_matrix(path_length, capacity);

    int max_cap = find_max_row(path_length, capacity);

    if (max_cap == -1) return false;

    int available_power = give_power(junctions, shortest[path_length - 1]);
    if (is_charging_possible(available_power, max_cap, capacity, forbidden_values)) {
        log("possible");
        chargers.push_back(shortest[path_length - 1]);
        max_score = max_cap + available_power;
    } else {
        max_score = max_cap;
    }

    find_chargers(max_cap, chargers, path_length, shortest);

    return true;
}


void print_chargers_reverse(chargers used_chargers) {
    for (chargers::reverse_iterator riter = used_chargers.rbegin(); riter != used_chargers.rend(); riter++) {
        cout << *riter << " ";
    }

    cout << endl;
}

void print_path(path &shortest) {
    for (path::iterator piter = shortest.begin(); piter != shortest.end(); piter++) {
        cout << *piter << " ";
    }

    cout << endl;
}

void print_result(bool shortest_is_possible, path &shortest_path,
                  chargers &used_chargers, int current_power) {
    if (shortest_is_possible) {
        cout << shortest_path.size() << " " << current_power << " "
             << used_chargers.size() << endl;

        print_path(shortest_path);

        print_chargers_reverse(used_chargers);
    } else {
        cout << -1 << endl;
    }
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

    //shortest path - RUNTIME ERROR
    vector<int> shortest_path = find_shortest_path_assign_powerbank_values(junctions,
                                                                           num_junctions,
                                                                           powerbanks);
    print_set(forbidden);
    print_map(junctions);
    if (shortest_path[0] == -1) {
        cout << -1 << endl;
        return 0;
    }
//    //TODO without runtime error up to this part

    int max_score = -1;
    chargers used_chargers;

    //print_vec(shortest_path);
    //   cout << "here" << endl;
    bool is_possible_shortest = if_possible_short_path(junctions, shortest_path,
                                                       capacity, max_score,
                                                       forbidden, cost,
                                                       used_chargers);
    if (max_score > capacity) {
        cout << -1 << endl;
        return 0;
    }
    print_result(is_possible_shortest, shortest_path, used_chargers, max_score);

    return 0;
}




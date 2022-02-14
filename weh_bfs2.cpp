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
    //log("after all");
    if (size >= 1) return make_pair(found_junc, adj_junc[first_not_visited]);
    else return make_pair(found_junc, -1);
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

    iter_0 init = push_into_queue_without_0(levels_queued, junctions, 1, preceding,
                                            visited);
    assign_powerbank_value(init.first, powerbanks[0]);

    int next_level = init.second;
    int distance = 1;
    iter_0 temp_level;
    //log("after first");
    int found_dist = 0; //0;
    while (!levels_queued.empty()) {
        int next_junc = levels_queued.front();
        levels_queued.pop();

        if (!visited[next_junc]) {
            //cout << next_junc << " next_level: " << next_level << " dist: " << distance << endl;
            visited[next_junc] = true;
            temp_level = push_into_queue_without_0(levels_queued, junctions,
                                                   next_junc, preceding, visited);
            //log("ass");
            if (next_junc == num_junctions) found_dist = distance;  //TODO tested outside with -1, there's something wrong
            assign_powerbank_value(temp_level.first, powerbanks[distance]);
            //log("died");
            if (next_level == next_junc) {
                if (temp_level.second != -1) next_level = temp_level.second;
                else next_level = -1;

                distance++;
            } else if (next_level == -1) {
                if (temp_level.second != -1) next_level = temp_level.second;
            }
        }
    }
    //log("after while");
    //cout << found_dist << endl;
    vector<int> shortest_path(found_dist + 1, -1);
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
    shortest_path[found_dist] = num_junctions; //TODO THIS PART CAUSES RUNTIME ERROR
    for (int i = found_dist - 1; i >= 0; i--) {
        //cout << i <<  endl;
        shortest_path[i] = preceding[cur];
        cur = preceding[cur];
    }

    return shortest_path;
}

/*
 * End of BFS
 */

void charge_if_possible(int &available_power, int &current_power,
                        alarm_values &forbidden_powers, int capacity,
                        chargers &used_chargers, int junc_num) {
    if (available_power == -1) return;

    int new_value = current_power + available_power;
    cout << " cur " << current_power << " avail " << available_power << " new " << new_value << endl;
    if (new_value <= capacity &&
        forbidden_powers.find(new_value) == forbidden_powers.end()) {
        current_power = new_value;
        used_chargers.push_back(junc_num);
        available_power = -1;
    }
}

bool if_possible_charging(int available_power, int &current_power, alarm_values &forbidden,
                          int capacity) {
    int new_value = current_power + available_power;
    if (new_value <= capacity
        && forbidden.find(new_value) == forbidden.end()) {
        current_power = new_value;
        return true;
    }
    return false;
}

int give_power(tracks &junction, path shortest_path, int cur_pos) {
    tracks::iterator found_junc = junction.find(shortest_path[cur_pos]);
    adjacent_and_powerbanks &roads_powers = found_junc->second;
    int junction_power = get<1>(roads_powers);

    return junction_power;
}

void fill_next_row(int cur_pos, int cur_cap, tracks &junction, alarm_values &forbidden,
                   int capacity,
                   path &shortest_path, int cost) {

    int junction_power = give_power(junction, shortest_path, cur_pos);

    if (cur_cap - cost >= 0) {
        previous_coordinates[cur_pos + 1][cur_cap - cost] = cur_cap; //pozycja, skad przybywa - wiersz znany
    }

    int changed_capacity = cur_cap;
    bool is_chargeable = if_possible_charging(junction_power, changed_capacity, forbidden, capacity);
    if (is_chargeable) {
        //cout << " |prev " << cur_cap << " changed " << changed_capacity <<"| ";
        //cout << "POS " << cur_pos << " " << cur_cap << endl;
        //       cout << " |nextI " << cur_pos + 1 << " " << changed_capacity - cost << "| ";
        if (changed_capacity - cost >= 0) {
            previous_coordinates[cur_pos + 1][changed_capacity - cost] = cur_cap;
            if_previous_charged[cur_pos + 1][changed_capacity - cost] = 1;
        }
    }
}

int find_max_in_row(int max_val, int row[], int length) {
    for (int i = 0; i < length; i++) {

        //       cout << " mi : " << i << " ri " << row[i] << endl;
        if (row[i] != -1 && i > max_val) {
            max_val = i;

        }

    }
    //   cout << "max: <<" << max_val << endl;
    return max_val;
}

void find_best_route(chargers &used_chargers, path &shortest_path,
                     int charged[MAX_ROW][MAX_COL], int coord[MAX_ROW][MAX_COL],
                     int capacity, int start, int last_row) {

    int i = last_row;
    int j = start;

    int tempj = j;
    while (i != 0 && j != capacity) {
        if (charged[i][j] == 1) {
            used_chargers.push_back(shortest_path[i - 1]); //previous was charged
        }
//        cout << "ri " << i << " rj " << j << endl;
        j = coord[i][tempj];
        tempj = j;
        i -= 1;
    }
}

bool if_possible_short_path(path &shortest_path, int capacity, alarm_values &forbidden,
                            tracks &junction, int cost, chargers &used_chargers,
                            int &max_score) {

    int path_length = shortest_path.size();
    //opusc uzupelnianie ostatniego wiersza
    //while i != 0 && j != capacity
    //0, 1
    /* int if_previous_charged[MAX_ROW][MAX_COL]; //[path_length][capacity + 1];
     //przejdź po kolumnach, by znaleźć największe
     //wysstarczy znac numer kolumny - zawsze przejedzam o +1 wzgledem sciezki
     int previous_coordinates[MAX_ROW][MAX_COL];
     int last_charging[MAX_COL]; */

    for (int i = 0; i < path_length; i++) {
        for (int j = 0; j < capacity + 1; j++) {
            //          cout << i << " " << j << endl;
            if_previous_charged[i][j] = 0;
            previous_coordinates[i][j] = -1;
            last_charging[j] = -1;
        }
    }

    //initialization -> beginnging of the trip
    fill_next_row(0, capacity, junction, forbidden,
                  capacity,shortest_path, cost);

    //ostatni osobno obslugujemy
    for (int i = 1; i < path_length - 1; i++) {
        //       cout << "i : " << i << endl;
        for (int j = 0; j < capacity + 1; j++) {
            //cout << "i: " << i << " j: " << j << endl;
            //          cout << previous_coordinates[i][j] << " ";
            //           cout << j << endl;
            if (previous_coordinates[i][j] != -1) {
                //cout << "i: " << i << " j: " << j << endl;
                fill_next_row(i, j, junction, forbidden,
                              capacity,
                              shortest_path, cost);
            }
        }
        //       cout << endl;
    }

    bool short_is_possible = false;
    for (int j = 0; j < capacity + 1; j++) {
        //      cout << previous_coordinates[path_length - 1][j] << endl;
        if (previous_coordinates[path_length - 1][j] != -1) {
            short_is_possible = true;
        }
    }

    if (!short_is_possible) {
        return false;
    }

    bool possible_last_charge = false;
    bool temp_bool;
    for (int j = 0; j < capacity + 1; j++) {
        //       cout << previous_coordinates[path_length - 1][j] << endl;
        if (previous_coordinates[path_length - 1][j] != -1) {
            if (!possible_last_charge) {
                possible_last_charge = true;
            }

            int junction_power = give_power(junction, shortest_path, path_length - 1);
            int changed_capacity = j;
            temp_bool = if_possible_charging(junction_power, changed_capacity, forbidden, capacity);
            if (temp_bool) {
                last_charging[changed_capacity] = j;
            }
        }
    }

    int index2 = -1;
    int final_index;
    int starting_index;

    index2 = find_max_in_row(index2, previous_coordinates[path_length - 1], capacity + 1);
    if (possible_last_charge) {
        int index1 = -1;
        index1 = find_max_in_row(index1, last_charging, capacity + 1);
        final_index = max(index1, index2);
        if (final_index == index1) {
            starting_index = last_charging[final_index];
            used_chargers.push_back(shortest_path[path_length - 1]);
        } else {
            starting_index = index2;
        }
    }

    max_score = final_index;

    find_best_route(used_chargers, shortest_path, if_previous_charged, previous_coordinates,
                    capacity, starting_index, path_length - 1);

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
    //TODO without runtime error up to this part
//
//    int max_score = -1;
//    chargers used_chargers;
//
//    //print_vec(shortest_path);
//    //   cout << "here" << endl;
//    bool is_possible_shortest = if_possible_short_path(shortest_path,
//                                                       capacity,
//                                                       forbidden,
//                                                       junctions, cost,
//                                                       used_chargers, max_score);
//
//    print_result(is_possible_shortest, shortest_path, used_chargers, max_score);

    return 0;
}



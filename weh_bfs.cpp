//
// Created by heheszek on 21.11.2021.
//
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <deque>

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
using visited = int;
using adjacent_and_powerbanks = tuple<adjacent_junctions, powerbank_value, visited>;
using tracks = std::unordered_map<junction_number, adjacent_and_powerbanks>;
using distance = int;
//using key_data = pair<junction_number, pair<distance, visited>>;
using available_power = vector<int>;
using path = vector<int>;
using chargers = vector<int>;

using queue = std::deque<junction_number>;

const int NOT_VISITED = 0;
const int VISITED = 1;

const int MAX_ROW = 1002;
const int MAX_COL = 5002;

int if_previous_charged[MAX_ROW][MAX_COL]; //[path_length][capacity + 1];
//przejdź po kolumnach, by znaleźć największe
//wysstarczy znac numer kolumny - zawsze przejedzam o +1 wzgledem sciezki
int previous_coordinates[MAX_ROW][MAX_COL];
int last_charging[MAX_COL];

void insert_into_map(tracks &junctions, int road_in, int road_out, int num_roads,
                     int last_junc) {
    tracks::iterator  iter = junctions.find(road_in);

    if (iter == junctions.end()) {
        adjacent_junctions vec_junc;
        vec_junc.push_back(road_out);
        adjacent_and_powerbanks vector_power_pair = make_tuple(vec_junc, -1, NOT_VISITED);
        junctions.insert(make_pair(road_in, vector_power_pair));
    }
    else {
        if (road_in != last_junc) {
            adjacent_and_powerbanks &previous = iter->second;
            adjacent_junctions &vec_junc = get<0>(previous);
            vec_junc.push_back(road_out);
        }
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
        insert_into_map(junctions, road_in, road_out, num_of_roads, num_of_junctions);
        insert_into_map(junctions, road_out, road_in, num_of_roads, num_of_junctions);
        if (road_out == num_of_junctions) {
            insert_into_map(junctions, road_out, -1, num_of_roads, num_of_junctions);
        }
    }

    int power_value;
    for (int i = 0; i < num_of_junctions; i++) {
        cin >> power_value;
        powerbanks.push_back(power_value);
    }

    return set_of_forbidden;
}

void print_input(tracks &junctions, alarm_values &not_allowed, int capacity,
                 int cost, int disallowed, int num_junc, int num_roads,
                 available_power powerbanks) {
    cout << capacity << " " << cost << " " << disallowed << endl;

    for (alarm_values::iterator iter = not_allowed.begin();
         iter != not_allowed.end(); iter++) {
        cout << *iter << " ";
    }

    cout << "\n" << num_junc << " " << num_roads << endl;

    for (tracks::iterator triter = junctions.begin(); triter != junctions.end();
         triter++) {

        cout << triter->first << " : ";

        adjacent_junctions adjvec = get<0>(triter->second);
        for (adjacent_junctions::iterator aditer = adjvec.begin();
             aditer != adjvec.end(); aditer++) {

            cout << *aditer << " ";
        }

        cout << endl;
    }

    for (available_power::iterator aviter = powerbanks.begin(); aviter != powerbanks.end();
         aviter++) {
        cout << *aviter << " ";
    }

    cout << endl;
}

void assign_new_short(int &shortest_length, int current_length,
                      path &shortest_path, path current_path) {
    if (shortest_length > current_length) {
        shortest_length = current_length;
        shortest_path = current_path;  //does it work?
    }
}

/*void assign_powerbank_value(path &current_path, int road_key, tracks::iterator &found_roads,
                            int current_length, available_power powerbanks) {
    current_path.push_back(road_key);

    adjacent_and_powerbanks& roads_powers = found_roads->second;

    adjacent_junctions &adj_junc = get<0>(roads_powers);
    powerbank_value &current_power = get<1>(roads_powers);
    distance &current_distance = get<2>(roads_powers);

    if (current_length < current_distance) {
        current_distance = current_length;
        current_power = powerbanks[current_length];
    }
} */

void add_neighbours(tracks &junctions, int road_key, int level, queue &neigh) {
    tracks::iterator firstiter = junctions.find(road_key);

    adjacent_and_powerbanks &roads_powers = firstiter->second;
    adjacent_junctions &adjvec = get<0>(roads_powers);
    powerbank_value &power = get<1>(roads_powers);
    visited &is_visited = get<2>(roads_powers);
    for (adjacent_junctions::iterator adjiter = adjvec.begin(); adjiter != adjvec.end(); adjiter++) {
        if (!is_visited) {
            neigh.push_back(*adjiter);
        }
    }
}

void bfs_find_shortest_path_update_powerbank_assignment(tracks &junctions) {
    queue adjacent;

    tracks::iterator firstiter = junctions.find(1);

    adjacent_and_powerbanks &roads_powers = firstiter->second;
    adjacent_junctions &adjvec = get<0>(roads_powers);
    for (adjacent_junctions::iterator adjiter = adjvec.begin(); adjiter != adjvec.end(); adjiter++) {
        adjacent.push_back()
    }
}


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

int main(void) {
    int capacity;
    int cost;
    int disallowed;
    int num_junctions;
    int num_roads;

    tracks junctions;
    available_power powerbanks;

    alarm_values forbidden = read_data(junctions, capacity, cost, disallowed,
                                       num_junctions, num_roads, powerbanks);

    print_input(junctions, forbidden, capacity, cost, disallowed,
                num_junctions, num_roads, powerbanks);

    cout << endl;

    int shortest_length = num_roads + 1;
    int current_length = 0;

    path shortest_path;
    path current_path;

    find_shortest_path_update_powerbank_assignment(junctions, shortest_path,
                                                   1, current_length, shortest_length,
                                                   num_junctions, current_path,
                                                   powerbanks);

    print_path(shortest_path);

    int max_score = -1;
    chargers used_chargers;

    //   cout << "here" << endl;
    bool is_possible_shortest = if_possible_short_path(shortest_path,
                                                       capacity,
                                                       forbidden,
                                                       junctions, cost,
                                                       used_chargers, max_score);

    print_result(is_possible_shortest, shortest_path, used_chargers, max_score);
}



//
// Created by heheszek on 21.11.2021.
//
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::make_tuple;
using std::get;

using std::vector;
using std::tuple;

using alarm_values = std::unordered_set<int>;
using powerbank_value = int;
using junction_number = int;
using adjacent_junctions = vector<int>;
using distance = int;
using adjacent_and_powerbanks = tuple<adjacent_junctions, powerbank_value, distance>;
using tracks = std::unordered_map<junction_number, adjacent_and_powerbanks>;
using available_power = vector<int>;
using path = vector<int>;

void insert_into_map(tracks &junctions, int road_in, int road_out, int num_roads) {
    tracks::iterator  iter = junctions.find(road_in);

    if (iter == junctions.end()) {
        adjacent_junctions vec_junc;
        vec_junc.push_back(road_out);
        adjacent_and_powerbanks vector_power_pair = make_tuple(vec_junc, -1, num_roads + 1);
        junctions.insert(make_pair(road_in, vector_power_pair));
    }
    else {
        adjacent_and_powerbanks &previous = iter->second;
        adjacent_junctions &vec_junc = get<0>(previous);
        vec_junc.push_back(road_out);
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
        insert_into_map(junctions, road_in, road_out, num_of_roads);
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
void find_shortest_path_update_powerbank_assignment(tracks &junctions,
                                                    path &shortest_path,
                                                    int road_key,
                                                    int current_length,
                                                    int &shortest_length,
                                                    int last_junc,
                                                    path &current_path,
                                                    available_power powerbanks) {
    if (road_key == last_junc) {
        current_path.push_back(road_key);
        assign_new_short(shortest_length, current_length, shortest_path,
                         current_path);
        current_path.pop_back();

        return;
    }

    tracks::iterator found_roads = junctions.find(road_key);

    if (found_roads == junctions.end()) {
        return;
    }
    else {
        current_path.push_back(road_key);

        adjacent_and_powerbanks& roads_powers = found_roads->second;

        adjacent_junctions &adj_junc = get<0>(roads_powers);
        powerbank_value &current_power = get<1>(roads_powers);
        distance &current_distance = get<2>(roads_powers);

        if (current_length < current_distance) {
            current_distance = current_length;
            current_power = powerbanks[current_length];
        }

        for (adjacent_junctions::iterator adjiter = adj_junc.begin(); adjiter != adj_junc.end();
            adjiter++) {
        find_shortest_path_update_powerbank_assignment(junctions, shortest_path,
                                                       *adjiter, current_length,
                                                       shortest_length,
                                                       last_junc, current_path,
                                                       powerbanks);
        }

        current_path.pop_back();


    }

}

void print_path(path &shortest) {
    for (path::iterator piter = shortest.begin(); piter != shortest.end(); piter++) {
        cout << *piter << " ";
    }

    cout << endl;
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
}

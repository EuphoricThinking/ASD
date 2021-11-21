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
using std::make_pair;

using std::vector;
using std::pair;

using alarm_values = std::unordered_set<int>;
using powerbank_value = int;
using junction_number = int;
using adjacent_junctions = vector<int>;
using adjacent_and_powerbanks = pair<adjacent_junctions, powerbank_value>;
using tracks = std::unordered_map<junction_number, adjacent_and_powerbanks>;
using available_power = vector<int>;

void insert_into_map(tracks &junctions, int road_in, int road_out, int num_roads) {
    tracks::iterator  iter = junctions.find(road_in);

    if (iter == junctions.end()) {
        adjacent_junctions vec_junc;
        vec_junc.push_back(road_out);
        adjacent_and_powerbanks vector_power_pair = make_pair(vec_junc, num_roads + 1);
        junctions.insert(make_pair(road_in, vector_power_pair));
    }
    else {
        adjacent_and_powerbanks &previous = iter->second;
        adjacent_junctions &vec_junc = previous.first;
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

        adjacent_junctions adjvec = (triter->second).first;
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
}

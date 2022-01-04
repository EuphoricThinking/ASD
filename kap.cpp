//
// Created by heheszek on 04.01.2022.
//
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using std::pair;
using std::unordered_map;
using std::vector;

using std::cout;
using std::cin;
using std::endl;

using std::make_pair;
using std::sort;
using std::get;

using point = pair<int, int>;
using island = pair<int, point>;
using islands = vector<island>;
using island_and_neighbours = pair<island, islands>;
using graph = vector<island_and_neighbours>;


islands read_input(int &num_islands) {
    cin >> num_islands;

    islands result;

    int x;
    int y;
    for (int i = 0; i < num_islands; i++) {
        cin >> x >> y;
        point new_point = make_pair(x, y);
        result.push_back(make_pair(i, new_point));
    }

    return result;
}

void print_points(islands pp) {
    for (islands::iterator iter = pp.begin(); iter != pp.end(); iter++) {
        cout << "index " << iter->first << " " <<
                                               (iter->second).first
                                               << (iter->second).second
                                               << endl;
    }
}

void print_input(int num_islands, islands pp) {
    cout << num_islands << endl;
    print_points(pp);
}

graph initialize_islands(int num_islands) {
    graph result;

    for (int i = 0; i < num_islands; i++) {
        island isl = make_pair(-1, make_pair(-1, -1));
        islands isls;
        result.push_back(make_pair(isl, isls));
    }

    return result;
}

void insert_into_graph (graph &result, islands &pp, int num_islands) {
    island first_island = pp[0];
    islands isls;
    isls.push_back(pp[1]);
    result[first_island.first] = make_pair(first_island, isls);

    for (int i = 1; i < num_islands - 1; i++) {
        island current = pp[i];
        int index = current.first;
        island_and_neighbours &data = result[index];

        island &inserted_island = data.first;
        islands &neighbours = data.second;

        if (inserted_island.first == -1) inserted_island = current;
        neighbours.push_back(pp[i - 1]);
        neighbours.push_back(pp[i + 1]);
    }
}

graph create_graph(islands &pp, int num_islands) {
    graph result = initialize_islands(num_islands);

    sort(pp.begin(), pp.end());

    island first_island = pp[0];
    islands isls;
    isls.push_back(pp[1]);
    result[first_island.first] = make_pair(first_island, isls);

    for (int i = 1; i < num_islands - 1; i++) {
        island current = pp[i];
        int index = current.first;
        island_and_neighbours &data = result[index];

        island &inserted_island = data.first;
        islands &neighbours = data.second;

        if (inserted_island.first == -1) inserted_island = current;
        neighbours.push_back(pp[i - 1]);
        neighbours.push_back(pp[i + 1]);
    }

    return result;
}


int main(void) {
    int num_islands;
    islands read_islands = read_input(num_islands);
    print_input(num_islands, read_islands);

    return 0;
}
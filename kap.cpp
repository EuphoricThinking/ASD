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

using point = pair<int, int>;
using neighbours = vector<point>;
using points = vector<point>;
using graph = unordered_map<point, neighbours>;



points read_input(int &num_islands) {
    cin >> num_islands;

    points result;

    int x;
    int y;
    for (int i = 0; i < num_islands; i++) {
        cin >> x >> y;
        point new_point = make_pair(x, y);
        result.push_back(new_point);
    }

    return result;
}

void print_points(points pp) {
    for (points::iterator iter = pp.begin(); iter != pp.end(); iter++) {
        cout << iter->first << " " << iter->second << endl;
    }
}

void print_input(int num_islands, points pp) {
    cout << num_islands << endl;
    print_points(pp);
}

void insert_into_graph(graph &islands, point current_island, point island_to_insert) {
    graph::iterator found = islands.find(current_island);

    if (found == islands.end()) {
        points new_points;
        new_points.push_back(island_to_insert);
        islands.insert(make_pair(current_island, new_points));
    } else {
        points &old_points = found->second;
        old_points.push_back(island_to_insert);
    }
}
graph sort_coordinates_and_insert_into_graph(points pp) {
    sort(pp.begin(), pp.end());

    print_points(pp);
    graph result;

    result
}

int main(void) {
    int num_islands;
    points read_islands = read_input(num_islands);
    print_input(num_islands, read_islands);

    return 0;
}
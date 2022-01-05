//
// Created by heheszek on 04.01.2022.
//
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using std::pair;
using std::unordered_map;
using std::vector;
using std::tuple;
using std::priority_queue;

using std::cout;
using std::cin;
using std::endl;

using std::make_pair;
using std::make_tuple;
using std::sort;
using std::get;
using std::abs;
using std::greater;
using std::min;

using point = pair<int, int>;
using island = pair<int, point>;
using islands = vector<island>;
using island_and_neighbours = pair<island, islands>;
using graph = vector<island_and_neighbours>;
using parent = island;
using distance = int;
using family = pair<island, parent>;
using dijkstra_data = pair<distance, family>;
using dijkstra_queue = priority_queue<dijkstra_data, vector<dijkstra_data>,
        greater<dijkstra_data>>;

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

void print_island(island isl) {
    cout << "index " << isl.first << " | " << isl.second.first << " " <<
    isl.second.second << endl;
}

void print_islands(islands pp) {
    for (islands::iterator iter = pp.begin(); iter != pp.end(); iter++) {
        print_island(*iter);
    }
}

void print_input(int num_islands, islands pp) {
    cout << num_islands << endl;
    print_islands(pp);
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

void insert_into_graph (graph &result, islands pp, int num_islands) {
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

bool sort_island_first_coordinate(const island &a, const island &b) {
    return a.second.first < b.second.first;
}

bool sort_island_second_coordinate(const island &a, const island &b) {
    return a.second.second < b.second.second;
}

graph create_graph(islands &pp, int num_islands) {
    graph result = initialize_islands(num_islands);
  //  cout << endl;
    sort(pp.begin(), pp.end(), sort_island_first_coordinate);
  //  print_islands(pp);
    insert_into_graph(result, pp, num_islands);

    sort(pp.begin(), pp.end(), sort_island_second_coordinate);
  //  cout << endl;
  //  print_islands(pp);
    insert_into_graph(result, pp, num_islands);

    return result;
}

int get_distance(island i1, island i2) {
    point i1_coordinates = i1.second;
    point i2_coordinates = i2.second;

    int x_diff = abs(i1_coordinates.first - i2_coordinates.first);
    int y_diff = abs(i1_coordinates.second - i2_coordinates.second);

    return x_diff + y_diff;
}

islands dijkstra(graph &with_adjacent, island start, island stop) {
    islands shortest;

    dijkstra_queue dq;
    dijkstra_data new_data = make_pair(0, make_pair(start, start));
    dq.push(new_data);
    int dist = 0;

    int last_visited = start.first;
    //while (!dq.empty()) {
    while (last_visited != stop.first) {
        dijkstra_data returned = dq.top();
        dq.pop();

        while (returned.first < dist) {
            returned = dq.top();
            dq.pop();
        } //change current index to while inot index of last

        int current_dist = returned.first;
        island current_island = returned.second.first;
        island_and_neighbours adjacent = with_adjacent[current_island.first];
        islands neighbours = adjacent.second;

        dist = current_dist;
        shortest.push_back(current_island);
        last_visited = current_island.first;

        for (islands::iterator iter = neighbours.begin(); iter != neighbours.end();
        iter++) {
            family fm = make_pair(*iter, current_island);
            distance to_add = returned.first + get_distance(*iter, current_island);
            dijkstra_data to_add_dd = make_pair(to_add, fm);
            dq.push(to_add_dd);
        }
    }

    return shortest;
}

void sum_x_y(point &result, point to_add) {
    if (to_add.first > to_add.second) {
        result.second = result.second + to_add.second;
    } else {
        result.first = result.first + to_add.first;
    }
}

int return_result(islands from_dijkstra) {
    point result = make_pair(0, 0);
    for (islands::iterator iter = from_dijkstra.begin(); iter != from_dijkstra.end();
    iter++) {
        sum_x_y(result, iter->second);
    }

    return min(result.first, result.second);
}
int main(void) {
    int num_islands;
    islands read_islands = read_input(num_islands);
    island start = read_islands[0];
    island stop = read_islands[num_islands - 1];
    print_input(num_islands, read_islands);

    graph map_islands = create_graph(read_islands, num_islands);
    islands from_dijkstra = dijkstra(map_islands, start, stop);
    int result = return_result(from_dijkstra);
    cout << result << endl;

    return 0;
}
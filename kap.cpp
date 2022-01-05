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
using graph = vector<islands>;

using distances = vector<int>;
using visited = vector<bool>;
using dijkstra_data = pair<int, island>;
using dijkstra_queue = priority_queue<dijkstra_data, vector<dijkstra_data>,
        greater<>>;

const int MAX_COORDINATE = 1000000100;

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
    for (auto iter = pp.begin(); iter != pp.end(); iter++) {
        print_island(*iter);
    }
}

void print_input(int num_islands, const islands &pp) {
    cout << num_islands << endl;
    print_islands(pp);
}

graph initialize_islands(int num_islands) {
    graph result;

    for (int i = 0; i < num_islands; i++) {
        islands isls;
        result.push_back(isls);
    }

    return result;
}

void insert_into_graph (graph &result, islands pp, int num_islands) {
    island first_island = pp[0];
    result[first_island.first].push_back(pp[1]);

    for (int i = 1; i < num_islands - 1; i++) {
        island current = pp[i];
        int index = current.first;
        result[index].push_back(pp[i - 1]);
        result[index].push_back(pp[i + 1]);
    }
}

bool sort_island_first_coordinate(const island &a, const island &b) {
    return a.second.first < b.second.first;
}

bool sort_island_second_coordinate(const island &a, const island &b) {
    return a.second.second < b.second.second;
}

graph create_graph(islands pp, int num_islands) {
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

   // return x_diff + y_diff;
    return min(x_diff, y_diff);
}

islands initialize_parents(int num_islands) {
    islands result;

    for (int i = 0 ; i < num_islands; i++) {
        island ils;
        result.push_back(ils);
    }

    return result;
}

distances initialize_distances(int num_islands) {
    distances result;

    for (int i = 0; i < num_islands; i++) {
        result.push_back(MAX_COORDINATE);
    }

    return result;
}

visited initialize_visited(int num_islands) {
    visited result;

    for (int i = 0; i < num_islands; i++) {
        result.push_back(false);
    }

    return result;
}

islands dijkstra(graph &with_adjacent, island start, int num_islands) {
    islands parents = initialize_parents(num_islands);
    distances dist = initialize_distances(num_islands);
    visited vis = initialize_visited(num_islands);

    dijkstra_queue dq;
    dq.push(make_pair(0, start));
    dist[start.first] = 0;
    parents[start.first] = start;

    int new_dist;
    int current_index;
    while (!dq.empty()) {
        dijkstra_data current = dq.top();
        dq.pop();

        island current_island = current.second;
        current_index = current.second.first;

        if (!vis[current_index]) {
            islands neighbours = with_adjacent[current_index];

            for (auto & neighbour : neighbours) {
                new_dist = dist[current_index] +
                           get_distance(current_island, neighbour);

                if (new_dist < dist[neighbour.first]) {
                    dist[neighbour.first] = new_dist;
                    parents[neighbour.first] = current_island;
                    dq.push(make_pair(new_dist, neighbour));
                }
            }

            vis[current_index] = true;
        }
    }

    return parents;
}

    /*islands shortest;

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

    return shortest; */


void sum_x_y(point &result, point to_add) {
    if (to_add.first > to_add.second) {
        result.second = result.second + to_add.second;
    } else {
        result.first = result.first + to_add.first;
    }
}

point distance_islands(island a, island b) {
    point result = make_pair(abs(a.second.first - b.second.first),
                             abs(a.second.second - b.second.second));

    return result;
}

int return_result(islands from_dijkstra, island stop) {
    point result = make_pair(0, 0);
    island current = stop;
    point diff;

    while (current.first != 0) {
        diff = distance_islands(current, from_dijkstra[current.first]);
        sum_x_y(result, diff);
        current = from_dijkstra[current.first];
    }

    return min(result.first, result.second);
}

int main() {
    int num_islands;
    islands read_islands = read_input(num_islands);
    island start = read_islands[0];
    island stop = read_islands[num_islands - 1];
  //  print_input(num_islands, read_islands);

    graph map_islands = create_graph(read_islands, num_islands);
    islands from_dijkstra = dijkstra(map_islands, start, num_islands);
    int result = return_result(from_dijkstra, stop);
    cout << result << endl;

    return 0;
}
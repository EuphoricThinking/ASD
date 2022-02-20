//
// Created by heheszek on 20.02.2022.
//

#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::queue;
using std::vector;

using vec_bool = vector<bool>;
using vec_int = vector<int>;

const int ROWS = 8;
const int COLS = 7;
int test_data[ROWS][COLS] = {{2, 3,},
                       {5, 3, 7, 6},
                       {4, 5},
                       {5, 7},
                       {7},
                        {4},
                             {4},
                             {4}};

void print_input() {
    for (int i = 0; i< ROWS; i++) {
        cout << i + 1 << ": ";
        for (int j = 0; j < COLS; j++) {
            cout << test_data[i][j] << " ";
        }
        cout << endl;
    }
}

void bfs() {
     vec_bool visited(ROWS, false);
     vec_int parents(ROWS, -1);
     vec_int distances(ROWS, -1);

     visited[0] = true;
     parents[0] = -1;
     distances[0] = 0;

     queue<int> children;

     for (int j: test_data[0]) {
         if (j != 0) {
             children.push(j);
             parents[j] = 0;
             distances[j] = 1;
             visited[j] = true;
        }
     }

     while (!children.empty()) {
         int next_ch = children.front();
         children.pop();
         //visited[next_ch] = true;

         for (int j: test_data[next_ch - 1]) {
             if (!visited[j] && j!= 0) { //TODO remove zero part
                 visited[j] = true;
                 children.push(j);
                 parents[j] = next_ch;
                 distances[j] = distances[next_ch] + 1;
             }
         }
     }

     for (int i = 0; i < ROWS; i++) {
         int cur_par = parents[i];
         cout << i << ": ";
         while (cur_par != -1) {
             cout << cur_par << " ";
             cur_par = parents[cur_par];
         }

         cout << endl;
     }
}

int main() {
    print_input();
    bfs();

    return 0;
}
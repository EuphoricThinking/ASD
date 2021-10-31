#include <iostream>
#include <vector>
#include <sstream>

using namespace std;
using initial_array = pair<int, vector<int>>;
using possibilities = vector<vector<pair<int, int>>>;

initial_array read_file() {
    string temp;
    initial_array result;
    cin >> result.first;
    cin.ignore();
    getline(cin, temp);
    int values;
    stringstream words_to_extract(temp);
    while(words_to_extract >> values) {
        result.second.push_back(values);
    }
    return result;
}

void printer_vector(vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void printer(initial_array &ia) {
    cout << ia.first << endl;
    printer_vector(ia.second);
}

int number_of_possibilities_i(intiial_array &arr, int i, int j) {
    int if_greater_than_first = arr[i] < arr[j];
    int if_greater_than_
}
possibilities calculate_possibilites(initial_array &data_arr) {


}


int main() {
    initial_array data = read_file();
    printer(data);
}


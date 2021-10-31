#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<long long> initialize_vector_with_zeroes(int &number_of_all_players) {
    vector<long long> empty_labels;

    for (int i = 0; i < number_of_all_players; i++) {
        empty_labels.push_back(0LL);
    }

    return empty_labels;
}

vector<long long> read_matches_label_the_players(int &num_of_all_players, int &num_of_matches) {
    cin >> num_of_all_players >> num_of_matches;

    vector<long long> labels = initialize_vector_with_zeroes(num_of_all_players);

    string read_line;
    int number_of_a_player;
    int the_first_player_from_another_team = num_of_all_players/2;

    for (int match = 0; match < num_of_matches; match++) {
        getline(cin, read_line);
        stringstream numbers_to_extract(read_line);
        for (int player = 0; player < num_of_all_players; player++) {
            numbers_to_extract >> number_of_a_player;
            if (player >= the_first_player_from_another_team) {
                labels[number_of_a_player - 1] ^= (1LL << match);  //number_of_a_player - 1 -> indexing from 0
            }
        }
    }
    
    return labels;
}

int main(void) {
    int number_of_players;
    int number_of_matches;
    vector<long long> labels = read_matches_label_the_players(number_of_players, number_of_matches);
}

//
// Created by heheszek on 13.11.2021.
//
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

namespace {
    using std::cin;
    using std::cout;
    using std::endl;

    using std::sort;

    using std::vector;
    using std::string;
    using std::stringstream;

    using players = vector<long long>;
}

players initialize_vector_with_zeroes(int num_of_players) {
    players empty_labels;

    for (int i = 0; i < num_of_players; i++) {
        empty_labels.push_back(0LL);
    }

    return empty_labels;
}

players read_input(int &num_players, int &num_matches) {
    cin >> num_players >> num_matches;
    cin.ignore();

    players labels = initialize_vector_with_zeroes(num_players);

    string read_line;
    int the_first_player_from_another_team = num_players/2;
    int num_single_player;

    for (int match = 0; match < num_matches; match++) {
        getline(cin, read_line);
        stringstream all_players(read_line);

        for (int player = 0; player < num_players; player++) {
            all_players >> num_single_player;

            if (player >= the_first_player_from_another_team) {
                labels[num_single_player - 1] ^= (1LL << match); //num_single_player - 1 : index from
            }
        }
    }

    return labels;
}

bool whether_have_played_in_the_same_team(players &filled_labels, int num_players) {
    sort(filled_labels.begin(), filled_labels.end());

    for (int i = 0; i < num_players - 1; i++) {
        if (filled_labels[i] == filled_labels[i + 1]) {
            return false;
        }
    }

    return true;
}

void print_result(bool result) {
    if (result) {
        cout << "TAK" << endl;
    }
    else {
        cout << "NIE" << endl;
    }
}

int main(void) {
    int num_of_players;
    int num_of_matches;

    players labels = read_input(num_of_players, num_of_matches);
    bool whether_always_opponents = whether_have_played_in_the_same_team(labels,
                                                                 num_of_players);

    print_result(whether_always_opponents);

    return 0;
}


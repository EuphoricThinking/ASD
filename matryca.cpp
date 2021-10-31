//
// Created by heheszek on 31.10.2021.
//

#include <iostream>

namespace {
    using std::cout;
    using std::cin;
    using std::min;
    using std::endl;

    using std::string;

    string read_input() {
        string result;
        getline(cin, result);

        return result;
    }

    long minimum_gap_length(string order) {
        char previous_character = '1';
        long previous_index = -1;

        long num_of_chars = (long)order.length();
        long index = 0;
        long minimum_distance = num_of_chars + 1;

        while (index < num_of_chars) {
            if (order[index] != '*') {
                if (order[index] != previous_character && previous_character != '1') {
                    minimum_distance = min(minimum_distance,
                                           index - previous_index + 1);

                }
                previous_character = order[index];
                previous_index = index;
            }
            index++;
        }

        return minimum_distance;
    }

    long minimum_template_length(long min_gap_len, size_t order_length) {
        return min((long)order_length - min_gap_len + 2, (long)order_length);
    }
}


int main () {
    string order = read_input();

    long minimum_distance = minimum_gap_length(order);
    long minimum_pattern_length = minimum_template_length(minimum_distance, order.length());
    cout << minimum_pattern_length << endl;

    return 0;

}
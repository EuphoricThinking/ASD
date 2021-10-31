//
// Created by heheszek on 30.10.2021.
//

#include <iostream>
#include <vector>
#include <tuple>

using std::cout;
using std::cin;
using std::endl;
using std::get;
using std::max;

using std::vector;
using std::tuple;

using prices = vector<long>;
using orders = vector<long>;
using sum = vector<long long>;

using max_odd_left = long;
using max_even_left = long;
using min_odd_right = long;
using min_even_right = long;
using minmax_tuple = tuple<max_odd_left, max_even_left, min_odd_right,
                        min_even_right>;
using minmax_vector = vector<minmax_tuple>;

const int LEFT = 0;
const int RIGHT = 1;

const int MAX_ODD = 0;
const int MAX_EVEN = 1;
const int MIN_ODD = 2;
const int MIN_EVEN = 3;

/*
 * The array of prices is summed up from right to the left
 * The array of tuples indicates the smallest number from right end to the current
 * position (odd or even) and the greates number from the left end to the current position
 */


bool read_input(long &products, prices &sorted_list, orders &ordered_products,
                long &days) {
    cin >> products;

    if (products <= 0) {
        return false;
    }

    long counter = 0;
    long single_item; //price of number of orders
    while (counter < products) {
        cin >> single_item;
        sorted_list.push_back(single_item);
        counter++;
    }

    cin >> days;

    if (days <= 0) {
        return false;
    }

    counter = 0;
    while (counter < days) {
        cin >> single_item;
        ordered_products.push_back(single_item);
        counter++;
    }

    return true;
}

void print_readout(long products, prices &sorted_list, orders &ordered_prod,
                   long days) {
    cout << products << endl;

    for (long i = 0; i < products; i++) {
        cout << sorted_list[i] << " ";
    }
    cout << endl;

    cout << days << endl;

    for (long i = 0; i < days; i++) {
        cout << ordered_prod[i] << endl;
    }
}

bool whether_value_is_better_than_previous(long new_value, long previous_value,
                                            int mode) {
    if (mode == LEFT) { //looking for max value
                if (new_value > previous_value || previous_value == -1) {
                    return true;
                }
                return false;
    }
    else {
        if (new_value < previous_value || previous_value == -1) {
            return true;
        }
        return false;
    }
}

void assign_tuple_at_position(minmax_tuple &tuple_to_fill, long price,
                               minmax_tuple &previous_tuple, int mode) {
    if (price%2 == 0) {
        if (mode == LEFT) { //looking for max even
            if (whether_value_is_better_than_previous(price,
                                                       get<MAX_EVEN>(previous_tuple),
                                                               LEFT)) {
                get<MAX_EVEN>(tuple_to_fill) = price;
            }
            else {
                get<MAX_EVEN>(tuple_to_fill) = get<MAX_EVEN>(previous_tuple);
            }
            get<MAX_ODD>(tuple_to_fill) = get<MAX_ODD>(previous_tuple);
        }
        else { //even minimum
            if (whether_value_is_better_than_previous(price, get<MIN_EVEN>(previous_tuple), RIGHT)) {
                get<MIN_EVEN>(tuple_to_fill) = price;
            }
            else {
                get<MIN_EVEN>(tuple_to_fill) = price;
            }
            get<MIN_ODD>(tuple_to_fill) = get<MIN_ODD>(previous_tuple);
        }
    }
    else {
        if (mode == LEFT) { //odd max
            if (whether_value_is_better_than_previous(price, get<MAX_ODD>(previous_tuple), LEFT)) {
                get<MAX_ODD>(tuple_to_fill) = price;
            }
            else {
                get<MAX_ODD>(tuple_to_fill) = get<MAX_ODD>(previous_tuple);
            }
            get<MAX_EVEN>(tuple_to_fill) = get<MAX_EVEN>(previous_tuple);
        } //odd min
        else {
            if (whether_value_is_better_than_previous(price, get<MIN_ODD>(previous_tuple), RIGHT)) {
                get<MIN_ODD>(tuple_to_fill) = price;
            }
            else {
                get<MIN_ODD>(tuple_to_fill) = get<MIN_ODD>(previous_tuple);
            }
            get<MIN_EVEN>(tuple_to_fill) = get<MIN_EVEN>(previous_tuple);
        }
    }
}

void print_minmax_tuple(minmax_tuple tup) {
         cout << "max odd: " << get<MAX_ODD>(tup) << " max even: " <<
         get<MAX_EVEN>(tup) << "    min odd: " <<
         get<MIN_ODD>(tup) << " min even: " <<
         get<MIN_EVEN>(tup) << endl;
}
void print_tuples(minmax_vector tuples, long products, prices sorted_prices) {
    for (int i = 0; i < products; ++i) {
        cout << sorted_prices[products - 1 - i] << " -> ";
        print_minmax_tuple(tuples[i]);
    }
}

void print_sums(sum summed_up, long products) {
    for (int i = 0; i < products; ++i) {
        cout << summed_up[i] << " ";
    }
    cout << endl;
}

/*
 * RIGHT mode - from roght to left
 * LEFT mode - from left to right
 */
sum prepare_suffix_sum_and_minmax_data(prices &sorted_prices, long products, minmax_vector &list_of_minmax) {
    minmax_tuple minmax_at_position = std::make_tuple(-1, -1, -1, -1);
    sum sum_from_right(products);
    minmax_tuple initial_tuple = std::make_tuple(-1, -1, -1, -1);

    assign_tuple_at_position(minmax_at_position, sorted_prices[products - 1],
                             initial_tuple, RIGHT);
    list_of_minmax.push_back(minmax_at_position);
    sum_from_right[0] = sorted_prices[products - 1];

    long sum_index = 1;
    for (long i = products - 2; i >= 0; --i) {
        minmax_tuple new_minmax = std::make_tuple(-1, -1, -1, -1);
        assign_tuple_at_position(new_minmax, sorted_prices[i], list_of_minmax[sum_index - 1], RIGHT);

        list_of_minmax.push_back(new_minmax);
        sum_from_right[sum_index] = sum_from_right[sum_index - 1] + sorted_prices[i];
        sum_index++;
    }

    initial_tuple = std::make_tuple(-1, -1, -1, -1);
    //assign_tuple_at_position(list_of_minmax[products - 1], sorted_prices[0], initial_tuple, LEFT);
    assign_tuple_at_position(list_of_minmax[products - 2], sorted_prices[0], initial_tuple, LEFT);

    for (long i = 2; i < products; ++i) {
        assign_tuple_at_position(list_of_minmax[products - 1 - i], sorted_prices[i - 1], list_of_minmax[products - i], LEFT);
    }

    return sum_from_right;
}

long long find_sum(long long calculated_sum, minmax_tuple current_position) {
    long long cand1 = -1;
    long long cand2 = -1;
    if (get<MAX_EVEN>(current_position) != -1) {
        if (get<MIN_ODD>(current_position) != -1) {
            cand1 = calculated_sum - get<MIN_ODD>(current_position) + get<MAX_EVEN>(current_position);
        }
    }
    if (get<MAX_ODD>(current_position) != - 1) {
        if (get<MIN_EVEN>(current_position) != -1) {
            cand2 = calculated_sum - get<MIN_EVEN>(current_position) +
                    get<MAX_ODD>(current_position);
        }
    }
    return max(cand1, cand2);
}

long long find_price(long ordered_products, minmax_vector &minmax_found, sum &summed_up) {
    long long initial_prize = summed_up[ordered_products - 1];

    if (initial_prize%2 != 0) {
        return initial_prize;
    }
    else {
        initial_prize = find_sum(initial_prize, minmax_found[ordered_products - 1]);
        return initial_prize;
    }
}

void return_sum(minmax_vector &minmax_found, orders &oredered_products, long number_of_days, sum &summed_up) {
    long long result;
    for (int i = 0; i < number_of_days; i++) {
        result = find_price(oredered_products[i], minmax_found, summed_up);
        cout << result << '\n';
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);



    long number_of_products;
    long number_of_days;
    prices sorted_prices;
    orders products_per_day;

    bool initially_possible = read_input(number_of_products, sorted_prices, products_per_day,
               number_of_days);
    print_readout(number_of_products, sorted_prices, products_per_day,
                  number_of_days);

    if (!initially_possible) {
        cout << -1;
        return 1;
    }

    if (number_of_products <= 0) {
        cout << -1 << endl;
        return 1;
    }

    minmax_vector list_of_minmax;
    sum sum_from_right = prepare_suffix_sum_and_minmax_data(sorted_prices,
                                                               number_of_products,
                                                               list_of_minmax);

    print_tuples(list_of_minmax, number_of_products, sorted_prices);
    print_sums(sum_from_right, number_of_products);

    return_sum(list_of_minmax, products_per_day, number_of_days, sum_from_right);

    return 0;
}
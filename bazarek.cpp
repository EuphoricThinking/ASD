#include <iostream>
#include <vector>

using namespace std;
using number_of_available_products = long;
using number_of_days = long;
using number_ordered_products = long;
using prices = vector<long>;
using orders = tuple<number_of_available_products, vector<long>, number_of_days, vector<number_ordered_products>

void read_input_save_orders(char[] filename) {
    FILE* opened_orders = fopen(filename, "r");
    long available_products;
    fscanf("%ld\n")
}

int main(int argc, char** argv) {

    return 0;
}
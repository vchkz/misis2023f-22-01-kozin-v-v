#include <iostream>

int main() {
    int num_test_cases;
    std::cin >> num_test_cases;

    while (num_test_cases--) {
        int array_size;
        std::cin >> array_size;

        int input_array[array_size];
        int flag = 0;

        for (int i = 0; i < array_size; ++i) {
            std::cin >> input_array[i];
            if (i != 0) {
                if (input_array[i] < input_array[i - 1]) {
                    flag = 1;
                }
            }
        }

        int boolean_array[array_size];
        int ones = 0, zeros = 0;

        for (int i = 0; i < array_size; ++i) {
            std::cin >> boolean_array[i];
            if (boolean_array[i] == 1) {
                ones++;
            } else {
                zeros++;
            }
        }

        if ((ones == array_size || zeros == array_size) && flag == 1) {
            std::cout << "No" << std::endl;
        } else {
            std::cout << "Yes" << std::endl;
        }
    }

    return 0;
}

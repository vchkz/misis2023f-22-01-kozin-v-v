#include <iostream>
#include <vector>
#include <climits>

int main() {
    int test_cases;
    std::cin >> test_cases;

    while (test_cases--) {
        int array_size, divisor;
        std::cin >> array_size >> divisor;

        std::vector<int> elements(array_size);

        for (int i = 0; i < array_size; i++) {
            std::cin >> elements[i];
        }

        int min_difference = INT_MAX;
        int even_count = 0;

        for (int i = 0; i < array_size; i++) {
            if (elements[i] % 2 == 0) {
                even_count++;
            }

            int remainder = elements[i] % divisor;

            if (remainder == 0) {
                min_difference = std::min(min_difference, remainder);
            } else {
                min_difference = std::min(min_difference, divisor - remainder);
            }
        }

        if (divisor == 4) {
            if (even_count >= 2) {
                min_difference = 0;
            } else if (even_count == 1) {
                min_difference = std::min(min_difference, 1);
            } else {
                min_difference = std::min(min_difference, 2);
            }
        }

        std::cout << min_difference << std::endl;
    }

    return 0;
}


//
// Created by kozin on 26.10.2023.
//

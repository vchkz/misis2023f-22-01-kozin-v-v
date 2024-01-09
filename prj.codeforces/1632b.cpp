#include <iostream>

int main() {
    int num_test_cases;
    std::cin >> num_test_cases;

    while (num_test_cases--) {
        int array_size;
        std::cin >> array_size;

        int max_bit = 0;
        while ((1 << (max_bit + 1)) <= array_size - 1)
            max_bit++;

        for (int i = (1 << max_bit) - 1; i >= 0; i--)
            std::cout << i << " ";

        for (int i = (1 << max_bit); i < array_size; i++)
            std::cout << i << " ";

        std::cout << '\n';
    }

    return 0;
}

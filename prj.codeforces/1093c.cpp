#include <iostream>

int main() {
    int num_elements;
    std::cin >> num_elements;

    long long second_array[100000];
    long long result_array[200000];

    // max(result_array[i-1], second_array[i] - result_array[num_elements-i-1])
    std::cin >> second_array[0];
    result_array[0] = 0;
    result_array[num_elements - 1] = second_array[0];

    for (int i = 1; i < num_elements / 2; i++) {
        std::cin >> second_array[i];
        result_array[i] = std::max(result_array[i - 1], second_array[i] - result_array[num_elements - i]);
        result_array[num_elements - i - 1] = second_array[i] - result_array[i];
    }

    for (int i = 0; i < num_elements; i++) {
        std::cout << result_array[i] << " ";
    }

    return 0;
}

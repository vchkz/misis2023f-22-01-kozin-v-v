#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <stack>

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int num_tests;
    std::cin >> num_tests;

    while (num_tests--) {
        int array_size;
        std::cin >> array_size;
        std::cin.ignore();

        std::string input_line;
        std::getline(std::cin, input_line);
        std::istringstream iss(input_line);

        int current_number;
        std::vector<int> numbers;
        while (iss >> current_number) {
            numbers.push_back(current_number);
        }

        std::stack<int> temp_stack;
        int inversion_count = 0;
        for (int i = 0; i < array_size; ++i) {
            while (!temp_stack.empty() && numbers[i] < temp_stack.top()) {
                temp_stack.pop();
                inversion_count += 1;
            }
            temp_stack.push(numbers[i]);
        }

        std::cout << inversion_count << std::endl;
    }

    return 0;
}

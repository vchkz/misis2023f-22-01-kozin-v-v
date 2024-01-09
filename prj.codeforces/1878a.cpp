#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <map>

int main() {
    int num_tests;
    std::cin >> num_tests;

    while (num_tests--) {
        int size_a, target_value;
        std::cin >> size_a >> target_value;

        std::set<int> unique_values;
        for (int i = 0; i < size_a; ++i) {
            int element;
            std::cin >> element;
            unique_values.insert(element);
        }

        std::cout << (unique_values.count(target_value) == 1 ? "YES" : "NO") << std::endl;
    }
    return 0;
}

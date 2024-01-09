#include <iostream>
#include <vector>
#include <set>

const int inf = 1e9 + 7;


int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int num_tests;
    std::cin >> num_tests;

    while (num_tests--) {
        int array_size, j, k, l;
        std::cin >> array_size;

        std::vector<int> array_values(array_size);
        for (int i = 0; i < array_size; ++i) {
            std::cin >> array_values[i];
        }

        for (j = array_size - 1; j >= 1; --j) {
            if (array_values[j] < array_values[j - 1]) {
                break;
            }
        }

        std::set<int> set_before_j;
        std::set<int> set_after_j;

        for (k = j - 1; k >= 0; --k) {
            set_before_j.insert(array_values[k]);
        }

        for (k = array_size - 1; k >= j; --k) {
            if (set_before_j.find(array_values[k]) != set_before_j.end()) {
                break;
            }
        }

        for (l = 0; l <= k; ++l) {
            set_after_j.insert(array_values[l]);
        }

        std::cout << set_after_j.size() << std::endl;
    }

    return 0;
}

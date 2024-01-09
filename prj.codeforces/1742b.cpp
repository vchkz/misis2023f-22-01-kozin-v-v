#include <iostream>
#include <vector>
#include <algorithm>

#define MOD_CONST 1000000007

int binpow(int a, int b) {
    if (b == 0) return 1;
    int res = binpow(a, b / 2);
    return (b % 2) ? res * res * a : res * res;
}

void solve(int case_num) {
    int size, element_count;
    std::cin >> size;
    std::vector<int> elements(size);

    for (auto &element : elements) {
        std::cin >> element;
    }

    std::sort(elements.begin(), elements.end());

    for (int i = 1; i < size; ++i) {
        if (elements[i] == elements[i - 1]) {
            std::cout << "NO" << std::endl;
            return;
        }
    }

    std::cout << "YES" << std::endl;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int test_cases;
    std::cin >> test_cases;

    for (int case_num = 0; case_num < test_cases; ++case_num) {
        solve(case_num);
    }

    return 0;
}

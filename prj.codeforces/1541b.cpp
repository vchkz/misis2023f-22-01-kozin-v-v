#include <iostream>
#include <vector>

typedef long long Long;
typedef std::pair<Long, Long> Pair;

void Solve() {
    int num_tests;
    std::cin >> num_tests;

    while (num_tests--) {
        int n;
        std::cin >> n;

        std::vector<int> indices(2 * n + 1, -1);

        for (int i = 1; i <= n; i++) {
            int value;
            std::cin >> value;
            indices[value] = i;
        }

        int count = 0;

        for (int sum = 3; sum <= 2 * n; sum++) {
            for (int i = 1; i * i <= sum; i++) {
                if (sum % i == 0 && i * i != sum && indices[i] != -1 && indices[sum / i] != -1 && indices[i] + indices[sum / i] == sum) {
                    count++;
                }
            }
        }

        std::cout << count << std::endl;
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    Solve();

    return 0;
}

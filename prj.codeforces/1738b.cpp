#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int tc;
    std::cin >> tc;

    while (tc--) {
        int n, k;
        std::cin >> n >> k;
        std::vector<long long> s(n + 1);

        for (int i = n - k + 1; i <= n; ++i)
            std::cin >> s[i];

        if (k == 1) {
            std::cout << "YES" << std::endl;
            continue;
        }

        std::vector<long long> a(n + 1);

        for (int i = n - k + 2; i <= n; ++i)
            a[i] = s[i] - s[i - 1];

        if (!std::is_sorted(a.begin() + n - k + 2, a.end()) || s[n - k + 1] > a[n - k + 2] * (n - k + 1)) {
            std::cout << "NO" << std::endl;
        } else {
            std::cout << "YES" << std::endl;
        }
    }

    return 0;
}

//
// Created by kozin on 11.10.2023.
//

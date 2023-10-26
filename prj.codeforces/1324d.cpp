#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    long long n;
    std::cin >> n;
    std::vector<long long> originalValues(n), modifiedValues(n);

    for (long long i = 0; i < n; i++)
        std::cin >> originalValues[i];

    for (long long i = 0; i < n; i++) {
        long long x;
        std::cin >> x;
        modifiedValues[i] = originalValues[i] - x;
    }

    std::sort(modifiedValues.begin(), modifiedValues.end());

    long long answer = 0;
    for (long long i = 0; i < n; i++) {
        answer += std::min(n - (std::upper_bound(modifiedValues.begin(), modifiedValues.end(), -modifiedValues[i]) - modifiedValues.begin()), n - i - 1);
    }

    std::cout << answer;
}

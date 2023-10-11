#include <iostream>

int main() {
    long long int t;
    std::cin >> t;
    while (t--) {
        long long int x;
        std::cin >> x;
        if (x % 2020 == 0 || x % 2021 == 0) {
            std::cout << "YES" << std::endl;
        } else if (((x / 2020) - (x / 2021)) == 1) {
            std::cout << "YES" << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
    }
    return 0;
}

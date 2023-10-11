#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    long long int x, y, i, j, k;
    std::cin >> x;
    for (i = 1; i <= x; i++) {
        std::cin >> y;
        std::vector<long long int> a(y + 1), b(y + 1);
        for (j = 1; j <= y; j++) {
            std::cin >> a[j];
            b[j] = a[j];
        }
        std::sort(b.begin(), b.end());
        for (j = 1; j <= y; j++) {
            for (k = 1; k <= y; k++) {
                if (a[j] == b[k]) {
                    std::cout << y - k + 1 << " ";
                    b[k] = -1;
                    break;
                }
            }
        }
        std::cout << std::endl;
    }
    return 0;
}

//
// Created by kozin on 11.10.2023.
//

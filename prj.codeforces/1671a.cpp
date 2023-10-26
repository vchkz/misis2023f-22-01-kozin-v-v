#include <iostream>
#include <string>

int main() {
    int num_cases;
    std::cin >> num_cases;

    while (num_cases--) {
        std::string str;
        std::cin >> str;
        int count = 1;

        if (str.size() == 1) {
            std::cout << "NO" << std::endl;
            continue;
        }

        if (str[0] != str[1] || str[str.size() - 1] != str[str.size() - 2]) {
            std::cout << "NO" << std::endl;
            continue;
        }

        int is_repeated = 0;

        for (int i = 1; i < str.size() - 1; i++) {
            if (str[i] != str[i - 1] && str[i] != str[i + 1]) {
                is_repeated = 1;
                break;
            }
        }

        if (is_repeated) {
            std::cout << "NO" << std::endl;
        } else {
            std::cout << "YES" << std::endl;
        }
    }
}

//
// Created by kozin on 26.10.2023.
//

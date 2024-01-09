#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long test_cases;
    std::cin >> test_cases;

    while (test_cases--) {
        std::string input;
        std::cin >> input;

        input = '0' + input;

        int flag = input.size();

        for (int i = input.size() - 1; i > 0; i--) {
            if (input[i] == '9' + 1) {
                input[i] = '0';
                input[i - 1]++;
            }

            if (input[i] >= '5') {
                flag = i;
                input[i - 1]++;
            }
        }

        for (int i = 0; i < input.size(); i++) {
            if (i == 0 && input[i] == '0') {
                continue;
            }

            if (i < flag) {
                std::cout << input[i];
            } else {
                std::cout << '0';
            }
        }

        std::cout << std::endl;
    }

    return 0;
}

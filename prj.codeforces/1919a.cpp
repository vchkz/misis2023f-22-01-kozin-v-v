#include <iostream>

typedef long long int Int64;
typedef unsigned long long int UInt64;
typedef long double Float64;

void gameOutcome() {
    Int64 scoreA, scoreB;
    std::cin >> scoreA >> scoreB;
    int turn = 0;  // 0 for playerA, 1 for playerB

    while (scoreA != 0 || scoreB != 0) {
        if (scoreA > scoreB) {
            if ((scoreA - scoreB) % 2) {
                scoreA = scoreB;
                turn = 1;
            } else {
                scoreA = scoreB;
                turn = 0;
            }
        } else if (scoreA < scoreB) {
            if ((scoreB - scoreA) % 2) {
                scoreB = scoreA;
                turn = 1;
            } else {
                scoreB = scoreA;
                turn = 0;
            }
        }
        if (scoreA == scoreB) {
            if (turn == 1) {
                std::cout << "Alice" << std::endl;
                return;
            } else if (turn == 0) {
                std::cout << "Bob" << std::endl;
                return;
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int rounds;
    std::cin >> rounds;
    while (rounds--) {
        gameOutcome();
    }

    return 0;
}

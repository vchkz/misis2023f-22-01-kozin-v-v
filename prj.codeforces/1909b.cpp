#include <iostream>
#include <algorithm>

typedef long long ll;

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

void processArray(ll arr[], int size) {
    ll gcdValue = 1;
    while (true) {
        ll currentGcd = 0, oddCount = 0;
        for (int i = 0; i < size; ++i) {
            currentGcd = gcd(arr[i], currentGcd);
        }
        for (int i = 0; i < size; ++i) {
            arr[i] /= currentGcd;
            if (arr[i] & 1) {
                oddCount++;
            }
        }
        gcdValue *= currentGcd;
        if (oddCount == size) {
            for (int i = 0; i < size; ++i) {
                arr[i]--;
            }
        } else {
            std::cout << 2 * gcdValue << std::endl;
            return;
        }
    }
}

void solve() {
    int size;
    std::cin >> size;
    ll arr[size];
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }
    std::sort(arr, arr + size);
    processArray(arr, size);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int cases;
    std::cin >> cases;
    while (cases--) {
        solve();
    }

    return 0;
}

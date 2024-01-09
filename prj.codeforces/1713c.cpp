#include <iostream>
#include <vector>
#include <cmath>

typedef long long ll;
typedef std::vector<std::vector<ll>> vvi;
typedef std::pair<ll, ll> pii;
typedef std::vector<ll> vi;

ll findNextPerfectSquare(ll num) {
    ll x = 0;
    while (x < num) {
        ll candidate = x + num;
        ll squareRoot = static_cast<ll>(std::sqrt(candidate));
        if (squareRoot * squareRoot == candidate) {
            break;
        }
        x++;
    }
    return x;
}

void solve() {
    ll n;
    std::cin >> n;

    ll current = 0;
    current = findNextPerfectSquare(n - 1);

    ll maxVal = n;
    ll minVal = current;
    vi result(n);

    for (ll i = n - 1; i >= 0; i--) {
        if (current < maxVal) {
            result[i] = current++;
        } else {
            maxVal = minVal;
            current = findNextPerfectSquare(i);
            minVal = current;
            result[i] = current++;
        }
    }

    for (ll val : result) {
        std::cout << val << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    ll t = 1;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

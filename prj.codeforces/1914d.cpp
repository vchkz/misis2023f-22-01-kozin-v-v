#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;
typedef long double lld;

void solve() {
    ll n;
    std::cin >> n;

    std::vector<std::pair<ll, ll>> arr_a(n), arr_b(n), arr_c(n);

    for (int i = 0; i < n; i++) {
        ll d;
        std::cin >> d;
        arr_a[i] = {d, i};
    }

    for (int i = 0; i < n; i++) {
        ll d;
        std::cin >> d;
        arr_b[i] = {d, i};
    }

    for (int i = 0; i < n; i++) {
        ll d;
        std::cin >> d;
        arr_c[i] = {d, i};
    }

    std::sort(arr_a.begin(), arr_a.end());
    std::sort(arr_b.begin(), arr_b.end());
    std::sort(arr_c.begin(), arr_c.end());

    ll ans = 0;
    for (ll i = n - 3; i < n; i++) {
        for (ll j = n - 3; j < n; j++) {
            if (arr_a[i].second != arr_b[j].second) {
                for (ll k = n - 3; k < n; k++) {
                    if (arr_a[i].second != arr_c[k].second && arr_b[j].second != arr_c[k].second) {
                        ans = std::max(ans, arr_a[i].first + arr_b[j].first + arr_c[k].first);
                    }
                }
            }
        }
    }

    std::cout << ans << std::endl;
}

int main() {
    ll t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

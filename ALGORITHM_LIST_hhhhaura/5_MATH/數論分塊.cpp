#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MAXN 1000005
#define MOD 1000000007
#define INF 1000000000000000000
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;

int solve(int n) {
	int ans = 0, k = sqrt(n);
	rep(i, 1, k) {
		ans += (n / i > k ? n / i : 0);
	}
	rep(i, 1, k) {
		int l = n / (i + 1) + 1, r = n / i;
		ans += (r - l + 1) * i;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		cout << solve(n) << "\n";
	}
	return 0;
}
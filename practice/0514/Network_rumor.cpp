#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
using namespace std;
namespace solver {
	const int P = 13;
	const int INF = 1000000000;
	int n, a[P][P], cnt[P];
	int dp[1 << P][P];
	void init_(int _n) {
		n = _n;
		rep(i, 0, (1 << n) - 1) rep(j, 0, n - 1) {
			dp[i][j] = INF;
		}
	}
	int solve() {
		rep(k, 0, n - 1) rep(i, 0, n - 1) rep(j, 0, n - 1) {
			a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
		}
		rep(i, 0, n - 1) dp[1 << i][i] = 0, dp[0][0] = 0;
		rep(i, 1, (1 << n) - 1) {
			rep(j, 0, n - 1) if((i >> j) & 1) {
				for(int l = i; l > 0; l = (l - 1) & i) if((l >> j) & 1){
					int r = i ^ l;
					rep(k, 0, n - 1) if((r >> k) & 1) {
						dp[i][j] = min(dp[i][j], max(dp[l][j] + a[j][k], dp[r][k] + a[j][k]));
					}
				}
			}
		}
		return dp[(1 << n) - 1][0];

	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 0, n - 1) rep(j, 0, n - 1) {
		cin >> a[i][j];
	}
	cout << solve() << "\n";
	return 0;
}

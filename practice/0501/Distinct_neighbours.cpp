#define wiwihorz
#include <bits/stdc++.h>
#define int long long int
#define rep(i, a, b) for(int i = a; i <= b;++i)
#define rrep(i, a, b) for(int i = b; i >= a; --i)
#define MOD 1000000007
using namespace std;
namespace math {
	int n;
	vector<vector<int>> c, h;
	void init_(int _n) {
		n = _n;
		c.assign(n + 1, vector<int>(n + 1, 0));
		rep(i, 0, n) c[i][0] = 1;
		rep(i, 1, n) rep(j, 1, i) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
		}
		return;
	}
	void add(int &a, int b) {a = (a + b) % MOD;}
	int C(int a, int b) {
		if(a == b) return 1;
		if(a < 0 || b < 0) return 0;
		return c[a][b];
	}
	int H(int a, int b) {
		return C(a - 1, b - 1);
	}
}
namespace solver {
	signed n;
	vector<int> cnt, dp[2];
	void init_(int _n) {
		n = _n;
		cnt.assign(n + 1, 0);
		dp[0].assign(n + 1, 0);
		dp[1].assign(n + 1, 0);
		math::init_(n + 5);
	} 
	int solve() {
		dp[0][0] = 1;
		int sum = 0;
		rep(i, 1, n) {
			bool id = (i & 1); sum += cnt[i - 1];
			rep(j, 0, sum + max(0ll, cnt[i] - 1)) {
				dp[id][j] = 0;
				rep(a, 0, cnt[i]) rep(b, 0, a) {
					signed x = j - cnt[i] + a + b;
					math::add(dp[id][j], dp[!id][x] * math::H(cnt[i], a) % MOD
						* math::C(x, b) % MOD * math::C(sum + 1 - x, a - b) % MOD);
				}
			}
		}
		return dp[n & 1][0];
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) {
		int x; cin >> x;
		cnt[x] ++;
	}	
	cout << solve() << "\n";
	return 0;
}


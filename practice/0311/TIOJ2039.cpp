#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(signed i = a; i <= b; i++)
#define rrep(i, a, b) for(signed i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define MAXN 1000005
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;

struct aliens {
	struct res {
		int v, t;
	};
	signed n, k;
	vector<int> dp;
	vector<signed> cnt, a;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		dp.assign(n + 1, 0);
		a.assign(n + 1, 0);
		cnt.assign(n + 1, 0);
	};
	res check(int x) {
		int id = 0;
		dp.assign(n + 1, 0);
		cnt.assign(n + 1, 0);
		rep(i, 1, n) {
			int v = dp[id] - a[id + 1] - x + a[i];
			if(v > dp[i - 1]) {
				cnt[i] = cnt[id] + 1;
				dp[i] = v;
			}
			else dp[i] = dp[i - 1], cnt[i] = cnt[i - 1];
			if(dp[i] - a[i + 1] > dp[id] - a[id + 1]) {
				id = i;
			}
		}
		return {dp[n], cnt[n]};
	}
	int solve() {
		int l = 0, r = 1e7 + 1;
		while(r - l > 1) {
			int mid = (l + r) / 2;
			res cur = check(mid);
			if(cur.t < k) r = mid;
			else l = mid;
		}
		res a = check(0), b = check(l), c = check(r);
		int sm = c.v + r * c.t, bg = b.v + l * b.t;
		if(a.t <= k) return a.v;
		else return sm + (k - c.t) * (bg - sm) / (b.t - c.t);
	}
} dp;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	signed n, k; cin >> n >> k;
	dp.init_(n, k);
	rep(i, 1, n) cin >> dp.a[i];
	cout << dp.solve() << "\n";
	return 0;
} 

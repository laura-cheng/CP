//#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
#define int long long int

using namespace std;

namespace dp {
	vector<int> ans, val, a, b;
	vector<int> v, pos, pre, dp;
	int n; 
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, 0);
		b.assign(n + 1, 0);
		v.assign(n + 1, 0);
		pos.assign(n + 1, 0);
		pre.assign(n + 1, 0);
		dp.assign(n + 1, 0);
		ans.clear(), val.clear();
	}
	void solve() {
		rep(i, 1, n) {
			val.push_back(b[i]);
			val.push_back(a[i]);
		}
		sort(all(val)), val.resize(unique(all(val))- val.begin());
		rep(i, 1, n) {
			int x = lower_bound(val.begin(), val.end(), b[i]) - val.begin() + 1;
			pos[x] = i;
		}
		rep(i, 1, n) {
			int x = lower_bound(val.begin(), val.end(), a[i]) - val.begin() + 1;
			v[i] = pos[x];
		}
		rrep(i, 1, n) {
			dp[i] = 1;
			rep(j, i + 1, n) {
				if(v[i] >= v[j]) continue;
				if(dp[i] < dp[j] + 1) {
					pre[i] = j, dp[i] = dp[j] + 1;
				}
				else if(dp[i] == dp[j] + 1) {
					if(a[pre[i]] < a[j]) pre[i] = j;
				}
			}
//			cerr << "i " << i << " dp " << dp[i] << " v " << v[i] << "\n";
		}
		int len = 0, p = 0;
		rep(i, 1, n) len = max(len, dp[i]);
		rep(i, 1, n) if(dp[i] == len) {
			if(a[i] > a[p]) p = i;	
		}
		rep(i, 0, len - 1) {
			ans.push_back(a[p]);
			p = pre[p];
		}
		return;
	}

} ;
using namespace dp;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; 
	cin >> n, init_(n);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> b[i];
	solve();
	rep(i, 0, signed(ans.size()) - 1) {
		cout << ans[i] << " \n"[i + 1 == ans.size()];
	}	
	return 0;
}

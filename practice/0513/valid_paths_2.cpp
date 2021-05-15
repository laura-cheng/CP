#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl;} 
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, ans = 0;
	const int MOD = 1000000007;
	vector<int> dp;
	vector<vector<int>> mp;
	void init_(int _n) {
		n = _n, ans = 0;
		dp.assign(n + 1, 0);
		mp.assign(n + 1, vector<int>());
	}
	void add(int &a, int b) {
		a = (a + b) % MOD;
	}
	void dfs(int x, int par) {
		int cur = 0;
		for(auto i : mp[x]) if(i != par) {
			dfs(i, x);
			add(cur, dp[x] * dp[i] % MOD);
			add(dp[x], dp[i]);
		}
		cur = (cur * 2) % MOD;
		add(ans, cur);
		add(ans, dp[x] + 1);
		dp[x] = (dp[x] * 2 + 1) % MOD;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		init_(n);
		rep(i, 1, n - 1) {
			int x, y; cin >> x >> y;
			mp[x].push_back(y);
			mp[y].push_back(x);
		}
		dfs(1, 1);
		cout << ans << "\n";
	}
	return 0;
}

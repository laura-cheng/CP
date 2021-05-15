#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

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
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n;
	vector<int> v, pre;
	vector<vector<int>> dp;
	void init_(int _n) {
		n = _n;
		v.assign(n, 0);
		pre.assign(n + 2, 0);
		dp.assign(n + 1, vector<int>(n + 1, INF));
	}
	int solve() {
		sort(all(v)), reverse(all(v));
		rrep(i, 0, n - 1) pre[i + 1] = pre[i + 2] + v[i];
		dp[1][0] = pre[2];
		rep(l, 0, n) {
			rep(a, 0, n) rep(b, 0, n - a - l) {
				dp[a + b][a] = min(dp[a + b][a], 
					dp[a][b] + (pre[l + 1] - pre[l + a + 1]) + pre[l + a + b + 1]);
			}
			if(l == n) return dp[0][0];
			rep(a, 1, n) rep(b, 0, n) {
				dp[a - 1][b] = dp[a][b];
			}
			rep(b, 0, n) dp[n][b] = INF;
		}
		return 0;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	for(auto &i : v) cin >> i;
	cout << solve() << "\n";
	return 0;
}

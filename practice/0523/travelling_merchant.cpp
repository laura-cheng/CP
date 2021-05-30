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

#define INF (LLONG_MAX / 2)
#define MOD 1000000007
#define eps (1e-9)

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
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
namespace solver {
	int n, K;
	vector<vector<int>> dis, dp, buy, sell, d1;
	void init_(int _n, int _k) {
		n = _n, K = _k;
		dis.assign(n + 1, vector<int>(n + 1, INF));
		dp.assign(n + 1, vector<int>(n + 1, 0));
		buy.assign(n + 1, vector<int>(K + 1, INF));
		sell.assign(n + 1, vector<int>(K + 1, -INF));
		return;
	}
	bool check(int x) {
		d1.assign(n + 1, vector<int>(n + 1, INF));
		rep(i, 1, n) rep(j, 1, n) d1[i][j] = 
			min(dis[i][j], INF / x) * x - dp[i][j];
		rep(k, 1, n) rep(i, 1, n) rep(j, 1, n) 
			d1[i][j] = min(d1[i][j], d1[i][k] + d1[k][j]);
		rep(i, 1, n) if(d1[i][i] <= 0) return 1;
		return false;
				
	}
	int solve() {
		rep(k, 1, n) rep(i, 1, n) rep(j, 1, n) {
			dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
		}
		rep(i, 1, n) rep(j, 1, n) rep(k, 1, K) {
			dp[i][j] = max(dp[i][j], sell[j][k] - buy[i][k]);
		} 
		int l = 0, r = 1e9 + 1;
		while(r - l > 1) {
			int mid = (l + r) / 2;
			if(check(mid)) l = mid;
			else r = mid;
		}
		return l;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, k; cin >> n >> m >> k;
	init_(n, k);
	rep(i, 1, n) rep(j, 1, k) {
		int x, y; cin >> x >> y;
		if(x != -1) buy[i][j] = x;
		if(y != -1) sell[i][j] = y;
	}
	rep(i, 1, m) {
		int a, b, c; cin >> a >> b >> c;
		dis[a][b] = min(dis[a][b], c);
	}
	cout << solve() << "\n";
	return 0;
} 

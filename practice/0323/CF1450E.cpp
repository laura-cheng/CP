#define wiwihorz
#include <bits/stdc++.h>
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

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {
	while(L < R) cerr << *L << " \n"[next(L) == R], ++L;
}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct DSU {
	int n;
	vector<int> par, rk;
	void init_(int _n) {
		n = _n;
		par.assign(n + 1, 0);
		rk.assign(n + 1, 0);
		rep(i, 1, n) par[i] = i;
	}
	int find_par(int a) {
		if(par[par[a]] == par[a]) return par[a];
		else return par[a] = find_par(par[a]);
	}
	void unite(int a, int b) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return;
		if(rk[aa] > rk[bb]) par[bb] = aa;
		else if(rk[bb] > rk[aa]) par[aa] = bb;
		else rk[aa] ++, par[bb] = aa;
	}
	bool same(int a, int b) {
		return find_par(a) == find_par(b);
	}

} ;
namespace AC {
	int n, m; 
	bool yes;
	DSU dsu;
	vector<vector<int>> dp;
	void init_(int _n, int _m) {
		n = _n, m = _m, yes = 1;
		dp.assign(n + 1, vector<int>(n + 1, INF));
		rep(i, 1, n) dp[i][i] = 0;
		dsu.init_(2 * n);
	}
	bool floyd() {
		rep(k, 1, n) rep(i, 1, n) rep(j, 1, n) {
			dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
		}
		rep(i, 1, n) if(dp[i][i] < 0) return false;
		return true;
	}
	void add_edge(int tp, int a, int b) {
		if(tp == 1) {
			dp[b][a] = -1;
			dp[a][b] = 1;
		}
		else {
			dp[a][b] = 1;
			dp[b][a] = 1;
		}
		dsu.unite(a + n, b);
		dsu.unite(a, b + n);
		if(dsu.same(a, b)) yes = 0;
	}
	void solve() {
		if(!yes || !floyd()) {
			cout << "NO\n";
			return;
		}
		int ans = -INF, id = 0, amn, amx;
		rep(i, 1, n) {
			int mx = -INF, mn = INF;
			rep(j, 1, n) {
				mx = max(mx, dp[i][j]);
				mn = min(mn, dp[i][j]);
			}
			if(mx - mn > ans) {
				ans = mx - mn, id = i;
				amn = mn, amx = mx;
			}
		}
		cout << "YES\n";
		cout << ans << "\n";
		rep(i, 1, n) {
			cout << dp[id][i] - amn << " \n"[i == n];
		}
	}
};
using namespace AC;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n, m);
	rep(i, 1, m) {
		int tp, a, b;
		cin >> a >> b >> tp;
		add_edge(tp, a, b);
	}
	solve();
	
	return 0;
}

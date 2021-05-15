#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1e9
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
	while(L < R) cerr << *L << " \n"[next(L) == R], ++ L;
}
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct AC {
	int n, tar, l, st, ans;
	struct edge {
		int to, cost, rev;
	};
	vector<vector<edge>> mp;
	vector<int> dp, sc, bg, d;
	void init_(int _n) {
		n = _n;
		mp.assign(n + 1, vector<edge>());
		dp.assign(n + 1, 0);
		return;
	}
	bool trace(int x, int par, int g) {
		if(x == g) return true;
		for(auto &i : mp[x]) {
			if(i.to == par) continue;
			bool yes = trace(i.to, x, g);
			if(yes) {
				mp[i.to][i.rev].cost = -INF;
				i.cost = -INF; 
				return true;
			}
		}
		return false;
	}
	int dfs(int x, int par, int dd = 0) {

	}
	int solve1() {
		dfs(1, 1);
		int ans = 0;
		rep(i, 1, n) ans = max(dp[i], ans);
		return 2 * (n - 1) - ans + 1;
	}
	int solve2() {
		dfs(1, 1);
		int x = 0, ans = 0;
		rep(i, 1, n) {
			if(dp[x] < dp[i]) {
				x = i, ans = dp[i];
			}
		}
		trace(bg[x], bg[x], sc[x]);
		dp.assign(n + 1, 0);
		dfs(1, 1);
		int cur = 0;
		rep(i, 1, n) cur = max(cur, dp[i]);
		return 2 * (n - 1) - cur - ans + 2;
	}
} ac;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	ac.init_(n);
	rep(i, 1, n - 1) {
		int a, b; cin >> a >> b;
		int aa = ac.mp[a].size();
		int bb = ac.mp[b].size();
		ac.mp[a].push_back({b, 1, bb});
		ac.mp[b].push_back({a, 1, aa});
	}
	if(n == 1) cout << "0\n";
	else if(k == 1) cout << ac.solve1() << "\n";
	else cout << ac.solve2() << "\n";
	
	return 0;
}



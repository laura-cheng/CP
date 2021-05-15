#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

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
	int n, k;
	vector<int> t;
	vector<vector<int>> mp;
	vector<vector<vector<int>>> dp;
	void init_(int _n, int _k) {
		n = _n, k = min(_k, 2 * n);
		t.assign(n + 1, 0);
		mp.assign(n + 1, vector<int>());
		dp.assign(n + 1, vector<vector<int>>());
	}

	void dfs(int x, int par) {
		dp[x].assign(2, vector<int>(k + 1, -INF));
		dp[x][0][0] = 0;
		for(auto i : mp[x]) {
			if(i == par) continue;
			dfs(i, x);
			rrep(m, 0, k) {			
				rep(st, 0, k) {
					if(m - st - 1 >= 0) {
						dp[x][1][m] = max(dp[x][1][m], dp[x][0][m - st - 1] + max(dp[i][0][st], dp[i][1][st]));
					}
					if(m - st - 2 >= 0) {
						dp[x][1][m] = max(dp[x][1][m], dp[x][1][m - st - 2] + dp[i][0][st]);
						dp[x][0][m] = max(dp[x][0][m],dp[x][0][m - st - 2] + dp[i][0][st]);
					}
				}	
			}
			dp[i].clear();
		}
		rep(i, 0, k) dp[x][0][i] += t[x], dp[x][1][i] += t[x];
		return;
	}
	int solve() {
		dfs(1, 1);
		int v = 0;
		rep(i, 0, k) {
			v = max(v, dp[1][0][i]);
			v = max(v, dp[1][1][i]);
		}
		return v;
	}
} ac;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	ac.init_(n, k);
	rep(i, 1, n) cin >> ac.t[i];
	rep(i, 1, n - 1) {
		int a, b; cin >> a >> b;
		ac.mp[a].push_back(b);
		ac.mp[b].push_back(a);
	}
 	cout << ac.solve() << "\n";
	return 0;
}



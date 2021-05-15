#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) for(int i = a; i <= b; i++)

#define INF 1000000000000000000
#define MAXN 1000005
#define MOD 1000000007
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a )
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ",kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, m;
	vector<vector<int>> a, dp;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		a.assign(n + m + 1, vector<int>(n + m + 1, 0));
		dp.assign(n + m + 1, vector<int>(n + m + 1, INF));
	} 
	void build() {
		rep(i, 1, m + n) rep(j, 1, m + n) {
			if(a[i][j]) dp[i][j] = 0;
		}
		rep(l, 1, m + n) rep(i, 1, m + n) rep(j, 1, m + n) {
			rep(k, 1, m) {
				dp[i][j] = min(dp[i][j], max(dp[k][j], dp[k][i]) 
					+ bool(dp[k][j] == dp[k][i] && dp[k][j]) + 1);
			}
		}
		return;
	}
	int query(int a, int b) {
		if(dp[a][b] == INF) return -1;
		else return dp[a][b];
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int n, m, p;
		cin >> m >> n >> p;
		init_(n, m);
		rep(i ,1, m + n) rep(j, 1, m + n) {
			char x; cin >> x;
			if(x == 'Y') a[i][j] = 1;
		}
		build();
		cout << "Case #" << tt << ": ";
		rep(i, 1, p) {
			int a, b; cin >> a >> b;
			cout << query(a, b) << " \n"[i == p];
		}
	}	
	return 0;
}

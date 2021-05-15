#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define rrep(i, a, b) for(int i = b; i >= a; --i)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1e9
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

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
namespace AC {
	const int N = 505;
	int n, m, dp[N][N], ans = 0, cnt = 0;
	int pre[N][N][N], ways[N][N][N], anses[N][N];
	void init_(int _n, int _m) {
		n = _n, m = _m;
		rep(i, 1, n) rep(j, 1, n) dp[i][j] = INF;
		rep(i, 1, n) dp[i][i] = 0;
		cnt = ans = 0;	
	}
	void solve() {
		rep(k, 1, n) rep(i, 1, n) rep(j, 1, n) {
			dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
		}
		rep(k, 1, n) rep(i, 1, n) rep(j, 1, n)  {
			int cc = dp[k][i] - dp[k][j];
			if(cc < 0) continue;
			ways[i][j][cc] ++;
			pre[i][j][cc] += cc;
		}
		rep(i, 1, n) rep(j, 1, n) rrep(k, 0, n) {
			pre[i][j][k] += pre[i][j][k + 1];
			ways[i][j][k] += ways[i][j][k + 1];
		}
		rep(k, 1, n) rep(i, 1, n) rep(j, i + 1, n) {
			int x = dp[k][i] + 1;
			anses[i][j] += pre[k][j][x] - ways[k][j][x] * x;		
		}	
		rep(i, 1, n) rep(j, i + 1, n) ans = max(ans, anses[i][j]);
		rep(i, 1, n) rep(j, i + 1, n) cnt += bool(ans == anses[i][j]);
	}
};
using namespace AC;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n, m);
	rep(i, 1, m) {
		int a, b; cin >> a >> b;
		dp[a][b] = dp[b][a] = 1;
	} 
	solve();
	cout << cnt << " " << ans << "\n";
	return 0;
}

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
#define MAXN 1000005
#define eps (1e-9)

#define int long long int
#define pii pair<int, int>
#define lld long double
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2>  void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...)
#define vprint(...)
#endif
namespace solver {
	int n, k;
	vector<vector<int>> dp;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		dp.assign(n + 1, vector<int>(n + 1, 0));
	}
	int solve() {
		dp[2][0] = 1;
		rep(i, 3, n) dp[i][1] = 1;
		rep(i, 3, n) rep(j, 2, k) {
			int cs1 = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
			int cs2 = 0;
			rep(m, 3, i - 1) rep(l, 1, j) {
				cs2 = (cs2 + (dp[i - m + 2][j - l] 
					* (dp[m - 1][l - 1] + dp[m - 1][l]))) % MOD;
			}
			dp[i][j] = (cs1 + cs2) % MOD;
		}
		return dp[n][k];
	} 
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	init_(n, k);
	cout << solve() << "\n";
	
	return 0;
}

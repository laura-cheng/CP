#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i= b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define MAXN 1000005
#define eps (1e-9)

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
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct DP {
	int n, k;
	vector<vector<int>> K, dp;
	vector<int> a;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		K.assign(k + 2, vector<int>(n + 2, 0));
		dp.assign(k + 1, vector<int>(n + 1, INF));
		a.assign(n + 1, 0);
		return;
	}
	int w(int i, int j) {
		int x = (i + 1 + j) / 2, y = ceil(i + 1 + j, 2);
		int ans1 = INF, ans2 = INF;
		ans1 = a[j] - a[x] - (a[x] - a[x - 1]) * (j - x) +
			(a[x] - a[x - 1]) * (x - i) - a[x] + a[i];
		ans2 = a[j] - a[y] - (a[y] - a[y - 1]) * (j - y) +
			(a[y] - a[y - 1]) * (y - i) - a[y] + a[i];
		return min(ans1, ans2);
	}
	int solve() {
		sort(all(a));
		k = min(k, n);
		rep(i, 1, n) a[i] += a[i - 1];
		rep(i, 0, k) dp[i][0] = 0;
		rep(i, 1, k) {
			K[i][n + 1] = n - 1;
			rrep(j, 1, n) {
				rep(m, K[i - 1][j], K[i][j + 1]) {
					int v = dp[i - 1][m] + w(m, j);
					if(v < dp[i][j]) {
						dp[i][j] = v;
						K[i][j] = m;
					}
				}
			}
		}
		return dp[k][n];
	
	} 
} dp;
struct DP2 {
	int n, k;
	vector<vector<int>> dp;
	vector<int> a;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		dp.assign(k + 1, vector<int>(n + 1, INF));
		a.assign(n + 1, 0);
		return;
	}
	int w(int i, int j) {
		int x = (i + 1 + j) / 2, y = ceil(i + 1 + j, 2);
		int ans1 = INF, ans2 = INF;
		ans1 = a[j] - a[x] - (a[x] - a[x - 1]) * (j - x) +
			(a[x] - a[x - 1]) * (x - i) - a[x] + a[i];

		ans2 = a[j] - a[y] - (a[y] - a[y - 1]) * (j - y) +
			(a[y] - a[y - 1]) * (y - i) - a[y] + a[i];

		return min(ans1, ans2);
	}
	int solve() {
		sort(all(a));
		k = min(k, n);
		rep(i, 1, n) a[i] += a[i - 1];
		dp[0][0] = 0;
		rep(i, 1, k) rep(j, 1, n) {
			rep(m, 0, j - 1) {
				dp[i][j] = min(dp[i][j], dp[i - 1][m] + w(m, j));
			}
		
		}
		return dp[k][n];
	
	} 
};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	dp.init_(n, k);
	rep(i, 1, n - 1) {
		cin >> dp.a[i];
	}
	cout << dp.solve() << "\n";
	
	return 0;
}

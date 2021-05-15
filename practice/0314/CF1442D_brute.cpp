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
struct DP1 {
	int n, k;
	vector<vector<int>> a, dp, K;
	vector<int> t;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		a.assign(n + 1, vector<int>());
		dp.assign(n + 1, vector<int>(k + 1, 0));
		K.assign(n + 1, vector<int>(k + 1, 0));
		t.assign(n + 1, 0);
	}
	int solve() {
 		rep(i, 1, n) {
 			rep(j, 0, k) {
 				rep(m, max(0ll, j - t[i]) ,j) {
 					int v = dp[i - 1][m] + a[i][j - m];
 					if(dp[i][j] < v) {
 						K[i][j] = m;
 						dp[i][j] = v;
 					}
 				}
 			}
 			vprint(all(K[i]));
 		}
 		
 		return dp[n][k];
	}
} dp;
struct DP2{
	int n, k;
	vector<vector<int>> a, dp, K;
	vector<int> t;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		a.assign(n + 1, vector<int>());
		dp.assign(n + 1, vector<int>(k + 1, 0));
		K.assign(n + 1, vector<int>(k + 1, 0));
		t.assign(n + 1, 0);
	}
	int solve() {
		rep(i, 1, n) {
			CDQ(i, 0, k, 0, t[i]);
		}
		return dp[n][k];
	}
	void CDQ(int x, int L, int R, int l, int r) {
		if(L == R) {
			rep(i, l, r) {
				if(i > L) continue;
				dp[x][L] = max(dp[x][L], dp[x - 1][L - i] + a[x][i]);
			}
			return;
		}
		int mid = (L + R) / 2, best = l;
		rep(i, l, r) {
			if(i > mid) continue;
			int v = dp[x - 1][mid - i] + a[x][i];
			if(v > dp[x][mid]) {
				best = i;
				dp[x][mid] = v;
			}
		}
		CDQ(x, L, mid, l, best);
		CDQ(x, mid + 1, R, best, r);
		return;
	}


} ;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	dp.init_(n, k);
	rep(i, 1, n) {
		cin >> dp.t[i];
		dp.a[i].assign(dp.t[i] + 1, 0);
		rep(j, 1, dp.t[i]) {
			cin >> dp.a[i][j];
			dp.a[i][j] += dp.a[i][j - 1];
		}
	}
	cout << dp.solve() << "\n";
	return 0;
}

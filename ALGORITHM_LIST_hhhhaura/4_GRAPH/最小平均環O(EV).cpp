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
struct min_mean_cycle {
	int n, A, B;
	vector<vector<int>> mp, dp;
	void init_(int _n) {
		n = _n , A = 1, B = 0;
		mp.assign(n + 1, vector<int>(n + 1, INF));
		dp.assign(n + 2, vector<int>(n + 1, INF));
		dp[0][0] = 0;
		rep(i, 1, n) mp[0][i] = 0;
	}
	void solve() {
		rep(i, 1, n + 1) rep(k, 0, n) rep(j, 0, n) {
			dp[i][j] = min(dp[i][j], dp[i - 1][k] + mp[k][j]);
		}
		rep(j, 1, n) {
			int curA = 0, curB = 1;
			rep(i, 1, n) {
				if(dp[n + 1][j] == INF || dp[i][j] == INF) continue;
				int aa = dp[n + 1][j] - dp[i][j];
				int bb = n + 1 - i;
				if(curA * bb < curB * aa) curA = aa, curB = bb;
			}
			if(curA && A * curB > B * curA) A = curA, B = curB;
		}
		if(A == 1 && B == 0) A = -1, B = -1;
		else {
			int gcd = __gcd(A, B);
			A /= gcd, B /= gcd;
		}
	}

} a;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	a.init_(n);
	rep(i, 1, n) rep(j, 1, n) {
		int x; cin >> x;
		if(x) a.mp[i][j] = x; 
	}
	a.solve();
	cout << a.A << " " << a.B << "\n"; 
	return 0;
} 

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
namespace SOLVE {
	int n, x, y;
	string s;
	void init_(string _s, int _x, int _y) {
		s = _s, x = _x, y = _y;
		n = s.size();
		s.insert(0, "0");
	}
	int solve() {
		vector<vector<int>> dp(2, vector<int>(n + 1, INF));
		dp[0][0] = dp[1][0] = 0;
		rep(i, 1, n) {
			if(s[i] == 'C') dp[0][i] = min(dp[0][i - 1], dp[1][i - 1] + y);
			else if(s[i] == 'J') dp[1][i] = min(dp[1][i - 1], dp[0][i - 1] + x);
			else {
				dp[0][i] = min(dp[0][i - 1], dp[1][i - 1] + y);
				dp[1][i] = min(dp[1][i - 1], dp[0][i - 1] + x);
			}
		} 
		return min(dp[0][n], dp[1][n]);
	}

};
using namespace SOLVE;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int x, y; string s;
		cin >> x >> y >> s;
		init_(s, x, y);
		cout << "Case #" << tt << ": " << solve() << "\n";
	}
	return 0;
} 

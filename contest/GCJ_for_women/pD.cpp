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
	int n; string s;
	vector<vector<int>> dp, vis;
	void init_(int _n, string _s) {
		n = _n, s= _s;
		dp.assign(n + 1, vector<int>(n + 1, 0));
		vis.assign(n + 1, vector<int>(n + 1, 0));
		rep(i, 1, n) rep(j, i, n) {
			if(((j - i + 1) & 1) == (n & 1)) dp[i][j] = -INF;
			else dp[i][j] = INF;
		} 
	}
	void solve() {
		rep(i, 1, n) rep(j, i, n) {
			int len = (j - i + 1);	
			if(s[i - 1] == s[j - 1] 
				&& s[i - 1] == 'O' && ((len & 1) == (n & 1))) {
				dp[i][j] = -len - 1;
				vis[i][j] = 1;	
			}
			if(s[i - 1] == s[j - 1] 
				&& s[i - 1] == 'I' && ((len & 1) == ((n - 1) & 1))) {
				dp[i][j] = len + 1;	
				vis[i][j] = 1;
			}
			
		}
		rep(i, 1, n) {
			if(n & 1) {
				if(s[i - 1] == 'O') dp[i][i] = -2;
				else dp[i][i] = 1; 
			}
			else {
				if(s[i - 1] == 'I') dp[i][i] = 2;
				else dp[i][i] = -1;
			}
		}
		rep(l, 1, n - 1) rep(i, 1, n - l) {
			int j = l + i, len = l + 1;
			if(vis[i][j]) continue;
			if((len & 1) == (n & 1)) {
				if(s[i - 1] == 'I') dp[i][j] = max({dp[i][j], dp[i + 1][j]});
				if(s[j - 1] == 'I') dp[i][j] = max({dp[i][j], dp[i][j - 1]});
			}
			else {
				if(s[i - 1] == 'O') dp[i][j] = min({dp[i][j], dp[i + 1][j]});
				if(s[j - 1] == 'O') dp[i][j] = min({dp[i][j], dp[i][j - 1]});
			}
		}
		if(dp[1][n] < 0) cout << "O " << -dp[1][n] << "\n"; 
		else cout << "I " << dp[1][n] << "\n";
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		string s; cin >> s;
		init_(s.size(), s);
		cout << "Case #" << tt << ": ";
		solve();
	}
	return 0;
}

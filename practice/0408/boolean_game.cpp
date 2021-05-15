#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

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
#define print(a...) kout("[" + string(#a) + "] = ", a) 
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace subtask2 {
	int n, m, k;
	struct seg {
		int l, r, g;
	};
	vector<seg> a;
	vector<int> dp[2];
	vector<vector<pii>> b;
	void init_(int _n, int _m, int _k) {
		n = _n, m = _m, k = _k;
		a.clear();
		b.assign(n + 1, vector<pii>());
		dp[0].assign(n + 1, 0);
		dp[1].assign(n + 1, 0);
	}
	void solve() {
		for(auto i : a) {
			int cur = 0;
			for(auto j : a) if(i.l <= j.l && i.r >= j.r) {
				cur += j.g;
			}
			b[i.r].push_back({i.l, cur});
			print(i.l, i.r, cur);
		}
		rep(i, 1, n) {
			dp[0][i] = max({0ll, dp[1][i - 1], dp[0][i - 1]});
			dp[1][i] = dp[0][i];
			for(auto j : b[i]) {
				dp[1][i] = max({dp[1][i], dp[1][max(0ll, j.first - 2)] + j.second
					, dp[0][j.first - 1] + j.second});
			}
			print(dp[0][i], dp[1][i]);
		}
		cout << max(dp[1][n], dp[0][n]) << "\n";
	}
	/*
	1
	4 2 1
	-4 -2 5 2
	1 3 0
	1 4 -3
	*/
};
namespace subtask1 {
	int n, m, k;
	struct seg {
		int l, r, g;
	};
	vector<seg> a;
	vector<int> dp;
	vector<vector<pii>> b;
	void init_(int _n, int _m, int _k) {
		n = _n, m = _m, k = _k;
		a.clear();
	}
	void solve() {
		vector<int> ans;
		rep(i, 0, (1 << n) - 1) {
			int cur = 0;
			for(auto j : a) {
				bool yes = 1;
				rep(l, j.l, j.r) 
					yes &= ((i >> (l - 1)) & 1);
				if(yes) cur += j.g;
			}
			ans.push_back(cur);
		}
		sort(all(ans));
		reverse(all(ans));
		rep(i, 0, k - 1) cout << ans[i] << " \n"[i + 1 == k];
	}
};
namespace AC {
	int n, m, k;
	struct seg {
		int l, r, g;
	};
	vector<seg> a;
	vector<vector<int>> dp, pre;
	void init_(int _n, int _m, int _k) {
		n = _n, m = _m, k = _k;
		a.clear();
		dp.assign(n + 1, vector<int>(k, -INF));
	}
	void solve() {
		dp[0][0] = 0;
		rep(i, 1, n) {	
			vector<int> temp;
			rep(j, 0, k - 1) temp.push_back(dp[i - 1][j]);
			rep(j, 1, i) {
				int cur = 0;
				for(auto l : a) if(i >= l.r && j <= l.l) {
					cur += l.g;		
				}
				rep(l, 0, k - 1) temp.push_back(dp[max(0ll, j - 2)][l] + cur);
			}
			sort(all(temp)), reverse(all(temp));
			rep(j, 0, k - 1) dp[i][j] = temp[j]; 
		}
		rep(i, 0, k - 1) cout << dp[n][i] << " \n"[i + 1 == k];
	}
};
using namespace AC;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n, m, k;
		cin >> n >> m >> k;
		init_(n, m, k);
		rep(i, 1, n) {
			int x; cin >> x;
			a.push_back({i, i, x});
		}
		rep(i, 1, m) {
			int l, r, x;
			cin >> l >> r >> x;
			a.push_back({l, r, x});
		}
		solve();
		
	}
	
	return 0;
}

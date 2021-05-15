#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define MAXN 1000005
#define eps (1e-9)

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
struct AC {
	int n, k;
	vector<vector<int>> mp;
	vector<int> sz, hson, a;
	struct pt {
		int st, bk, val;
	};
	void init_(int _n, int _k) {
		n = _n, k = _k, k = min(k, 2 * n);
		mp.assign(n + 1, vector<int>());
		sz.assign(n + 1, 0);
		hson.assign(n + 1, 0);
		a.assign(n + 1, 0);
	}
	void get_sz(int x, int par) {
		sz[x] = 1;
		for(auto i : mp[x]) {
			if(i == par) continue;
			get_sz(i, x);
			sz[x] += sz[i];
			if(sz[hson[x]] < sz[i]) hson[x] = i;
		}
		return;
	}
	vector<pt> dfs(int x, int par) {
		vector<vector<int>> dp(k + 1, vector<int>(2, -1e9));
		vector<pt> cur, ans;
		dp[0][0] = 0;
		if(hson[x]) {
			cur = dfs(hson[x], x);
			for(auto i : cur) {
				if(i.st + 1 <= k) {
					dp[i.st + 1][1] = max(dp[i.st + 1][1], i.val);		
				}
				if(i.st + 2 <= k && !i.bk) {
					dp[i.st + 2][0] = max(dp[i.st + 2][0], i.val);
				}
			}
		}
		for(auto i : mp[x]) {
			if(i == par || i == hson[x]) continue;
			cur = dfs(i, x);
			for(auto j : cur) {
				rrep(m, 0, k) if(m + j.st + 2 <= k && !j.bk) {
					dp[m + j.st + 2][1] = max(
						dp[m + j.st + 2][1],
						dp[m][1] + j.val
					);
				}
				rrep(m, 0, k) if(m + j.st + 1 <= k) {
					dp[m + j.st + 1][1] = max({
						dp[m + j.st + 1][1], 
						dp[m][0] + j.val
					}); 
				}
				rrep(m, 0, k) if(m + j.st + 2 <= k && j.bk == 0) {
					dp[m + j.st + 2][0] = max(
						dp[m + j.st + 2][0],
						dp[m][0] + j.val
					);
				}
			}
		}
		cerr << "sstart\n";
		rep(i, 0, k) rep(j, 0, 1) {
			if(dp[i][j] > 0) print(x, i, j, dp[i][j] + a[x]), ans.push_back({i, j, dp[i][j] + a[x]});
		}
		cerr <<"eend\n";
		ans.push_back({0, 0, a[x]});
		dp.clear(), cur.clear();
		return ans;
	}
	int solve() {
		get_sz(1, 1);
		vector<pt> a = dfs(1, 1);
		int ans = 0;
		for(auto i : a) if(i.st <= k) ans = max(ans, i.val);
		return ans;
	}
} ac;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	ac.init_(n, k);
	rep(i, 1, n) cin >> ac.a[i];
	rep(i, 1, n - 1) {
		int a, b; cin >> a >> b;
		ac.mp[a].push_back(b);
		ac.mp[b].push_back(a);
	}
	cout << ac.solve() << "\n";
	
	return 0;
}

#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl;} 
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n;
	const int MOD = 1000000007;
	vector<int> a, sz, dp, deg, fac, inv;
	vector<vector<int>> mp1, mp2;
	int pow_(int a, int times) {
		int ans = 1;
		for(;times > 0; times >>= 1, a = a * a % MOD) {
			if(times & 1) ans = ans * a % MOD;
		}
		return ans;
	}
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, 0);
		sz.assign(n + 1, 0);
		dp.assign(n + 1, 0);
		deg.assign(n + 1, 0);
		mp1.assign(n + 1, vector<int>());
		mp2.assign(n + 1, vector<int>());
		inv.assign(n + 1, 1);
		fac.assign(n + 1, 1);
		rep(i, 1, n) fac[i] = fac[i - 1] * i % MOD;
		inv[n] = pow_(fac[n], MOD - 2);
		rrep(i, 0, n - 1) inv[i] = inv[i + 1] * (i + 1) % MOD;
	}
	int C(int n, int m) {
		if(n < m || n < 0 || m < 0) return 0;
		return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
	}
	void dfs(int x) {
		sz[x] = 1;
		dp[x] = 1;
		for(auto i : mp2[x]) {
			dfs(i);
			sz[x] += sz[i];
			dp[x] = dp[x] * dp[i] % MOD;
		}
		int sum = 0;
		for(auto i : mp2[x]) {
			dp[x] = dp[x] * C(sz[x] - 1 - sum, sz[i]) % MOD;
			sum += sz[i];
		}
		return;
	}
	int solve() {
		stack<int> s; s.push(1);
		rep(i, 1, n - 1) {
			if(a[i + 1] - a[i] > 1) return 0;
			if(a[i + 1] - a[i] == 1) {
				mp1[i].push_back(i + 1);
				deg[i + 1] ++;
				s.push(i + 1);
			}
			else {
				while(s.size() >= a[i + 1]) {
					int x = s.top(); s.pop();
					mp1[i + 1].push_back(x);
					deg[x] ++;
				}
				if(s.size()) {
					mp1[s.top()].push_back(i + 1);
					deg[i + 1] ++;
				}
				s.push(i + 1);
			}
		}
		queue<int> q;
		rep(i, 1, n) if(!deg[i]) q.push(i);
		assert(q.size() == 1);
		int st = q.front();
		while(q.size()) {
			int cur = q.front(); q.pop();
			for(auto i : mp1[cur]) {
				deg[i] --;
				if(!deg[i]) {
					mp2[cur].push_back(i);
					q.push(i);
				}
			}
 		}
 		dfs(st);
 		return dp[st];
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int n; cin >> n;
		init_(n);
		rep(i, 1, n) cin >> a[i];
		cout << "Case #" << tt << ": " <<  solve() << "\n";
	}
	return 0;
}

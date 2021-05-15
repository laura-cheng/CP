#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1e9
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
// dp[0] = alex chose > max(dp[1] + 1 or dp[2] or 0)
// dp[1] = alex didn't choose and exposed > dp[2] or max(dp[0], dp[1])
// dp[2] = alex didn't choose and not exposed > dp[2] or 0 or at least two exposed
namespace solver {
	int n; 
	vector<vector<int>> mp;
	vector<int> dp1, dp2, dp3;
	void init_(int _n) {
		n = _n;
		mp.assign(n + 1, vector<int>());
		dp1.assign(n + 1, 0);
		dp2.assign(n + 1, 0);
		dp3.assign(n + 1, 0);
	}
	void dfs(int x, int par) {
		int v = 0, v1 = -INF, v2 = -INF, v3 = -INF;
		for(auto i : mp[x]) if(i != par) {
			dfs(i, x);
			dp1[x] += max({dp2[i] + 1, dp3[i], 0ll});
			dp2[x] += dp3[i];
			v3 = max(v3, -dp3[i] + max(dp1[i], dp2[i]));
			dp3[x] += max({dp3[i], dp2[i], dp1[i]});
			v += dp3[i];
			int cur = max(dp1[i], dp2[i]) - max({dp3[i], dp2[i], dp1[i]});
			if(v1 < cur) swap(v1, cur);
			if(v2 < cur) swap(v2, cur);
		}
		dp2[x] += v3;
		dp3[x] = max(v, dp3[x] + v1 + v2 + 1);
		return;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n; init_(n);
	rep(i, 1, n - 1) {
		int a, b; cin >> a >> b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	dfs(1, 1);
	cout << max({dp1[1], dp2[1], dp3[1]}) << "\n";
	return 0;
}

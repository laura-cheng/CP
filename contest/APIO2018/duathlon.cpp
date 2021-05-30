#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i ,a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)

using namespace std;
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().times_since_epoch().count())

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, ans = 0 ;
	vector<vector<int>> mp;
	vector<int> dp, sz;
	void init_(int _n) {
		n = _n, ans = 0;
		mp.assign(n + 1, vector<int>());
		dp.assign(n + 1, 0);
		sz.assign(n + 1, 0);
	}
	void dfs(int x, int par) {
		sz[x] = 1, dp[x] = 0;
		for(auto i : mp[x]) if(i != par) {
			dfs(i, x);
			dp[x] += dp[i] + sz[i];
			sz[x] += sz[i];
		}
		int temp = 0, cur = 0;
		for(auto i : mp[x]) if(i != par) {
			temp += dp[i] * (sz[x] - sz[i]);
			temp += cur * sz[i];
			cur += sz[i];
		}
		ans += temp;
		return;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n);
	rep(i, 1, m) {
		int a, b; cin >> a >> b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	rep(i, 1, n) if(!sz[i]) dfs(i, i);
	cout << ans * 2 << "\n";
	
	return 0;
}

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
#define eps (1e-9)
#define MAXN 1000005

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
namespace SOLVE {
	int n, k;
	vector<vector<int>> mp;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		mp.assign(n + 1, vector<int>());
	}
	int dfs(int x, int par) {
		int ans = 1, cnt = 0;
		for(auto i : mp[x]) {
			if(i == par) continue;
			cnt ++;
			ans = ans * dfs(i, x) % MOD;
		}
		int mx = k - 1 - bool(par != x);
		rep(i, 0, cnt - 1) {
			ans = ans * (mx - i) % MOD;
		}
		return ans;
	}
	int solve() {
		return k * dfs(1, 1) % MOD;
	}

};
using namespace SOLVE;

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	init_(n, k);
	rep(i, 1, n - 1) {
		int x, y; cin >> x >> y;
		mp[x].push_back(y);
		mp[y].push_back(x);
	}
	cout << solve() << "\n";
	return 0;
}

#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define eps (1e-9)
#define MAXN 1000005
#define MOD 1000000007

using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt199374 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, ii;
	vector<vector<int>> mp;
	vector<int> ans, a, id;
	vector<map<int, int>> color, sum;
	void init_(int _n) {
		n = _n, ii = 0;
		mp.assign(n + 1, vector<int>());
		color.assign(n + 1, map<int, int>());
		sum.assign(n + 1, map<int, int>());
		ans.assign(n + 1, 0);
		a.assign(n + 1, 0);
		id.assign(n + 1, 0);
	}
	void insert(int x, int col, int cnt) {
		int ori = color[x][col];
		sum[x][ori] -= col;
		sum[x][ori + cnt] += col;
		color[x][col] += cnt;
		return;
	}
	void dfs(int x, int par) {
		int best = 0, cnt = 0;
		for(auto i : mp[x]) if(i != par) {
			dfs(i, x);
			if(color[id[i]].size() 
				> color[id[best]].size()) best = i;
		}
		int cur = (id[best] ? id[best] : ++ii);
		id[x] = cur, insert(cur, a[x], 1);
		for(auto i : mp[x]) if(i != best && i != par) {
			for(auto j : color[id[i]]) {
				insert(cur, j.first, j.second);
			}
			color[id[i]].clear();
			sum[id[i]].clear();
		}
		ans[x] = sum[cur].rbegin() -> second;
		return;
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n - 1) {
		int x, y; cin >> x >> y;
		mp[x].push_back(y);
		mp[y].push_back(x);
	} 
	dfs(1, 1);
	rep(i, 1, n) cout << ans[i] << " \n"[i == n];
	return 0;
}

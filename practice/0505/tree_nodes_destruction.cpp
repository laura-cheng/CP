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

#define INF 1000000000000000000
#define eps (1e-9)
#define MOD 1000000007

using namespace std;
using namespace __gnu_pbds;

#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace LCA {
	int n, lg;
	vector<vector<int>> mp, ac;
	vector<int> d;
	void dfs(int x, int par, int dd = 0) {
		ac[0][x] = par, d[x] = dd;
		for(auto i : mp[x]) {
			if(i == par) continue;
			dfs(i, x, dd + 1);
		}
	}
	void init_(int _n, vector<vector<int>> _mp) {
		mp = _mp, n = _n;
		lg = 31 - __builtin_clz(n);
		ac.assign(lg + 1, vector<int>(n + 1, 0));
		d.assign(n + 1, 0);
		dfs(1, 1);
		rep(i, 1, lg) rep(j, 1, n) {
			ac[i][j] = ac[i - 1][ac[i - 1][j]];
		}
		return;
	}
	int lca(int a, int b) {
		if(d[a]< d[b]) swap(a, b);
		int need = d[a] - d[b];
		rep(i, 0, lg) if((need >> i) & 1) {
			a = ac[i][a];
		}
		if(a == b) return a;
		rrep(i, 0, lg) if(ac[i][a] != ac[i][b]) {
			a = ac[i][a];
			b = ac[i][b];
		}
		return ac[0][a];
	}	
};
namespace solver {
	int n, ans;
	vector<vector<int>> mp;
	vector<vector<pii>> v;
	vector<bool> vis, used;
	vector<pii> q;
	bool comp(int a, int b) {
		return LCA::d[a] > LCA::d[b];
	}
	void init_(int _n) {
		n = _n, ans = 0;
		mp.assign(n + 1, vector<int>());
		v.assign(n + 1, vector<pii>());
		vis.assign(n + 1, 0);
		used.assign(n + 1, 0);
		q.clear();
	}
	void mark(int x, int par) {
		vis[x] = 1;
		for(auto i : mp[x]) {
			if(i == par || vis[i]) continue;
			mark(i, x);
		}
	}
	void solve() {
		LCA::init_(n, mp);
		vector<int> cur;
		for(auto i : q) {
			int lca = LCA::lca(i.first, i.second);
			v[lca].push_back({i.first, i.second});
			cur.push_back(lca);
		}
		sort(cur.begin(), cur.end(), comp);
		for(auto i : cur) if(!vis[i]) {
			bool yes = 0;
			for(auto j : v[i]) 
				yes |= (!vis[j.first] && !vis[j.second]);
			if(yes) ans ++, mark(i, LCA::ac[0][i]);
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n);
	rep(i, 1, n - 1) {
		int a, b; cin >> a >> b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	rep(i, 1, m) {
		int a, b; cin >> a >> b;
		q.push_back({a, b});
	}
	solve();
	cout << ans << "\n";
	return 0;
}

#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define int long long int 

using namespace std;
namespace centroid_deco {
	int n;
	vector<vector<int>> mp, pre, op;
	vector<int> vis, sz, mx, ans;
	void init_(int _n) {
		n = _n;
		mp.assign(n + 1, vector<int>());
		pre.assign(n + 1, vector<int>());
		op.assign(n + 1, vector<int>());
		vis.assign(n + 1, 0);
		sz.assign(n + 1, 0);
		mx.assign(n + 1, 0);
		ans.assign(n + 1, 0);
	}
	void get_sz(int x, int par) {
		sz[x] = 1, mx[x] = 0;
		for(auto i : mp[x]) {
			if(i == par || vis[i]) continue;
			get_sz(i, x);
			sz[x] += sz[i];
			mx[x] = max(mx[x], sz[i]);
		}
		return;
	}
	int get_cen(int x, int par, int tot) {
		int best = x;
		for(auto i : mp[x]) {
			if(i == par || vis[i]) continue;
			int cur = get_cen(i, x, tot);
			if(max(tot - sz[cur], mx[cur]) < 
				max(tot - sz[best], mx[best])) best = cur;
		}
		return best;
	}
	int dfs(int x, int par, int id, int d, int tp) {
		int ans = 0;
		for(auto i : op[x]) {
			if(i < d) continue;
			ans += i - d;
			pre[id][min(i - d, sz[id])] += tp;
		}
		for(auto i : mp[x]) {
			if(vis[i] || i == par) continue;
			ans += dfs(i, x, id, d + 1, tp);
		}
		return ans;
	}
	int build(int x, int par) {
		int ans = 0;
		pre[x].assign(sz[x] + 1, 0);
		rrep(i, sz[x] + 1, pre[par].size() - 1) pre[x][sz[x]] += pre[par][i];
		rrep(i, 0, sz[x]) pre[x][i] += pre[par][i];
		ans = dfs(x, x, x, 1, -1);
		rrep(i, 0, sz[x] - 1) pre[x][i] += pre[x][i + 1];
		return ans;
	}
	
	int build1(int c, int x) {
		int ans = 0;
		pre[c].assign(sz[x] + 1, 0);
		ans = dfs(c, c, c, 0, 1);
		return ans;
	}
	void put(int x, int par, int id, int sum, int d) {
		sum -= pre[id][d], ans[x] += sum;
		for(auto i : mp[x]) {
			if(i == par || vis[i]) continue;
			put(i, x, id, sum, d + 1);
		}
		return;
	}
	void deco(int x, int par, int sum) {
		get_sz(x, x);
		int c = get_cen(x, x, sz[x]);
		if(x != par) {
			pre[x].clear();
			sum -= build(x, par);
			put(x, x, x, sum, 1);
			pre[x].clear();
		}
		int cur = build1(c, x);
		ans[c] += cur, vis[c] = 1;
		for(auto i : mp[c]) {
			if(vis[i]) continue;
			deco(i, c, cur);
		}
		return;
	}
	void solve() {
		pre[1].assign(n + 1, 0);
		deco(1, 1, 0);
		rep(i, 1, n) cout << ans[i] << "\n";
		return;
	}
};
using namespace centroid_deco;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n);
	rep(i, 1, n - 1) {
		int a, b; cin >> a;
		b = i + 1;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	rep(i, 1, m) {
		int a, b; cin >> a >> b;
		op[a].push_back(b);
	}
	solve();
	return 0;

}

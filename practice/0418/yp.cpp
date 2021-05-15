#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define INF 1000000000000000000
using namespace std;
using namespace __gnu_pbds;
#define int long long int
#define pii pair<int, int>
#define treap tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update>
namespace cd {
	int n, t;
	vector<vector<int>> mp, dis;
	vector<int> dep, pa, sz, mx;
	vector<int> es, cost, vis, id;
	vector<treap> a, b;
	void init_(int _n) {
		n = _n, t = 0;
		mp.assign(n + 1, vector<int>());
		dis.assign(32, vector<int>(n + 1, 0));
		dep.assign(n + 1, 0);
		pa.assign(n + 1, 0);
		sz.assign(n + 1, 0);
		mx.assign(n + 1, 0);
		vis.assign(n + 1, 0);
		a.assign(n + 1, treap());
		b.assign(n + 1, treap());
		id.assign(n + 1, 0);
		es.clear();
		cost.clear();
	}	
	void add_edge(int x, int y, int c) {
		mp[x].push_back(es.size());
		mp[y].push_back(es.size());
		cost.push_back(c);
		es.push_back(x ^ y);
	}
	void get_sz(int x, int par) {
		sz[x] = 1, mx[x] = 0;
		for(auto i : mp[x]) {
			int to = es[i] ^ x;
			if(to == par || vis[to]) continue;
			get_sz(to, x);
			sz[x] += sz[to];
			mx[x] = max(mx[x], sz[to]);
		}
	}
	int get_cen(int x, int par, int tot) {
		int best = x;
		for(auto i : mp[x]) {
			int to = es[i] ^ x;
			if(to == par || vis[to]) continue;
			int cur = get_cen(to, x, tot);
			if(max(mx[cur], tot - sz[cur]) < 
				max(mx[best], tot - sz[best])) best = cur;
		}
		return best;
	}
	void get_dis(int x, int par, int d, int tot) {
		dis[d][x] = tot;
		for(auto i : mp[x]) {
			int to = es[i] ^ x;
			if(to == par || vis[to]) continue;
			get_dis(to, x, d, tot + cost[i]);
		}
	}
	void deco(int x, int p, int d) {
		get_sz(x, x);
		int c = get_cen(x, x, sz[x]);
		dep[c] = d, pa[c] = p, vis[c] = 1;
		get_dis(c, c, d, 0);
		for(auto i : mp[c]) {
			int to = es[i] ^ c;
			if(vis[to]) continue;
			deco(to, c, d + 1);
		}
	}
	void add(int x) {
		int cur = x;
		id[x] = ++t;
		while(cur != -1) {
			a[cur].insert({dis[dep[cur]][x], t});
			if(pa[cur] != -1) b[cur].insert({dis[dep[cur] - 1][x], t});
			cur = pa[cur];
		}
	}
	void minu(int x) {
		int cur = x;
		while(cur != -1) {
			a[cur].erase(a[cur].find({dis[dep[cur]][x], id[x]}));
			if(pa[cur] != -1) b[cur].erase(b[cur].find({dis[dep[cur] - 1][x], id[x]}));
			cur = pa[cur];
		}	
	}
	int check(int x, int k) {
		int ans = a[x].order_of_key({k, INF});
		int cur = x;
		while(pa[cur] != -1) {
			int p = pa[cur];
			int d1 = k - dis[dep[p]][x];			
			ans += a[p].order_of_key({d1, INF});
			ans -= b[cur].order_of_key({d1, INF});
			cur = p;
		}
		return ans;
	}
	int query(int x, int k) {
		int l = -1, r = 1e18;
		while(r - l > 1) {
			int mid = (l + r) / 2;
			if(check(x, mid) >= k) r = mid;
			else l = mid;
		}
		return r;
	}
};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q; cin >> n >> q;
	cd::init_(n);
	rep(i, 1, n - 1) {
		int a, b, c; 
		cin >> a >> b >> c;
		cd::add_edge(a, b, c);
	}
	cd::deco(1, -1, 0);
	rep(i, 1, q) {
		int tp, a, b;
		cin >> tp;
		if(tp == 1) {
			cin >> a;
			cd::add(a);
		}
		else if(tp == 2) {
			cin >> a;
			cd::minu(a);
		}
		else {
			cin >> a >> b;
			int ans = cd::query(a, b);
			cout << ans << "\n";
		}
	}
	return 0;
}

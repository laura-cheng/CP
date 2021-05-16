#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MAXN 1000005
#define MOD 1000000007
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int ,int>
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
vector<vector<int>> mp;
vector<int> es, cost, x, y;
struct segment_tree {
	int n;
	vector<int> seg;
	void init_(int _n) {
		n = _n;
		seg.assign(2 * n + 1, 0);
		return;
	}
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void pull(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int lch = get(L, mid), rch = get(mid + 1, R);
		seg[nd] = max(seg[lch], seg[rch]);
		return;
	}
	void modify(int L, int R, int id, int val) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) seg[nd] = val;
		else {
			if(id <= mid) modify(L, mid, id, val);
			else modify(mid + 1, R, id, val);
			pull(L, R);
		}
		return;
	}
	int query(int L, int R, int l, int r) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return -INF;
		else if(l <= L && r >= R) return seg[nd];
		else {
			return max(
				query(L, mid, l, r),
				query(mid + 1, R, l, r)
			);
		}
	}
};
struct HLD {
	int n, timestamp;
	vector<int> dep, pa, rt;
	vector<int> hson, id, sz;
	segment_tree st;
	void init_(int _n) {
		n = _n, timestamp = 0;
		dep.assign(n + 1, 0);
		pa.assign(n + 1, 0);
		rt.assign(n + 1, 0);
		hson.assign(n + 1, 0);
		id.assign(n + 1, 0);
		sz.assign(n + 1, 0);
		get_info(1, 1);
		deco(1, 1, 1);
		st.init_(n);
	}
	void get_info(int x, int par, int d = 0) {
		sz[x] = 1, pa[x] = par, dep[x] = d;
		int mxid = 0;
		for(auto i : mp[x]) {
			int to = es[i] ^ x;
			if(to == par) continue;
			get_info(to, x, d + 1);
			sz[x] += sz[to];
			if(sz[to] > sz[mxid]) mxid = to;
		}
		hson[x] = mxid;
		return;
	}
	void deco(int x, int top, int par) {
		rt[x] = top, id[x] = ++timestamp;
		if(hson[x]) deco(hson[x], top, x);
		for(auto i : mp[x]) {
			int to = es[i] ^ x;
			if(to == par || to == hson[x]) continue;
			deco(to, to, x);
		}
		return;
	}
	void change(int u, int v, int w) {
		if(dep[u] < dep[v]) swap(u, v);
		st.modify(1, n, id[u], w);
	}
	int ask(int u, int v) {
		int ans = -INF;
		while(rt[u] != rt[v]) {
			if(dep[rt[u]] < dep[rt[v]]) swap(u, v);
			ans = max(ans, st.query(1, n, id[rt[u]], id[u]));
			u = pa[rt[u]];
		}
		if(u != v) {
			if(dep[u] < dep[v]) swap(u, v);
			ans = max(ans, st.query(1, n, id[v] + 1, id[u]));
		}
		return ans;
	}

} hld;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		mp.assign(n + 1, vector<int>());
		es.clear(), cost.clear();
		x.clear(), y.clear();
		rep(i, 1, n - 1) {
			int a, b, c;
			cin >> a >> b >> c;
			es.push_back(a ^ b);
			cost.push_back(c);
			x.push_back(a);
			y.push_back(b);
			mp[a].push_back(es.size() - 1);
			mp[b].push_back(es.size() - 1);
		}
		hld.init_(n);
		rep(i, 0, n - 2) {
			hld.change(x[i], y[i], cost[i]);
		}
		string op;
		while(cin >> op && op[0] != 'D') {
			int a, b; cin >> a >> b;
			if(op[0] == 'C') {
				hld.change(x[a - 1], y[a - 1], b);
			}
			else cout << hld.ask(a, b) << "\n";
		}
		
	}
	return 0;
}



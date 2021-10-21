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


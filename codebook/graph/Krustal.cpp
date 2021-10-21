int n, m;
struct edge {
	int u, v, cost;
	bool operator<(edge b) {
		return cost < b.cost;
	}
};
vector<edge> es;
struct DSU {
	int n;
	vector<int> par, rk;
	void init(int _n) {
		n = _n;
		par.assign(n + 1, 0);
		rk.assign(n + 1, 0);
		rep(i, 1, n) par[i] = i;
		return;
	} 
	int find_par(int a) {
		if(par[par[a]] == par[a]) return par[a];
		else return par[a] = find_par(par[a]);
	}
	bool same(int a, int b) {
		return find_par(a) == find_par(b);
	}
	void unite(int a, int b) {
		int aa = find_par(a), bb = find_par(b);
		if(aa == bb) return;
		if(rk[aa] > rk[bb]) par[bb] = aa;
		else if(rk[bb] > rk[aa]) par[aa] = bb;
		else par[bb] = aa, rk[aa] ++;
	}
}dsu;
int krustal() {
	dsu.init(n);
	sort(all(es));
	int ans = 0;
	for(auto i : es) {
		if(!dsu.same(i.u, i.v)) {
			ans += i.cost;
			dsu.unite(i.u, i.v);
		}
	}
	rep(i, 1, n) {
		if(dsu.find_par(i) 
			!= dsu.find_par(1)) return -1;
	}
	return ans;
}


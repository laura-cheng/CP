struct DSU {
	int n;
	vector<int> par, rk;
	void init_(int n) {
		par.assign(n + 1, 0);
		rk.assign(n + 1, 0);
		rep(i, 1, n) par[i] = i;
	}
	int find_par(int x) {
		if(par[par[x]] == par[x]) return par[x];
		else return par[x] = find_par(par[x]);
	}
	void unite(int a, int b) {
		int aa = find_par(a), bb = find_par(b);
		if(aa == bb) return;
		if(rk[aa] > rk[bb]) par[bb] = aa;
		else if(rk[bb] > rk[aa]) par[aa] = bb;
		else par[bb] = aa, rk[aa] ++;
		return;
	}
	bool same(int a, int b) {
		return find_par(a) == find_par(b);
	}
}dsu;

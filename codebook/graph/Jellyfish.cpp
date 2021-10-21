namespace solver {
	int n, ii;
	vector<int> cyc, id, len, es, to, pre, d;
	vector<vector<int>> mp;
	void init_(int _n) {
		n = _n, ii = 0, mx = 0;
		cyc.assign(n + 1, 0);
		id.assign(n + 1, 0);
		len.assign(n + 1, 0);
		es.assign(n + 1, 0);
		to.assign(n + 1, -1);
		pre.assign(n + 1, 0);
		d.assign(n + 1, 0);
		mp.assign(n + 1, vector<int>());
	}
	void dfs1(int x, int par) {
		for(auto i : mp[x]) if(i != par) {
			int t = es[i] ^ x; 
			if(!pre[t]) pre[t] = i, dfs1(t, i);
			else if(!cyc[t]) {
				int cur = x;
				while(cur != t) {
					id[cur] = ++ii;
					to[pre[cur]] = ii + 1;
					cyc[cur] = 1;
					cur = es[pre[cur]] ^ cur;
				}
				id[t] = ++ii;
				to[i] = 1;
				cyc[t] = 1;
			}
		}
	}
	void dfs2(int x, int par, int dd, int id) {
		len[id] = max(len[id], dd);
		int ch1 = 0, ch2 = 0;
		for(auto i : mp[x]) if(i != par) {
			int t = es[i] ^ x;
			if(!cyc[t]) {
				dfs2(t, i, dd + 1, id);
				int cur = d[t];
				d[x] = max(d[x], cur);
				if(cur > ch1) swap(cur, ch1);
				if(cur > ch2) swap(cur, ch2);
			}
		}
		d[x] = max(d[x], dd);
	}
	void solve() {
		pre[1] = -1, dfs1(1, -1);
		rep(i, 1, n) if(cyc[i]) {
			dfs2(i, -1, 1, id[i]);
		}
		len.resize(2 * ii + 1);
		rep(i, 1, ii) len[ii + i] = len[i];
	}
};

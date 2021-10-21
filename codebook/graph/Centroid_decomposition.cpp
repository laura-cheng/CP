vector<int> es, cost, yes;
vector<vector<int>> mp;
struct centroid_deco {
	int n;
	vector<int> sz, mx, pa, dep, vis;
	vector<vector<int>> dis;
	vector<int> cnt, sum, minu;
	void init_(int _n) {
		n = _n;
		sz.assign(n + 1, 0);
		mx.assign(n + 1, 0);
		pa.assign(n + 1, 0);
		dep.assign(n + 1, 0);
		cnt.assign(n + 1, 0);
		sum.assign(n + 1, 0);
		minu.assign(n + 1, 0);
		vis.assign(n + 1, 0);
		dis.assign(32, vector<int>(n + 1, 0));
		deco(1);
		return;
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
			if(max(tot - sz[cur], mx[cur]) < 
				max(tot - sz[best], mx[best])) best = cur;
		}
		return best;
	}
	void get_dis(int x, int par, int d, int tot = 0) {
		dis[d][x] = tot;
		for(auto i : mp[x]) {
			int to = es[i] ^ x;
			if(to == par || vis[to]) continue;
			get_dis(to, x, d, tot + cost[i]);
		}
		return;
	}
	void deco(int x, int par = -1, int d = 0) {
		get_sz(x, x);
		int c = get_cen(x, x, sz[x]);
		vis[c] = 1, dep[c] = d, pa[c] = par;
		get_dis(c, c, d);
		for(auto i : mp[c]) {
			int to = es[i] ^ c;
			if(vis[to]) continue;
			deco(to, c, d + 1);
		}
	}
	void modify(int x) {
		int cur = x;
		while(cur != -1) {
			cnt[cur] ++ ;
			sum[cur] += dis[dep[cur]][x];
			if(dep[cur]) minu[cur] += dis[dep[cur] - 1][x];
			cur = pa[cur];
		}
	}
	int query(int x) {
		int cur = x, ans = sum[cur];
		while(pa[cur] != -1) {
			int f = pa[cur], c = cur;
			ans += sum[f] - minu[c]
				+ (cnt[f] - cnt[c]) * dis[dep[f]][x];
			cur = pa[cur]; 
		}
		return ans;
	}

} deco;


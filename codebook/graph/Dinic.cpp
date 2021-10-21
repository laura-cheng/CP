struct Dinic {
	struct edge {
		int to, cap, rev;
	};
	vector<int> level, iter;
	vector<vector<edge>> mp;
	int n, s, t;
	void init(int _n, int _s, int _t) {
		n = _n, s = _s, t = _t;
		mp.assign(n + 1, vector<edge>());
		level.assign(n + 1, INF);
		iter.assign(n + 1, 0);
	}
	void add_edge(int u, int v, int cap) {
		mp[u].push_back({v, cap, signed(mp[v].size())});
		mp[v].push_back({u, 0, signed(mp[u].size()) - 1});
	}
	bool bfs() {
		level.assign(n + 1, INF);
		iter.assign(n + 1 , 0);
		level[s] = 0;
		queue<int> q; q.push(s);
		while(q.size()) {
			int cur = q.front(); q.pop();
			for(auto i : mp[cur]) {
				if(level[i.to] == INF && i.cap > 0) {
					q.push(i.to);
					level[i.to] = level[cur] + 1;
				}
			}
		}
		if(level[t] == INF) return false;
		return true;
	}
	int dfs(int cur, int flow) {
		if(cur == t) return flow;
		for(int &k = iter[cur]; k < mp[cur].size(); k ++) {
			edge &i = mp[cur][k];
			if(level[i.to] != level[cur] + 1 || i.cap <= 0) continue;
			int res = dfs(i.to, min(flow, i.cap));
			if(res > 0) {
				i.cap -= res;
				mp[i.to][i.rev].cap += res;
				return res;
			}		
		}
		return 0;
	}
	int flow() {
		int ans = 0;
		while(bfs()) {
			int res = 0;
			while(res = dfs(s, INF), res) {
				ans += res;
			}
		}
		return ans;
	}
};

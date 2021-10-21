struct edge {
	int t, cost;
};
vector<vector<edge>> mp;
vector<int> d, vis;
int solve(int s, int t) {
	d.assign(n + 1, INF);
	vis.assign(n + 1, 0);
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push({0, s}), d[s] = 0;
	while(pq.size()) {
		int cur = pq.top().second; pq.pop();
		if(vis[cur]) continue;
		vis[cur] = 1;
		for(auto i : mp[cur]) {
			if(d[i.t] > d[cur] + i.cost) {
				d[i.t] = d[cur] + i.cost;
				pq.push(pii(d[i.t], i.t));
			}
		}
	}
	if(d[t] == INF) return -1;
	else return d[t];

} 

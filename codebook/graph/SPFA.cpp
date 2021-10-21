struct edge {
	int t, cost;
};
vector<vector<edge>> mp;
vector<int> cnt, d;
int solve(int s, int t) {
	cnt.assign(n + 1, 0);
	d.assign(n + 1, INF);
	queue<int> q;
	q.push(s), d[s] = 0;
	while(q.size()) {
		int cur = q.front();
		q.pop(), cnt[cur] ++;
		if(cnt[cur] >= n) return -INF;
		for(auto i : mp[cur]) {
			if(d[i.t] > d[cur] + i.cost) {
				d[i.t] = d[cur] + i.cost;
				q.push(i.t);
			}
		}
	}
	if(d[t] == INF) return -1;
	else return d[t];
}

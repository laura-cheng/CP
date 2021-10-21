int n, m, ii;
vector<int> vis, match;
vector<vector<int>> mp;
void init_(int _n, int _m) {
	n = _n, m = _m ii = 0;
	mp.assign(n + 1, vector<int>());
	vis.assign(m + 1, 0);
	match.assign(m + 1, -1);
	return;
}
bool dfs(int x) {
	for(auto i : mp[x]) {
		if(vis[i] == ii) continue;
		vis[i] = ii;
		if(match[i] == -1 || dfs(match[i])) {
			match[i] = x;
			return true;
		}
	}
	return false;
}
int solve() {
	int ans = 0;
	rep(i, 1, n) ans += dfs(i);
	return ans;
}

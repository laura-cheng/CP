int pow_(int a, int times, int mod) {
	int ans = 1;
	for(;times > 0; times >>= 1, a = (a * a) % mod) {
		if(times & 1) ans = (ans * a) % mod;
	}
	return ans;
}
int solve(int a, int b, int n) {
	map<int, int> mp;
	int ans = INF, k = sqrt(n) + 1;
	rrep(i, 0, k) mp[pow_(a, i * k, n)] = i;
	rep(i, 0, k) {
		int cur = b * pow_(a, i, n) % n;
		if(mp.find(cur) != mp.end()) {
			int aa = mp[cur];
			if(aa * k - i >= 0)
			ans = min(ans, aa * k - i);
		}
	}
	if(ans == INF) return -1;
	else return ans;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int a, b, n;
	while(cin >> a >> b >> n) {
		int ans = solve(a, b, n);
		if(ans == -1) cout << "NOT FOUND\n";
		else cout << ans << "\n";
	}
	return 0;
}

struct min_mean_cycle {
	int n, A, B;
	vector<vector<int>> mp, dp;
	void init_(int _n) {
		n = _n , A = 1, B = 0;
		mp.assign(n + 1, vector<int>(n + 1, INF));
		dp.assign(n + 2, vector<int>(n + 1, INF));
		dp[0][0] = 0;
		rep(i, 1, n) mp[0][i] = 0;
	}
	void solve() {
		rep(i, 1, n + 1) rep(k, 0, n) rep(j, 0, n) {
			dp[i][j] = min(dp[i][j], dp[i - 1][k] + mp[k][j]);
		}
		rep(j, 1, n) {
			int curA = 0, curB = 1;
			rep(i, 1, n) {
				if(dp[n + 1][j] == INF || dp[i][j] == INF) continue;
				int aa = dp[n + 1][j] - dp[i][j];
				int bb = n + 1 - i;
				if(curA * bb < curB * aa) curA = aa, curB = bb;
			}
			if(curA && A * curB > B * curA) A = curA, B = curB;
		}
		if(A == 1 && B == 0) A = -1, B = -1;
		else {
			int gcd = __gcd(A, B);
			A /= gcd, B /= gcd;
		}
	}

} a;

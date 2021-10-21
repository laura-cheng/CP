// DP on cactus
/*
Divide into three cases
1. bridge => merge 
2. back edge => label it
3. forward edge => operate cycle
*/
#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
#define INF 1000000000
using namespace std;
namespace solver {
	int n, timestamp;
	vector<int> es, L, D, bad, pa;
	vector<vector<int>> mp, dp;
	void init_(int _n) {
		n = _n, timestamp = 0;
		es.clear();
		L.assign(n + 1, 0);
		D.assign(n + 1, 0);
		pa.assign(n + 1, 0);
		mp.assign(n + 1, vector<int>());
		dp.assign(2, vector<int>());
		dp[1].assign(n + 1, 1);
		dp[0].assign(n + 1, 0);
	}
	void add_edge(int a, int b) {
		mp[a].push_back(es.size());
		mp[b].push_back(es.size());
		es.push_back(a ^ b);
		bad.push_back(0);
		if(a == b) dp[0][a] = INF;
	}
	void dfs(int x, int par) {
		L[x] = D[x] = ++timestamp;
		for(auto i : mp[x]) if(i != par) {
			int to = es[i] ^ x;
			if(!D[to]) pa[to] = x, dfs(to, i);
			if(bad[i]) {
				vector<int> v1, v2;
				v1 = {0, INF}, v2 = {0, 0};
				for(int j = to; j != x; j = pa[j]) {
					v2[0] = v1[1] + dp[0][j];
					v2[1] = min(v1[0], v1[1]) + dp[1][j];
					v1.swap(v2);
				}
				dp[0][x] += v1[1];
				v1 = {INF, 0}, v2 = {0, 0};
				for(int j = to; j != x; j = pa[j]) {
					v2[0] = v1[1] + dp[0][j];
					v2[1] = min(v1[0], v1[1]) + dp[1][j];
					v1.swap(v2);
				}
				dp[1][x] += min(v1[0], v1[1]);
			}
			else if(D[to] < D[x]) {
				bad[i] = 1;
				L[x] = min(L[x], D[to]);
			}
			else {
				L[x] = min(L[x], L[to]);
				if(L[to] > D[x]) {
					dp[0][x] += dp[1][to];
					dp[1][x] += min(dp[1][to], dp[0][to]);
				}
			}
		}
	}
};

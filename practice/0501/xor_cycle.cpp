#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b;i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
using namespace std;
#define int long long int
namespace xorb {
	vector<int> b(60 + 1, 0);
	void insert(int x) {
		rrep(i, 0, 60) if((x >> i) & 1){
			if(b[i]) x ^= b[i];
			else b[i] = x, x = 0;
			if(x == 0) return;
		}
		return;
	}
};
namespace solver {
	int n;
	vector<int> d, vis, es, cost;
	vector<vector<int>> mp;
	void init_(int _n) {
		n = _n;
		d.assign(n + 1, 0);
		vis.assign(n + 1, 0);
		es.clear();
		cost.clear();
		mp.assign(n + 1, vector<int>());
	}
	void dfs(int x, int par, int dd = 0) {
		d[x] = dd, vis[x] = 1;
		for(auto i : mp[x]) if(i != par) {
			int to = es[i] ^ x;
			if(!vis[to]) dfs(to, i, dd ^ cost[i]);
			else xorb::insert(dd ^ cost[i] ^ d[to]);
		}
		return;
	}
	int solve() {
		dfs(1, -1, 0);
		int ans = 0;
		rrep(i, 0, 60) if((ans ^ xorb::b[i]) > ans) {
			ans ^= xorb::b[i];
		}
		return ans;
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n);
	rep(i, 1, m) {
		int a, b, c; 
		cin >> a >> b >> c;
		mp[a].push_back(i - 1);
		mp[b].push_back(i - 1);
		es.push_back(a ^ b);
		cost.push_back(c);
	} 
	cout << solve() << "\n";
	return 0;
}


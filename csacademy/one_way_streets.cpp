#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define all(x) x.begin(), x.end()
using namespace std;
#define int long long int
#define pii pair<int, int>
namespace solver {
	int n, m, k, ii, timestamp, bccid;
	vector<int> es, L, D, bcc;
	vector<int> id, pre, v, ans, vis;
	vector<pii> p;
	vector<vector<pii>> mp1, mp2;
	void init1_(int _n, int _m) {
		n = _n, m = _m;
		timestamp = 0, ii = 0, bccid = 0;
		es.clear(), id.clear();
		bcc.clear();
		L.assign(n + 1, 0);
		D.assign(n + 1, 0);
		bcc.assign(n + 1, 0);
		pre.assign(n + 1, 0);
		v.assign(n + 1, 0);
		ans.assign(m + 1, 0);
		mp1.assign(n + 1, vector<pii>());
		mp2.assign(n + 1, vector<pii>());
		vis.assign(n + 1, 0);
	}
	void init2_(int _k) {
		k = _k;
		p.assign(k + 1, {0, 0});
	}
	void add_edge1(int a, int b, int ii) {
		int cur = es.size();
		mp1[a].push_back({cur, 1});
		mp1[b].push_back({cur, -1});
		es.push_back(a ^ b);
		id.push_back(ii);
	
	}
	void add_edge2(int a, int b, int ii) {
		int cur = es.size();
		mp2[a].push_back({cur, 1});
		mp2[b].push_back({cur, -1});
		es.push_back(a ^ b);
		id.push_back(ii);
	
	}
	void dfs1(int x, int par) {
		L[x] = D[x] = ++timestamp;
		for(auto i : mp1[x]) if(i.first != par) {
			int to = es[i.first] ^ x;
			if(!D[to]) {
				pre[ii++] = to;
				dfs1(to, i.first);
				L[x] = min(L[x], L[to]);
			}
			else L[x] = min(L[x], D[to]);
			if(L[to] > D[x]) {
				bccid ++;
				while(pre[ii] != to) {
					ii --, bcc[pre[ii]] = bccid;
				}
			}
		}
	}
	void dfs2(int x, int par) {
		vis[x] = 1;
		for(auto i : mp2[x]) if(i.first != par) {
			int to = es[i.first] ^ x;
			dfs2(to, i.first);
			v[x] += v[to];
			if(v[to] > 0) ans[id[i.first]] = 1 * i.second;
			else if(v[to] < 0) ans[id[i.first]] = -1 * i.second;
		}
		return;
	}
	void solve() {
		rep(i, 1, n) if(!D[i]) {
			pre[ii++] = i, dfs1(i, -1);
			if(ii == 0) continue;
			bccid ++;
			while(pre[ii] != i) ii--, bcc[pre[ii]] = bccid;
		}
		
		rep(i, 1, n) for(auto j : mp1[i]) {
			int cur = j.first;
			if(bcc[i] == bcc[es[cur] ^ i] || j.second < 0) continue;
			add_edge2(bcc[i], bcc[es[cur] ^ i], id[cur]);
		}
		rep(i, 1, k) {
			int a = p[i].first, b = p[i].second;
			v[bcc[a]] += i;
			v[bcc[b]] -= i;
		}
		rep(i, 1, bccid) if(!vis[i]) dfs2(i, -1);
		rep(i, 1, m) {
			if(ans[i] == 0) cout << "B";
			else if(ans[i] == 1) cout << "L";
			else cout << "R";
		}
		cout << "\n";
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init1_(n, m);
	rep(i, 1, m) {
		int a, b; cin >> a >> b;
		add_edge1(a, b, i);
	}
	int k; cin >> k;
	init2_(k);
	rep(i, 1, k) 
		cin >> p[i].first >> p[i].second;
	solve();
	return 0;
} 

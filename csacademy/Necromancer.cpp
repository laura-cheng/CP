#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

using namespace std;
using namespace __gnu_pbds;

#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl;} 
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace Dinic {
	int n, s, t;
	const int INF = 1000000000;
	struct edge {
		int to, cap, rev;
	};
	vector<vector<edge>>mp;
	vector<int> level, iter;
	void init_(int _n, int _s, int _t) {
		n = _n, s = _s, t = _t;
		mp.assign(n + 1, vector<edge>());
		level.assign(n + 1, INF);
		iter.assign(n + 1, 0);
	}
	void add_edge(int a, int b, int c) {
		mp[a].push_back({b, c, signed(mp[b].size())});
		mp[b].push_back({a, 0, signed(mp[a].size()) - 1});
	}
	bool bfs() {
		level.assign(n + 1, INF);
		iter.assign(n + 1, 0);
		queue<int> q;
		level[s] = 0, q.push(s);
		while(q.size()) {
			int cur = q.front(); q.pop();
			for(auto i : mp[cur]) {
				if(level[i.to] != INF || i.cap <= 0) continue;
				level[i.to] = level[cur] + 1;
				q.push(i.to);
			}
		}		
		return (level[t] != INF);
	}
	int dfs(int s, int flow) {
		if(s == t) return flow;
		for(int &i = iter[s]; i < mp[s].size(); i++) {
			edge &e = mp[s][i];
			if(level[s] + 1 != level[e.to] || e.cap <= 0) continue;
			int cur = dfs(e.to, min(flow, e.cap));
			if(cur) {
				e.cap -= cur;
				mp[e.to][e.rev].cap += cur;
				return cur;
			}
		}
		return 0;
	}
	int flow() {
		int ans = 0;
		while(bfs()) {
			int res = 0;
			while(res = dfs(s, INF), res) 
				ans += res;
		}
		return ans;
	}
};
namespace solver {
	int n, k;
	vector<vector<bool>> valid;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		valid.assign(n + 1, vector<bool>(k + 1, 1));
	}
	int check(int x) {
		Dinic::init_(1 + n + k, 1, 1 + n + k);
		rep(i, 1, n) if(!valid[i][1]) {
			rep(j, 2, k) if(valid[i][j]) {
				Dinic::add_edge(i + 1, n + j, 1);
			}
		}
		rep(i, 1, n) Dinic::add_edge(1, i + 1, 1);
		rep(i, 2, k) Dinic::add_edge(i + n, n + k + 1, x);
		return Dinic::flow();
	}
	int solve() {
		int l = -1, r = n, cnt = 0;
		rep(i, 1, n) cnt += valid[i][1];
		while(r - l > 1) {
			int mid = (l + r) / 2;
			if(check(mid) + cnt >= n) r = mid;
			else l = mid;
		}
		return max(0, r - cnt + 1);
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	init_(n, k);
	rep(i, 1, n) {
		int x, y; cin >> x;
		rep(j, 1, x) {
			cin >> y;
			if(j != 1) valid[i][y] = 0;
		}
	}
	cout << solve() << "\n";
	return 0;
}

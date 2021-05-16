#define wiwihorz
#include <bits/stdc++.h> 
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i  = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1)/ (b))

#define MOD 1000000007
#define MAXN 1000005
#define INF 1000000000000000000ll
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_eince_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) out("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void out() {cerr << endl;}
template<class T1, class ... T2> void out(T1 a, T2 ... e) {cerr << a << " ", out(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif

using namespace std;
struct es {
	int f, t, cost;
	bool operator<(es b) {
		return cost < b.cost;
	}
};
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
int n, m, q;
vector<es> a;
int solve(int u, int v, int cost) {
	Dinic mn, mx;
	mn.init(n, u, v);
	mx.init(n, u, v);
	for(auto i : a) {
		if(i.cost < cost) {
			mn.add_edge(i.f, i.t, 1);
			mn.add_edge(i.t, i.f, 1);
		}
		if(i.cost > cost) {
			mx.add_edge(i.f, i.t, 1);
			mx.add_edge(i.t, i.f, 1);
		}
	}
	return mn.flow() + mx.flow();
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m) {
		int x, y, z;
		cin >> x >> y >> z;
		a.push_back({x, y, z});
	}
	cin >> q, sort(all(a));
	while(q--) {
		int x, y, z;
		cin >> x >> y >> z;
		cout << solve(x, y, z) << "\n";
	}
	return 0;
} 

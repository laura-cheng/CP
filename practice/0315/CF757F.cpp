#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loo-opt(on)

#define rep(i ,a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MAXN 1000005
#define MOD 1000000007
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {
	while(L < R) cerr << *L << " \n"[next(L) == R], ++L;
}
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct AC {
	int n, lg, s;
	struct edge {
		int to, cost;
	};
	vector<vector<edge>> a;
	vector<vector<int>> b, ac, c, mp;
	vector<int> d, sz;
	void init_(int _n, int _s) {
		n = _n, s = _s;
		lg = 31 - __builtin_clz(n);
		a.assign(n + 1, vector<edge>());
		b.assign(n + 1, vector<int> ());
		c.assign(n + 1, vector<int> ());
		mp.assign(n + 1, vector<int>());
		ac.assign(lg + 1, vector<int>(n + 1, 0));
		d.assign(n + 1, 0);
		sz.assign(n + 1, 0);
	}
	void dijkstra(int s) {
		vector<int> dis(n + 1, INF);
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		dis[s] = 0; pq.push({0, s});
		while(pq.size()) {
			pii p = pq.top(); pq.pop();
			if(dis[p.second] != p.first) continue;
			int cur = p.second;
			for(auto i : a[cur]) {
				int v = i.cost + dis[cur];
				if(dis[i.to] > v) {
					dis[i.to] = v;
					pq.push({v, i.to});
				}
			} 
		} 
		rep(i, 1, n) {
			if(dis[i] == INF) continue;
			for(auto j : a[i]) {
				if(dis[i] + j.cost == dis[j.to]) {
					b[i].push_back(j.to);
					c[j.to].push_back(i);
				}
			}
		}
		return; 
	}
	int LCA(int a, int b) {
		if(d[a] < d[b]) swap(a, b);
		int need = d[a] - d[b];
		rrep(i, 0, lg) {
			if((need >> i) & 1) a = ac[i][a];
		}
		if(a == b) return a;
		rrep(i, 0, lg) {
			if(ac[i][a] != ac[i][b]) {
				a = ac[i][a];
				b = ac[i][b];
			}
		}
		return ac[0][a];
	}
	void build() {
		vector<int> deg(n + 1, 0);
		rep(i, 1, n) for(auto j : b[i]) {
			deg[j] ++;
		}
		queue<int>q;
		q.push(s);
		while(q.size()) {
			int cur = q.front(); q.pop();
			int lca = c[cur].size() ? c[cur][0] : cur;
			for(auto i : c[cur]) {
				lca = LCA(i, lca);
			}
			mp[lca].push_back(cur);
			d[cur] = d[lca] + 1;
			ac[0][cur] = lca;
			rep(i, 1, lg) {
				ac[i][cur] = ac[i - 1][ac[i - 1][cur]]; 
			}
			for(auto i : b[cur]) {
				deg[i] --;
				if(!deg[i]) q.push(i);
			}
		}	
	} 
	void dfs(int x, int par) {
		sz[x] = 1;
		for(auto i : mp[x]) {
			if(i == par) continue;
			dfs(i, x);
			sz[x] += sz[i];
		}
		return;
	}
 	int solve() {
 		dijkstra(s);
 		build();
 		dfs(s, s);
 		int ans = 0;
 		rep(i, 1, n) if(i != s) {
 			ans = max(ans, sz[i]);
 		}
 		return ans;
 	}
} ac;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, s; 
	cin >> n >> m >> s;
	ac.init_(n, s);
	rep(i, 1, m) {
		int x, y, z;
		cin >> x >> y >> z;
		ac.a[x].push_back({y, z});
		ac.a[y].push_back({x, z});
	}
	cout << ac.solve() << "\n";
	return 0;
}

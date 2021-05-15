#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b;i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

using namespace std;
using namespace __gnu_pbds;

#define ll long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, sx, sy, ex, ey, tot;
	struct rec {
		int l, r, u, d, id;
	};
	vector<rec> r;
	vector<vector<int>> mp;
	vector<vector<pii>> row, col;
	vector<int> vx, vy, es;
	vector<ll> cost;
	void init_(int _n) {
		n = _n + 10, tot = 2 * n + 1;
		r.clear(), es.clear();
		cost.clear(), vx.clear();
		vy.clear(), r.clear();
		row.assign(tot + 1, vector<pii>());
		col.assign(tot + 1, vector<pii>());
		mp.assign(tot * tot + 1, vector<int>());
	}
	int get(int x, int y) {
		return (x - 1) * tot + y; 
	}
	void add_edge(int a, int b, ll c) {
//		int xa = vx[a / tot], ya = vy[a % tot - 1]; 
//		int xb = vx[b / tot], yb = vy[b % tot - 1]; 
//		print(xa, ya, xb, yb);	
		mp[a].push_back(es.size());
		mp[b].push_back(es.size());
		es.push_back(a ^ b);
		cost.push_back(c);
	}
	void add_rec(int l, int rr, int u, int d, int id) {
		r.push_back({l, rr, u, d, id});
		vx.push_back(l), vx.push_back(rr);
		vy.push_back(u), vy.push_back(d);
	}
	void build() {
		sort(all(vx)), vx.resize(unique(all(vx)) - vx.begin());
		sort(all(vy)), vy.resize(unique(all(vy)) - vy.begin());
		sx = lower_bound(vx.begin(), vx.end(), sx) - vx.begin() + 1;
		sy = lower_bound(vy.begin(), vy.end(), sy) - vy.begin() + 1;
		ex = lower_bound(vx.begin(), vx.end(), ex) - vx.begin() + 1;
		ey = lower_bound(vy.begin(), vy.end(), ey) - vy.begin() + 1;
		for(auto &i : r) {
			i.l = lower_bound(vx.begin(), vx.end(), i.l) - vx.begin() + 1;
			i.r = lower_bound(vx.begin(), vx.end(), i.r) - vx.begin() + 1;
			i.u = lower_bound(vy.begin(), vy.end(), i.u) - vy.begin() + 1;
			i.d = lower_bound(vy.begin(), vy.end(), i.d) - vy.begin() + 1;
			rep(j, i.l, i.r) {
				col[j].push_back({i.u, i.id});
				col[j].push_back({i.d, i.id});
				if(j != i.l) {
					add_edge(get(j, i.u), get(j - 1, i.u), (ll)(vx[j - 1] - vx[j - 2]));
					add_edge(get(j, i.d), get(j - 1, i.d), (ll)(vx[j - 1] - vx[j - 2]));
				}
			}
			rep(j, i.u, i.d) {
				row[j].push_back({i.l, i.id});
				row[j].push_back({i.r, i.id});
				if(j != i.u) {
					add_edge(get(i.l, j), get(i.l, j - 1), (ll)(vy[j - 1] - vy[j - 2]));
					add_edge(get(i.r, j), get(i.r, j - 1), (ll)(vy[j - 1] - vy[j - 2]));
				}
			}		
		}
		rep(i, 1, tot) {
			sort(all(row[i])), sort(all(col[i]));
			rep(j, 1, signed(row[i].size()) - 1) {
				if(row[i][j].second == row[i][j - 1].second) continue;
				int x = row[i][j].first, x1 = row[i][j - 1].first;
				add_edge(get(x, i), get(x1, i), (ll)(vx[x - 1] - vx[x1 - 1]));
			}
			rep(j, 1, signed(col[i].size()) - 1) {
				if(col[i][j].second == col[i][j - 1].second) continue;
				int y = col[i][j].first, y1 = col[i][j - 1].first;
				add_edge(get(i, y), get(i, y1), (ll)(vy[y - 1] - vy[y1 - 1]));
			}
		}
		row.clear();
		col.clear();
		vx.clear();
		vy.clear();
	}
	void solve() {
		vector<ll> dis(tot * tot + 1, INF);
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		pq.push({0, get(sx, sy)}), dis[get(sx, sy)] = 0;
		while(pq.size()) {
			pii p = pq.top(); pq.pop();
			if(dis[p.second] != p.first) continue;
			int cur = p.second;
			for(auto i : mp[cur]) {
				int to = es[i] ^ cur;
				ll v = dis[cur] + cost[i];
				if(v < dis[to]) {
					dis[to] = v;
					pq.push({v, to});
				}
			}
		}	
		if(dis[get(ex, ey)] == INF) cout << "No Path\n";
		else cout << dis[get(ex, ey)] << "\n";
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		cin >> sx >> sy;
		cin >> ex >> ey;
		int n; cin >> n;
		init_(n);
		rep(i, 1, n) {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			add_rec(min(a, c), max(a, c),
				min(b, d), max(b, d), i);
		}
		add_rec(sx, sx, sy, sy, n + 1);
		add_rec(ex, ex, ey, ey, n + 2);
		build();
		solve();
	}
	return 0;
}


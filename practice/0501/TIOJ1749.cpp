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

#define int long long int
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
#define x first
#define y second
namespace solver {
	int n, ii, sx, sy, ex, ey;
	struct edge {
		int to, cost;
	};
	struct pt {
		int x, id, tp;
		bool operator<(pt b) {
			if(tp != b.tp) return tp < b.tp;
			else return x < b.x;
		}
	};
	struct ln {
		int x, L, R, id;
		bool operator<(ln b) {
			return x < b.x;
		}
	}; 
	struct rec {
		int u, d, l, r;
	};
	vector<vector<pt>> p[2];
	vector<rec> r;
	vector<ln> a[2];
	vector<int> dis;
	vector<vector<edge>> mp;
	void init_(int _n) {
		n = _n, ii = 2;
		rep(i, 0, 1) {
			p[i].assign(n + 1, vector<pt>());
			a[i].clear();
		}
		r.assign(n + 1, {0, 0, 0, 0});
		dis.assign(20 * n + 1, INF);		
		mp.assign(20 * n + 1, vector<edge>());
	}
	void add_rec(int u, int d, int l, int rr, int id) {
		r[id] = {u, d, l, rr};
		a[0].push_back({l, u, d, id});
		a[0].push_back({rr, u, d, id});
		a[1].push_back({u, l, rr, id});
		a[1].push_back({d, l, rr, id});

		return;
	}
	void add_edge(int a, int b, int c) {
		mp[a].push_back({b, c});
		mp[b].push_back({a, c});
	}
	void proc(int id) {
		map<int, pii> map;
		for(auto i : a[id]) {
			print(i.x, i.L, i.R, ii);
			auto it = map.upper_bound(i.L);
			auto it1 = map.upper_bound(i.R);
			if(it != map.begin()) {
			 	it = prev(it); 
				int a = ++ii, b = ++ii;
				pii cur = it -> second;
				print(cur.second, i.x, i.L);
				p[id][i.id].push_back({i.L, a, 0});
				p[id][cur.first].push_back({i.L, b, 1});
				add_edge(a, b, abs(cur.second - i.x));
			}
			if(it != it1) for(it; next(it) != it1;) {
				auto temp = it;
				it = next(it);
				map.erase(temp);
			}
			if(it != map.end()) {
				int a = ++ii, b = ++ii;
				pii cur = it -> second;
				print(cur.second, i.x, i.R);
				p[id][i.id].push_back({i.R, a, 0});
				p[id][cur.first].push_back({i.R, b, 1});
				add_edge(a, b, abs(cur.second - i.x));
				map.erase(it);
			}
			map[i.L] = {i.id, i.x};
			if(next(map.find(i.L)) == map.end()) map[i.R + 1] = {0, -INF};
		}
	}
	void build() {
		sort(all(a[0])), proc(0);
		sort(all(a[1])), reverse(all(a[1])), proc(1);
		int sa = 0, sb = 0, ea = 0, eb = 0;
		rep(i, 1, n) {
			if(r[i].l <= sx && r[i].r >= sx) {
				if(r[i].u >= sy) sa = (sa && r[sa].u < r[i].u ? sa : i);
				if(r[i].d <= sy) sb = (sb && r[sb].d > r[i].d ? sb : i);
			}
			if(r[i].l <= ex && r[i].r >= ex) {
				if(r[i].u >= ey) ea = (ea && r[ea].u < r[i].u ? ea : i);
				if(r[i].d <= ey) eb = (eb && r[eb].d > r[i].d ? eb : i);
			}
		}
		p[0][sa].push_back({sx, ++ii, 0});
		add_edge(1, ii, abs(r[sa].u - sy));
		
		p[0][sb].push_back({sx, ++ii, 1});
		add_edge(1, ii, abs(r[sb].d - sy));
		
		p[0][ea].push_back({sx, ++ii, 0});
		add_edge(2, ii, abs(r[ea].u - sy));
		
		p[0][eb].push_back({sx, ++ii, 0});
		add_edge(2, ii, abs(r[eb].d - sy));
		
		sa = sb = ea = eb = 0;
		rep(i, 1, n) {
			if(r[i].u <= sy && r[i].d >= sy) {
				if(r[i].l >= sx) sa = (sa && r[sa].l < r[i].l ? sa : i);
				if(r[i].r <= sx) sb = (sb && r[sb].r > r[i].r ? sb : i);
			}
			if(r[i].u <= ey && r[i].d >= ey) {
				if(r[i].l >= ex) ea = (ea && r[ea].l < r[i].l ? ea : i);
				if(r[i].r <= ex) eb = (eb && r[eb].r > r[i].r ? eb : i);
			}
		}
		p[1][sa].push_back({sy, ++ii, 0});
		add_edge(1, ii, abs(r[sa].u - sx));
		
		p[1][sb].push_back({sy, ++ii, 1});
		add_edge(1, ii, abs(r[sb].d - sx));
		
		p[1][ea].push_back({sy, ++ii, 0});
		add_edge(2, ii, abs(r[ea].u - sx));
		
		p[1][eb].push_back({sy, ++ii, 0});
		add_edge(2, ii, abs(r[eb].d - sx));
		rep(i, 1, n) {
			sort(all(p[0][i]));
			sort(all(p[1][i]));
			vector<pt> es;
			rep(j, 0, 1) {
				es.push_back({p[j][i][0]});
				rep(k, 0, signed(p[j][i].size()) - 2) {
					pt a = p[j][i][k], b = p[j][i][k + 1];
					if(b.tp == 1) {
						es.push_back({p[j][i][k]});
						break;
					}
					add_edge(a.id, b.id, abs(a.x - b.x));
				}
			}
			reverse(all(p[0][i]));
			reverse(all(p[1][i]));
			rep(j, 0, 1) {
				es.push_back({p[j][i][0]});
				rep(k, 0, signed(p[j][i].size()) - 2) {
					pt a = p[j][i][k], b = p[j][i][k + 1];
					if(b.tp == 0) {
						es.push_back({p[j][i][k]});
						break;
					}
					add_edge(a.id, b.id, abs(a.x - b.x));
				}
			}
			assert(es.size() == 8);
			add_edge(es[1].id, es[2].id, 0);
			add_edge(es[3].id, es[4].id, 0);
			add_edge(es[5].id, es[6].id, 0);
			add_edge(es[7].id, es[0].id, 0);
		}
		return;
	}
	int solve() {
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		dis[1] = 0, pq.push({0, 1});
		while(pq.size()) {
			pii cur = pq.top(); pq.pop();
			if(cur.first == dis[cur.second]) continue;
			int x = cur.second;
			for(auto i : mp[x]) {
				int v = i.cost + dis[x];
				if(v < dis[i.to]) {
					dis[i.to] = v;
					pq.push({v, i.to});	
				}
			}
		}	
		if(dis[2] == INF) return -1;
		return dis[2];
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		cin >> sx >> sy >> ex >> ey;
		int n; cin >> n;
		init_(n);
		
		rep(i, 1, n) {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			add_rec(min(b, d), max(b, d), 
				min(a, c), max(a, c), i);
		}print("done");
		build();
		cout << solve() << "\n";
	}
	return 0;
}


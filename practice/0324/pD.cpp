#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random t19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {
	while(L < R) cerr << *L << " \n"[next(L) == R], ++L;
}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct LCA {
	int n, lg;
	struct edge {
		int u, v, w, a, b, p;
	};
	vector<vector<int>> mp;
	vector<vector<int>>ac, up[60], down[60];
	vector<int> d;
	vector<edge> train; 
	void init_(int _n) {
		n = _n, lg = 31 - __builtin_clz(n);
		mp.assign(n + 1, vector<int>());
		ac.assign(lg + 1, vector<int>(n + 1, 0));
		rep(i, 0, 59) {
			up[i].assign(lg + 1, vector<int>(n + 1, 0));
			down[i].assign(lg + 1, vector<int>(n + 1, 0));
		}
		d.assign(n + 1, 0);
		train.clear();
		return;
	}
	void dfs(int x, int par, int dd = 0) {
		d[x] = dd, ac[0][x] = par;
		for(auto i : mp[x]) {
			if(i == par) continue;
			dfs(i, x, dd + 1);
		}
	}
	void build() {
		dfs(1, 1);
		for(auto i : train) {
			if(d[i.u] > d[i.v]) {
				rep(j, 0, 59) {
					up[j][0][i.u] = 1 + ((i.a - j) % i.p + i.p) % i.p + i.w; 
					down[j][0][i.u] = 1 + ((i.b - j) % i.p + i.p) % i.p + i.w;
				}
			}
			else {
				rep(j, 0, 59) {
					down[j][0][i.v] = 1 + ((i.a - j) % i.p + i.p) % i.p + i.w; 
					up[j][0][i.v] = 1 + ((i.b - j) % i.p + i.p) % i.p + i.w;
				}
			}
			
		}
		rep(i, 1, lg) rep(j, 1, n) {
			ac[i][j] = ac[i - 1][ac[i - 1][j]];
		}
		rep(j, 1, lg) rep(i, 0, 59) rep(k, 1, n)  {
			int x = up[i][j - 1][k];
			int y = down[i][j - 1][ac[j - 1][k]];
			up[i][j][k] = x + up[(i + x) % 60][j - 1][ac[j - 1][k]];
			down[i][j][k] = y + down[(i + y) % 60][j - 1][k];
		}
		return;
	}
	int get_LCA(int a, int b) {
		if(d[a] < d[b]) swap(a, b);
		int need = d[a] - d[b];
		rep(i, 0, lg) if((need >> i) & 1) {
			a = ac[i][a];
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
	int query(int a, int b, int t) {
		int lca = get_LCA(a, b);
		int ans = 0, need, aa = a, ans1 = 0;
		need = d[a] - d[lca];
		rrep(i, 0, lg) if((need >> i) & 1){
			ans += up[t][i][a];
			t = (up[t][i][a] + t) % 60;
			a = ac[i][a];
		}
		need = d[b] - d[lca];
		

		int cur = b;
		vector<int> p(lg + 1, 0);
		rep(i, 0, lg) if((need >> i) & 1) {
			p[i] = cur;
			cur = ac[i][cur];
		}
		rrep(i, 0, lg) if((need >> i) & 1){
			ans += down[t % 60][i][p[i]];
			t = (down[t % 60][i][p[i]] + t) % 60;
		}

		return ans - 1;
	}
} ;
namespace SOLVE {
	int n;
	LCA lca;
	void init_(int _n) {n = _n; lca.init_(n);}
	void add_edge(int u, int v, int w, int a, int b, int p) {
		lca.train.push_back({u, v, w, a, b, p});
		lca.mp[u].push_back(v);
		lca.mp[v].push_back(u);
		return;
	}
	void build() {lca.build();}
 	int query(int h, int m, int s, int t) {
 		return lca.query(s, t, m);
 	}
};
using namespace SOLVE;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q; cin >> n >> q;
	init_(n);
	rep(i, 1, n - 1) {
		int u, v, w, a, b, p;
		cin >> u >> v >> w >> a >> b >> p;
		add_edge(u, v, w, a, b, p);
	}
	build();
	rep(i, 1, q) {
		int h, m, s, t;
		cin >> h >> m >> s >> t;
		cout << query(h, m, s, t) << "\n";
	}
	
	return 0;
}



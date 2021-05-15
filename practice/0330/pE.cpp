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
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct LCA {
	vector<vector<int>> mp, ac;
	vector<int> d;
	int n, lg;
	void init_(int _n) {
		n = _n, lg = 31 - __builtin_clz(n);
		mp.assign(n + 1, vector<int>());
		ac.assign(lg + 1, vector<int>(n + 1, 0));
		d.assign(n + 1, 0);
		return;
	}
	void build() {
		dfs(1, 1);
		rep(i, 1, lg) rep(j, 1, n) {
			ac[i][j] = ac[i - 1][ac[i - 1][j]];
		}
		return;
	}
	void dfs(int x, int par, int dd = 0) {
		ac[0][x] = par, d[x] = dd;
		for(auto i : mp[x]) {
			if(par == i) continue;
			dfs(i, x, dd + 1);
		}
 	}
	int lca(int a, int b) {
		if(d[a] < d[b]) swap(a, b);
		int need = d[a] - d[b];
		rep(i, 0, lg) if((need >> i) & 1) {
			a = ac[i][a];
		}
		if(a == b) return a;
		rrep(i, 0, lg) if(ac[i][a] != ac[i][b]) {
			a = ac[i][a];
			b = ac[i][b];
		}
		return ac[0][a];
	}
	bool query(vector<int> a) {
		int x = 0;
		for(auto i : a) if(d[x] < d[i]) {
			x = i;
		}
		for(auto i : a) {
			i = ac[0][i];
			if(lca(i, x) != i) return 0;
		}
		return 1;
	}
 
} lca;

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	lca.init_(n);
	rep(i, 1, n - 1) {
		int x, y; cin >> x >> y;
		lca.mp[x].push_back(y);
		lca.mp[y].push_back(x);
	}	
	lca.build();
	rep(i, 1, m) {
		int k; cin >> k;
		vector<int> a(k, 0);
		rep(j, 0, k - 1) cin >> a[j];
		if(lca.query(a)) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}

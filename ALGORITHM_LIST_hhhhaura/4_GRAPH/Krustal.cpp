#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define MAXN 1000005
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {cerr << a << " ", kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
int n, m;
struct edge {
	int u, v, cost;
	bool operator<(edge b) {
		return cost < b.cost;
	}
};
vector<edge> es;
struct DSU {
	int n;
	vector<int> par, rk;
	void init(int _n) {
		n = _n;
		par.assign(n + 1, 0);
		rk.assign(n + 1, 0);
		rep(i, 1, n) par[i] = i;
		return;
	} 
	int find_par(int a) {
		if(par[par[a]] == par[a]) return par[a];
		else return par[a] = find_par(par[a]);
	}
	bool same(int a, int b) {
		return find_par(a) == find_par(b);
	}
	void unite(int a, int b) {
		int aa = find_par(a), bb = find_par(b);
		if(aa == bb) return;
		if(rk[aa] > rk[bb]) par[bb] = aa;
		else if(rk[bb] > rk[aa]) par[aa] = bb;
		else par[bb] = aa, rk[aa] ++;
	}
}dsu;
int krustal() {
	dsu.init(n);
	sort(all(es));
	int ans = 0;
	for(auto i : es) {
		if(!dsu.same(i.u, i.v)) {
			ans += i.cost;
			dsu.unite(i.u, i.v);
		}
	}
	rep(i, 1, n) {
		if(dsu.find_par(i) 
			!= dsu.find_par(1)) return -1;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	while(cin >> n >> m) {
		es.clear();
		rep(i, 1, m) {
			int x, y, z;
			cin >> x >> y >> z;
			x ++, y ++;
			es.push_back({x, y, z});
		}
		cout << krustal() << "\n";
	}
	return 0;
}


#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define MAXN 1000005
#define MOD 1000000007
#define INF 1000000000000000000
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) out("[" + string(#a) +"] = ", a)
void vprint(auto L, auto R) {while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void out() {cerr << endl;}
template<class T1, class ... T2> void out(T1 a, T2 ... e) {cerr << a <<" ", out(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
int n, m, q, x, y;
struct DSU {
	int n;
	vector<int> par, rk;
	void init_(int n) {
		par.assign(n + 1, 0);
		rk.assign(n + 1, 0);
		rep(i, 1, n) par[i] = i;
	}
	int find_par(int x) {
		if(par[par[x]] == par[x]) return par[x];
		else return par[x] = find_par(par[x]);
	}
	void unite(int a, int b) {
		int aa = find_par(a), bb = find_par(b);
		if(aa == bb) return;
		if(rk[aa] > rk[bb]) par[bb] = aa;
		else if(rk[bb] > rk[aa]) par[aa] = bb;
		else par[bb] = aa, rk[aa] ++;
		return;
	}
	bool same(int a, int b) {
		return find_par(a) == find_par(b);
	}
}dsu;

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m >> q;
	dsu.init_(n);
	rep(i, 1, m) {
		cin >> x >> y;
		dsu.unite(x, y);
	}
	rep(i, 1, q) {
		cin >> x >> y;
		if(dsu.same(x, y)) cout << ":)\n";
		else cout << ":(\n";
	}
	return 0;
}  

#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 10000000000000000000
#define MOD 1000000007
#define MAXN 1000005
#define eps (1e-9)

//#define int long long int
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
struct DSU {
	int n, op;
	vector<int> par, sz;
	stack<pair<int*, int>> stack_par, stack_sz;
	void init_(int _n) {
		n = _n, op = 0;
		par.assign(n + 1, 0);
		sz.assign(n + 1, 1);
		rep(i, 1, n) par[i] = i;
		while(stack_par.size()) stack_par.pop();
		while(stack_sz.size()) stack_sz.pop();
	}
	int find_par(int a) {
		while(par[a] != a) a = par[a];
		return a;
	}
	void unite(int a, int b) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return;
		op ++;
		if(sz[bb] > sz[aa]) swap(aa, bb);
		stack_par.push({&par[bb], par[bb]});
		stack_sz.push({&sz[aa], sz[aa]});
		sz[aa] += sz[bb], par[bb] = aa;
		return;
	}
	void undo() {
		assert(op); op--;
		pair<int*, int> aa, bb;
		aa = stack_par.top(); stack_par.pop();
		bb = stack_sz.top(); stack_sz.pop();
		*aa.first = aa.second;
		*bb.first = bb.second;
	}
	bool same(int a, int b) {
		return find_par(a) == find_par(b);
	}
};
struct AC {
	int n, bccid, ii, timestamp;
	vector<vector<int>> a, mp, bcc;
	vector<int> L, D, pre, es, x, y;
	DSU dsu;
	void init_(int _n) {
		n = _n, bccid = 0;
		ii = timestamp = 0;
		a.assign(n + 1, vector<int>(n + 1, 0));
		mp.assign(n + 1, vector<int>());
		bcc.assign(1, vector<int>());
		L.assign(n + 1, 0);
		D.assign(n + 1, 0);
		pre.assign(n * n + 1, 0);
		es.clear();
		x.clear();
		y.clear();
	}
	void build() {
		rep(i, 1, n) rep(j, i + 1, n) {
			if(a[i][j] == 0) {
				add_edge(i, j);
			}
		}
	}
	void add_edge(int a, int b) {
		mp[a].push_back(es.size());
		mp[b].push_back(es.size());
		es.push_back(a ^ b);
		x.push_back(a);
		y.push_back(b);
		return;
	}
	void dfs(int x, int par) {
		L[x] = D[x] = ++timestamp;
		for(auto i : mp[x]) {
			if(i == par) continue;
			int to = es[i] ^ x;
			if(!D[to]) {
				pre[ii++] = i;
				dfs(to, i);
				L[x] = min(L[x], L[to]);
				if(D[x] <= L[to]) {
					bccid ++;
					bcc.push_back(vector<int>());
					while(pre[ii] != i) {
						ii --, bcc[bccid].push_back(pre[ii]);
					}
				}
			}
			else if(D[to] < D[x]) {
				pre[ii++] = i;
				L[x] = min(L[x], D[to]);	
			}
		}
	}
	int solve() {
		build();
		rep(i, 1, n) if(!D[i]) {
			dfs(i, -1);
		}
		dsu.init_(2 * n);
		vector<int> yes(n + 1, 0);
		rep(i, 1, bccid) {
			int cur = 0;
			for(auto j : bcc[i]) {
				dsu.unite(x[j], y[j] + n);
				dsu.unite(x[j] + n, y[j]);
				if(dsu.same(x[j], y[j])) cur = 1;
			}
			if(cur) for(auto j : bcc[i]) {
				yes[x[j]] = 1, yes[y[j]] = 1;
			}
			while(dsu.op) dsu.undo();
		}
		int ans = 0;
		rep(i, 1, n) ans += yes[i];
		return n - ans;
	}
} ac;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; 
	while(cin >> n >> m && (n || m)) {
		ac.init_(n);
		rep(i, 1, m) {
			int a, b; cin >> a >> b;
			ac.a[a][b] = ac.a[b][a] = 1;
		}
		cout << ac.solve() << "\n";
	}
	
	return 0;
}

#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define MAXN 1000005
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
struct DSU {
	int n, cnt, op;
	vector<int> par, sz;
	stack<pair<int *, int>> stack_par, stack_sz;
	void init_(int _n) {
		n = _n, cnt = n, op = 0;
		par.assign(n + 1, 0);
		sz.assign(n + 1, 1);
		rep(i, 1, n) par[i] = i;
	}
	int find_par(int a) {
		while(par[a] != a) a = par[a];
		return a;
	}
	void unite(int a, int b) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return ;
		
		op ++, cnt --;
		if(sz[aa] < sz[bb]) swap(aa, bb);
		stack_par.push({&par[bb], par[bb]});
		stack_sz.push({&sz[aa], sz[aa]});
		par[bb] = aa, sz[aa] += sz[bb];
		return;		
	}
	void undo() {
		if(!op) return;
		pair<int*, int> aa, bb;
		aa = stack_par.top(); stack_par.pop();
 		bb = stack_sz.top(); stack_sz.pop();
 		*aa.first = aa.second;
 		*bb.first = bb.second;
 		op--, cnt++;
 		return;
	}
};
struct MO {
	struct seg {
		int L, R, id;
		bool operator<(seg b) {
			return R < b.R;
		}
	};
	struct es {
		int u, v;
	};
	int n, m, q, bk, sz;
	vector<vector<seg>> a;
	vector<int> ans, pre;
	vector<es> b;
	DSU dsu;
	void init_(int _n, int _m, int _q) {
		n = _n, sz = pow(_m, 0.5) + 1;
		bk = ceil(_m, sz);
		m = _m, q = _q;
		a.assign(bk + 1, vector<seg>());
		dsu.init_(n);
		ans.assign(q + 1, 0);
		b.assign(m + 1, {0, 0});
		pre.assign(m + 1, 0);
	}
	void add(int L, int R, int id) {
		int x = ceil(L, sz);
		a[x].push_back({L, R, id});
	}
	void build() {
		rep(i, 1, m) {
			dsu.unite(b[i].u, b[i].v);
			pre[i] = dsu.cnt;
		}
		while(dsu.op) dsu.undo();
		return;
	}
	void solve() {
		rep(i, 1, bk) {
			sort(all(a[i]));
			int r = i * sz;
			for(auto j : a[i]) {
				if(j.R <= i * sz) {
					int cur = dsu.op;
					rep(k, j.L, j.R) dsu.unite(b[k].u, b[k].v);
					ans[j.id] = dsu.cnt - pre[j.R];
					while(dsu.op != cur) dsu.undo();
				}
				else {
					
					while(r < j.R) r++, dsu.unite(b[r].u, b[r].v);
					int cur = dsu.op;
					rrep(k, j.L, i * sz) {
						dsu.unite(b[k].u, b[k].v);
					}
					ans[j.id] = dsu.cnt - pre[j.R];
					while(cur != dsu.op) dsu.undo();
				}
			}
			while(dsu.op) dsu.undo();
		}
		return;
	}
} mo;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, q; cin >> n >> m >> q;
	mo.init_(n, m, q);
	rep(i, 1, m) {
		int a, b; cin >> a >> b;
		mo.b[i] = {a, b};
	}
	rep(i, 1, q) {
		int a, b; cin >> a >> b;
		mo.add(a, b, i);
	}
	mo.build();
	mo.solve();
	rep(i, 1, q) {
		cout << mo.ans[i] << "\n";
	}
	
	return 0;
} 

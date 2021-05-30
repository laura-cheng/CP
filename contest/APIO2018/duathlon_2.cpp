#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i ,a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)

using namespace std;
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().times_since_epoch().count())

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, ans = 0 ;
	vector<vector<int>> mp;
	vector<int> dp1, sz, w, vis;
	void init_(int _n, vector<vector<int>> _mp, vector<int> _w) {
		n = _n, ans = 0;
		dp1.assign(n + 1, 0);
		sz.assign(n + 1, 0);
		vis.assign(n + 1, 0);
		w = _w, mp = _mp;
	}
	void dfs(int x, int par) {
		vis[x] = 1, sz[x] = w[x], dp1[x] = 0;
		for(auto i : mp[x]) if(i != par) {
			dfs(i, x); 
			dp1[x] += dp1[i] + bool(w[x]) * sz[i];
			sz[x] += sz[i];
		}
		int temp = 0, cur = 0;
		for(auto i : mp[x]) if(i != par) {
			temp +=  dp1[i] * (sz[x] - sz[i]);
			temp += cur * sz[i];
			cur += sz[i];
		}
		if(w[x]) ans += temp;
		return;
	}
};
namespace solver1 {
	int n, m, ii, timestamp, bccid;
	vector<int> es, x, y, ide, idv, sz;
	vector<int> L, D, pre, iscut;
	vector<vector<int>> mp1, mp2;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		ii = 0, timestamp = 0, bccid = 0;
		es.assign(m + 1, 0);
		sz.assign(2 * n + 1, 0);
		x.assign(m + 1, 0);
		y.assign(m + 1, 0);
		ide.assign(m + 1, 0);
		idv.assign(n + 1, 0);
		L.assign(n + 1, 0);
		D.assign(n + 1, 0);
		pre.assign(m + 1, 0);
		iscut.assign(n + 1, 0);
		mp1.assign(n + 1, vector<int>());
		mp2.assign(2 * n + 1, vector<int>());
	}
	void add_edge(int u, int v, int id) {
		x[id] = u, y[id] = v;
		es[id] = u ^ v;
		mp1[u].push_back(id);
		mp1[v].push_back(id);
	}
	void dfs(int x, int par) {
		D[x] = L[x] = ++ timestamp;
		int cnt = 0, isAP = 0;
		for(auto i : mp1[x]) if(i != par && es[i]) {
			int to = es[i] ^ x;
			if(!D[to]) {
				pre[ii ++] = i;
				cnt ++, dfs(to, i);
				L[x] = min(L[x], L[to]);
				if(L[to] >= D[x]) {
					isAP = 1, bccid ++;
					while(pre[ii] != i) {
						ii --, ide[pre[ii]] = bccid;
					}
				}
			}
			else if(D[to] < D[x]) {
				pre[ii ++] = i;
				L[x] = min(L[x], D[to]);
			}
		}
		if(par == -1 && cnt < 2) isAP = 0;
		iscut[x] = isAP;
		return;
	}
	int solve() {
		rep(i, 1, n) if(!D[i]) dfs(i, -1);
		rep(i, 1, n) if(iscut[i]) idv[i] = ++bccid;
		rep(i, 1, m) if(!iscut[x[i]] && es[i]) idv[x[i]] = ide[i];
		rep(i, 1, m) if(!iscut[y[i]] && es[i]) idv[y[i]] = ide[i];
		rep(i, 1, n) sz[idv[i]] ++;
		rep(i, 1, m) if(es[i]) {
			if(sz[ide[i]] && iscut[x[i]]) {
				mp2[idv[x[i]]].push_back(ide[i]);
				mp2[ide[i]].push_back(idv[x[i]]);
			}
			if(sz[ide[i]] && iscut[y[i]]) {
				mp2[idv[y[i]]].push_back(ide[i]);
				mp2[ide[i]].push_back(idv[y[i]]);
			}
			if(iscut[x[i]] && iscut[y[i]] && !sz[ide[i]]) {
				mp2[idv[x[i]]].push_back(idv[y[i]]);
				mp2[idv[y[i]]].push_back(idv[x[i]]);
			}
		}
		vprint(all(iscut));
		vprint(all(idv));
		vprint(all(ide));
		vprint(all(sz));
		rep(i, 1, 2 * n) {
			sort(all(mp2[i]));
			mp2[i].resize(unique(all(mp2[i])) - mp2[i].begin());
			print(i);
			vprint(all(mp2[i]));
		}
		solver::init_(2 * n, mp2, sz);
		int ans = 0, cnt = 0;
		rep(i, 1, 2 * n) if(!solver::vis[i]) solver::dfs(i, i);
		rep(i, 1, 2 * n) if(sz[i]) cnt ++;
		rep(i, 1, 2 * n) {
			ans += sz[i] * (sz[i] - 1) * (sz[i] - 2) / 2;
			ans += sz[i] * (sz[i] - 1) * (cnt - 1);
		}
		rep(i, 1, n) if(iscut[i]) {
			for(auto j : mp2[idv[i]]) ans += sz[j] * (sz[j] - 1) / 2;
		}
		print(solver::ans);
		ans += solver::ans;
		return ans * 2;
	}
}
using namespace solver1;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n, m);
	rep(i, 1, m) {
		int a, b; cin >> a >> b;
		add_edge(a, b, i);
	}
	cout << solve() << "\n";
	return 0;
}

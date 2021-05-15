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
#define MAXN 1000005
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace LCA {
	int n, lg, timestamp;
	vector<vector<int>> mp, ac;
	vector<int> d, D, rD, leaf;
	void dfs(int x, int par, int dd) {
		d[x] = dd, D[x] = ++timestamp;
		rD[timestamp] = x, ac[0][x] = par;
		leaf[x] = (mp[x].size() < 1 || x != par && mp[x].size() == 1);
		for(auto i : mp[x]) {
			if(i == par) continue;
			dfs(i, x, dd + 1);
		}
	}
	void init_(int _n, vector<vector<int>> _mp) {
		n = _n, lg = 31 - __builtin_clz(n);
		mp = _mp, timestamp = 0;
		ac.assign(lg + 1, vector<int>(n + 1, 0));
		d.assign(n + 1, 0);
		D.assign(n + 1, 0);
		rD.assign(n + 1, 0);
		leaf.assign(n + 1, 0);
		leaf[0] = 1;
		dfs(1, 1, 0);
		rep(i, 1, lg) rep(j, 1, n) {
			ac[i][j] = ac[i - 1][ac[i - 1][j]];
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
} ;
using LCA::rD;
using LCA::D;
using LCA::d;
using LCA::leaf;
namespace solver {
	int n, ii;
	vector<int> a, b, need, rneed;
	vector<int> id, ch;
	vector<set<pii>> c, rc;
	vector<vector<int>> mp;
	void init_(int _n) {
		n = _n, ii = 1;
		a.assign(n + 1, 0);
		b.assign(n + 1, 0);
		need.assign(n + 1, 0);
		rneed.assign(n + 1, 0);
		id.assign(n + 1, 0);
		ch.assign(n + 1, 0);
		c.assign(2 * n + 1, set<pii>());
		rc.assign(2 * n + 1, set<pii>());
		mp.assign(n + 1, vector<int>());
	}
	bool dfs(int x, int par, int dd) {
		int cur = LCA::lca(need[x], rneed[x]), y = 1;
		if(cur != need[x] && cur != rneed[x] || !need[x] || !rneed[x]) return 0;
		id[x] = ii;
		if(d[need[x]] > d[dd]) dd = need[x];
		if(d[rneed[x]] > d[dd]) dd = rneed[x];
		if(d[dd] == d[x]) ii ++;
		else {
			for(auto i : mp[x]) {
				if(i == par) continue;
				if(LCA::lca(i, dd) != x) ch[x] = i;
			}
		}
		if(ch[x]) dfs(ch[x], x, dd);
		for(auto i : mp[x]) {
			if(i == par || i == ch[x]) continue;
			y &= dfs(i, x, i);
		}
		return y;
	}
	bool build() {
		LCA::init_(n, mp);
		vector<int> v;
		rep(i, 1, n) {
			v.push_back(a[i]);
			v.push_back(b[i]);
		}
		sort(all(v)), v.resize(unique(all(v)) - v.begin());
		rep(i, 1, n) {
			a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
			b[i] = lower_bound(v.begin(), v.end(), b[i]) - v.begin() + 1;
		}
		rep(i, 1, n) {
			int x = rD[i];
			c[a[x]].insert({d[x], x});
			rc[b[x]].insert({d[x], x});
			if(leaf[x]) for(int j = i; (i == j || !leaf[rD[j]]); j--) {
				int y = rD[j];
				if(!need[y]) {
					auto it = c[b[y]].upper_bound(pii(d[y],INF));
					if(it == c[b[y]].begin()) return 0;
					it = prev(it);
					if(LCA::lca(it -> second, y) != it -> second || 
						rneed[it -> second]) return 0;
					need[y] = it -> second;
					rneed[it -> second] = y;
					c[b[y]].erase(it);
					rc[b[y]].erase(rc[b[y]].find(pii(d[y], y)));
				}
				if(!rneed[y]) {
					auto it = rc[a[y]].upper_bound(pii(d[y],INF));
					if(it == rc[a[y]].begin()) return 0;
					it = prev(it);
					if(LCA::lca(it -> second, y) != it -> second ||
						need[it -> second]) return 0;
					rneed[y] = it -> second;
					need[it -> second] = y;
					rc[a[y]].erase(it);
					c[a[y]].erase(c[a[y]].find(pii(d[y], y)));
				}
			}
		}
		return dfs(1, 1, 1);
	}
	int dp(int x, int par) {
		int ans = 1, cnt = 1;
		for(auto i : mp[x]) {
			if(i == par) continue;
			cnt ++;
			ans = ans * dp(i, x) % MOD;
		}
		if(!ch[x]) ans = ans * cnt % MOD;		
		return ans;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n, s; cin >> n >> s;
		init_(n);
		rep(i, 1, n - 1) {
			int x, y; cin >> x >> y;
			mp[x].push_back(y);
			mp[y].push_back(x);
		}
		rep(i, 1, n) cin >> a[i];
		rep(i, 1, n) cin >> b[i];
		bool good = build();
		int ans = dp(1, 1) * good;
		cout << (s == 1? bool(ans) : ans) << "\n";
	}
	return 0;
}

#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MOD 1000000007
#define MAXN 1000005
#define eps (1e-9)

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
namespace solve_ {
	int n, lg, timestamp, ans; 
	vector<vector<int>> A, B, sp_in, sp_out;
	vector<int> sz, a, in, out, id;
	void init_(int _n) {
		n = _n, timestamp = 0, ans = 0;
		lg = 31 - __builtin_clz(n);
		A.assign(n + 1, vector<int>());
		B.assign(n + 1, vector<int>());
		sp_in.assign(lg + 1, vector<int>(n + 1, 0));
		sp_out.assign(lg + 1, vector<int>(n + 1, 0));
		sz.assign(n + 1, 0);
		a.assign(n + 1, 0);
		in.assign(n + 1, 0);
		out.assign(n + 1, 0);
		id.assign(2 * n + 1, 0);
	}
	void dfs1(int x, int par) {
		a[x] = ++timestamp;
		sz[x] = 1;
		for(auto i : A[x]) {
			if(i == par) continue;
			dfs1(i, x);
			sz[x] += sz[i];
		}
	}
	void dfs2(int x, int par) {
		in[a[x]] = ++timestamp;
		id[timestamp] = a[x];
		for(auto i : B[x]) {
			if(i == par) continue;
			dfs2(i, x);
		}
		out[a[x]] = ++timestamp;
		id[timestamp] = a[x];
	}
	void build() {
		timestamp = 0, dfs1(1, 1);
		timestamp = 0, dfs2(1, 1);
		rep(i, 1, n) {
			sp_in[0][i] = in[i];
			sp_out[0][i] = out[i]; 
		}
		rep(i, 1, lg) rep(j, 1, n) {
			sp_in[i][j] = min(sp_in[i - 1][j], sp_in[i - 1][min(n, j + (1 << (i - 1)))]);
			sp_out[i][j] = max(sp_out[i - 1][j], sp_out[i - 1][min(n, j + (1 << (i - 1)))]);
		}
	}
	bool query(int l, int r) {
		int cur = 31 - __builtin_clz(r - l + 1);
		int ll = min(sp_in[cur][l], sp_in[cur][r - (1 << cur) + 1]);
		int rr = max(sp_out[cur][l], sp_out[cur][r - (1 << cur) + 1]);
		return ((rr - ll + 1) == (r - l + 1) * 2) && (id[ll] == id[rr]);
	}
	void dfs3(int x, int par) {
		for(auto i : A[x]) {
			if(i == par) continue;
			int l = a[i], r = a[i] + sz[i] - 1;
			ans += query(l, r);
			dfs3(i, x);
		}
	}
	
};
using namespace solve_;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 2, n) {
		int x; cin >> x;
		A[i].push_back(x);
		A[x].push_back(i);
	} 	
	rep(i, 2, n) {
		int x; cin >> x;
		B[i].push_back(x);
		B[x].push_back(i);
	}
	build(), dfs3(1, 1);
	cout << ans << "\n";
		
	return 0;

}

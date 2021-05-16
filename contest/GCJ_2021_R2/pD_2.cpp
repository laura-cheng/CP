#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

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
void kout() { cerr << endl;} 
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
struct KM {
	const static int P = 150;
	const static int INF = 1000000000000000000;
	int n, ii, slack[P];
	int Lx[P], Ly[P], match[P];
	int visx[P], visy[P];
	int a[P][P];
	void init_(int _n) {
		n = _n, ii = 0;
		rep(i, 1, n) {
			slack[i] = INF;
			visx[i] = visy[i] = 0;
			Lx[i] = Ly[i] = 0;
			match[i] = -1;
			rep(j, 1, n) a[i][j] = 0;
		}
	}
	bool dfs(int x, bool aug) {
		if(visx[x] == ii) return false;
		visx[x] = ii;
		rep(i, 1, n) if(visy[i] != ii) {
			int cur = Lx[x] + Ly[i] - a[x][i];
			if(cur == 0) {
				visy[i] = ii;
				if(match[i] == -1 || dfs(match[i], aug)) {
					if(aug) match[i] = x;
					return true;
				}
			}
			else slack[i] = min(slack[i], cur);
		}
		return false;
	}
	bool augment() {
		rep(i, 1, n) if(visy[i] != ii && slack[i] == 0) {
			visy[i] = ii;
			if(match[i] == -1 || dfs(match[i], false)) {
				return true;
			}
		}
		return false;
	}
	void relabel() {
		int ans = INF;
		rep(i, 1, n) if(visy[i] != ii) 
			ans = min(ans, slack[i]);
		rep(i, 1, n) {
			if(visy[i] == ii) Ly[i] += ans;
			else slack[i] -= ans;
			if(visx[i] == ii) Lx[i] -= ans;
		}
	}
	int solve() { 
		rep(i, 1, n) rep(j, 1, n) 
			Lx[i] = max(Lx[i], a[i][j]);
		int ans = 0;
		rep(i, 1, n) {
			rep(j, 1, n) slack[j] = INF;
			ii ++;
			if(dfs(i, true)) continue;
			while(!augment()) relabel();
			ii ++;
			assert(dfs(i, true));
		}
		rep(i, 1, n) ans += a[match[i]][i];
		return ans;
	}
};
namespace solver {
	int r, c, f, s, m, g;
	vector<pii> M, G;
	vector<vector<int>> a, b;
	KM km;
	void init_(int _r, int _c, int _f, int _s) {
		r = _r, c = _c, f = _f, s = _s;
		M.clear();
		G.clear();
		a.assign(r + 1, vector<int>(c + 1, 0));
		b.assign(r + 1, vector<int>(c + 1, 0));
		km.init_(100); 
	}
	int solve() {
		rep(i, 1, r) rep(j, 1, c) {
			if(a[i][j] == b[i][j]) continue;
			else if(a[i][j]) M.push_back({i, j});
			else G.push_back({i, j});
		}
		rep(i, 1, M.size()) rep(j, 1, G.size()) {
			pii aa = M[i - 1], bb = G[j - 1];
			km.a[i][j] = max(km.a[i][j], 
				2 * f - (abs(aa.first - bb.first) + abs(aa.second - bb.second)) * s);
		}
		return (M.size() + G.size()) * f - km.solve();
	}
}
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int r, c, f, s;
		cin >> r >> c >> f >> s;
		init_(r, c, f, s);
		rep(i, 1, r) rep(j, 1, c) {
			char x; cin >> x;
			if(x == 'M') a[i][j] = 1;
			else a[i][j] = 0;
		}
		rep(i, 1, r) rep(j, 1, c) {
			char x; cin >> x;
			if(x == 'M') b[i][j] = 1;
			else b[i][j] = 0;
		}
		cout << "Case #" << tt << ": " << solve() << "\n";
	}
	return 0;
}

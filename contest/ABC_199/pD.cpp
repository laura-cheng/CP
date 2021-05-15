#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define eps (1e-9)
#define MAXN 1000005
#define MOD 1000000007

using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt199374 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace dsu {
	int n, cnt;
	vector<int> par, rk;
	void init_(int _n) {
		n = _n, cnt = _n;
		par.assign(n + 1, 0);
		rk.assign(n + 1, 0);
		rep(i, 1, n) par[i] = i;
	}
	int find_par(int a) {
		if(par[par[a]] == par[a]) return par[a];
		else return par[a] = find_par(par[a]);
	}
	void unite(int a, int b) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return;
		cnt --;
		if(rk[aa] > rk[bb]) par[bb] = aa;
		else if(rk[bb] > rk[aa]) par[aa] = bb;
		else par[bb] = aa, rk[aa] ++;
	}
	bool same(int a, int b) {
		return find_par(a) == find_par(b);
	}
};
namespace solver {
	int n, m;
	vector<pii> es;
	vector<bool> ok, ok1;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		ok.assign(1 << n, 1);
		ok1.assign(1 << n, 1);
		es.clear();
	}
	void build() {
		rep(i, 0, (1 << n)) {
			dsu::init_(2 * n);
			for(auto j : es) {
				if(!((i >> (j.first - 1)) & 1)) continue;
				if(!((i >> (j.second - 1)) & 1)) continue;
				if(dsu::same(j.first, j.second)) {
					ok[i] = 0;
					break;
				}
				dsu::unite(j.first, j.second + n);
				dsu::unite(j.first + n, j.second);
			}
		}
		rep(i, 0, (1 << n)) {
			for(auto j : es) {
				if(!((i >> (j.first - 1)) & 1)) continue;
				if(!((i >> (j.second - 1)) & 1)) continue;
				ok1[i] = 0;
				break;
			}
		}
	}
	int solve() {
		int ans = 0;
		rep(i, 0, (1 << n) - 1) {
			if(!ok1[i]) continue;
			if(!ok[i ^ ((1 << n) - 1)]) continue;
			dsu::init_(n);
			for(auto j : es) {
				if((i >> (j.first - 1)) & 1) continue;
				if((i >> (j.second - 1)) & 1) continue;
				dsu::unite(j.first, j.second);
			}
			ans += (1 << (dsu::cnt - __builtin_popcount(i)));
		}
		return ans;
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n, m);
	rep(i ,1, m) {
		int x, y; cin >> x >> y;
		es.push_back({x, y});
	}
	build();
	cout << solve() << "\n";
	return 0;
}
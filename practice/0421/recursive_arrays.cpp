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

#define MAXN 1000005
#define MOD 1000000007
#define INF 1000000000000000000
#define eps (1e-9)

using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_uodate>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); };
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace dsu {
	int n;
	vector<int> sz, par, cyc;
	void init_(int _n) {
		n = _n;
		sz.assign(n + 1, 0);
		par.assign(n + 1, 0);
		cyc.assign(n + 1, 0);
		rep(i, 1, n) {
			par[i] = i;
			sz[i] = 1;
		}
	}
	int find_par(int a) {
		while(a != par[a]) a = par[a];
		return a;
	}
	void unite(int a, int b) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return;
		if(sz[aa] < sz[bb]) swap(aa, bb);
		par[bb] = aa;
		sz[aa] += sz[bb];
		cyc[aa] = max(cyc[aa], cyc[bb]);
		return;
	}
};
namespace math {
	int n;
	vector<int> p, fac;
	void init_(int _n) {
		n = _n;
		p.clear();
		fac.assign(n + 1, 1);
		rep(i, 2, n) {
			if(fac[i] == 1) p.push_back(i);
			for(auto j : p) {
				if(i * j > n) break;
				fac[i * j] = j;
				if(i % j == 0) break;
			}
		}
	}
	vector<pii> deco(int x) {
		vector<pii> ans;
		while(fac[x] != 1) {
			int y = fac[x];
			ans.push_back({y, 0});
			while(x % y == 0) {
				ans[ans.size() - 1].second ++;
				x /= y;
			}
		}
		if(x != 1) ans.push_back({x, 1});
		return ans;
	}
}
namespace solver {
	int n, timestamp;
	vector<int> a, vis, gray, id, b;
	void init_(int _n) {
		n = _n, timestamp = 0;
		a.assign(n + 1, 0);
		vis.assign(n + 1, 0);
		gray.assign(n + 1, 0);
		id.assign(n + 1, 0);
		b.assign(n + 1, 0);
	}
	void dfs(int x) {
		gray[x] = 1;
		if(b[x])
	}
	int solve() {
		
	}	
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	return 0;
}


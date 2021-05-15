#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b;i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

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
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n;
	vector<int> v;
	vector<pii> a, ver;
	
	struct seg {
		lld m, k, v;
		lld operator()(lld x) {
			return m * x + k;
		}
		bool operator<(seg b) {
			return v < b.v;
		} 
	};
	vector<vector<seg>> st;
	void init_(int _n) {
		n = _n;
		a.assign(n, {0, 0});
	}
	void build() {
		for(auto i : a) v.push_back(i.first);
		sort(all(v)), v.resize(unique(all(v)) - v.begin());
		st.assign(v.size(), vector<seg>());
		ver.assign(v.size(), {0, 0});
		rep(i, 0, n - 1) {
			pii aa = a[i], bb = a[(i + 1) % n];
			if(aa > bb) swap(aa, bb);
			lld x = bb.first - aa.first, y = bb.second - aa.second;
			print(i, x, y);
			rep(j, 0, signed(v.size()) - 1) {
				if(v[j] <= bb.first && v[j] >= aa.first) {
					seg cur = {min((lld)1e9, y / x), (lld)aa.second - (lld)aa.first * min((lld)1e10, y / x), 0};
					cur.v = cur(v[j]);
					st[j].push_back(cur);
				}
			}
		}
		rep(i, 0, signed(v.size()) - 1) {
			sort(all(st[i]));
			print(v[i]);
			for(auto j : st[i]) {
				print(j.m, j.k, j.v);
			}
		}
	}
	
	bool solve(pii x) {
		int id = upper_bound(v.begin(), v.end(), x.first) - v.begin() - 1;
		if(id < 0) return 0;
		int l = -1, r = signed(st[id].size()) - 1;
		while(r - l > 1) {
			int mid = (l + r) / 2;
			if(x.second <= st[id][mid](x.first)) r = mid;
			else l = mid;
		}
		print(x.first, x.second, id, r);
		int ans = (signed(st[id].size()) - r );
		return (ans & 1) || abs(st[id][r](x.first) - x.second) <= eps;
	} 
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n);
	for(auto &i : a) 
		cin >> i.first >> i.second;
	build();
	int cnt = 0;
	rep(i, 1, m) {
		int x, y; cin >> x >> y;
		cnt += solve({x, y});
	}
	cout << cnt << "\n";
	return 0;
}


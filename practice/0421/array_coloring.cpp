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
namespace solver {
	int n, m, cc;
	struct seg {
		int l, r, id;
		bool operator<(seg b) {
			return (r - l) < (b.r - b.l);
		}
	};
	vector<int> a, L, R;
	vector<seg> b;
	vector<vector<int>> mp, id;
	void init_(int _n, int _m) {
		n = _n, m = _m, cc = 0;
		a.assign(n + 1, 0);
		L.assign(m + 1, INF);
		R.assign(m + 1, -INF);
		mp.assign(m + 1, vector<int>());
		id.assign(m + 1, vector<int>());
	}
	void build() {
		rep(i, 1, n) {
			L[a[i]] = min(L[a[i]], i);
			R[a[i]] = max(R[a[i]], i);
			id[a[i]].push_back(i);
		}
		id[0].push_back(n + 1);
		rep(i, 1, m) {
			if(L[i] == INF) cc ++;
			else b.push_back({L[i], R[i], i});
		}
		sort(all(b));
		map<int, int> cur;
		for(auto i : b) {
			auto it = cur.lower_bound(i.l);
			auto it1 = cur.lower_bound(i.r);
			for(auto j = it; j != it1;) {
				mp[i.id].push_back(j -> second);
				auto temp = j;
				j = next(j);
				cur.erase(temp);
			}
			cur[i.l] = i.id;
		}
		for(auto i : cur) mp[0].push_back(i.second);
		return;
	}
	int dfs(int x) {
		int cur = 0, ans = 0;
		for(auto i : id[x]) {
			int mx = 0, cnt = 0;
			while(cur < mp[x].size() && 
				id[mp[x][cur]][0] < i) {
				mx = max(mx, dfs(mp[x][cur]));
				cur ++, cnt ++;	
			}
			ans = max(ans, mx + cnt);
		}
		return max(1ll, ans);
	}
	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n, m);
	rep(i, 1, n) cin >> a[i];
	build();
	cout << dfs(0) + cc - 1 << "\n";
	return 0;
}


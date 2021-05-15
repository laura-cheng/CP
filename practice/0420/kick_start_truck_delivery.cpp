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
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace seg {
	int n;
	vector<int> val;
	inline int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void init_(int _n) {
		n = _n;
		val.assign(2 * n + 1, 0);
	} 
	void modify(int L, int R, int l, int r, int v) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return;
		else if(l <= L && r >= R) val[nd] = __gcd(val[nd], v);
		else {
			modify(L, mid, l, r, v);
			modify(mid + 1, R, l, r, v);
		}
	}
	int query(int L, int R, int id) {
		if(L == R) return val[get(id, id)];
		else {
			int mid = (L + R) / 2;
			if(id <= mid) return __gcd(val[get(L, R)], query(L, mid, id));
			else return __gcd(val[get(L, R)], query(mid + 1, R, id));
		}
	}
};
namespace solver {
	int n, q, timestamp;
	struct query {
		int w, x, id;
		bool operator<(query b) {
			return w < b.w;
		}
	};
	struct edge {
		int u, v, L, A;
		bool operator<(edge b) {
			return L < b.L;
		}
	};
	vector<query> qq;
	vector<vector<int>> mp;
	vector<int> ans, in, out, d;
	vector<edge> v;
	void dfs(int x, int par, int dd) {
		in[x] = ++ timestamp;
		d[x] = dd;
		for(auto i : mp[x]) {
			if(i == par) continue;
			dfs(i, x, dd + 1);
		}
		out[x] = ++ timestamp;
	}
	void init_(int _n, int _q) {
		n= _n, q = _q;
		timestamp = 0;
		qq.clear();
		v.clear();
		mp.assign(n + 1, vector<int>());
		ans.assign(q + 1, 0);
		in.assign(n + 1, 0);
		out.assign(n + 1, 0);
		d.assign(n + 1, 0);
		seg::init_(2 * n);
		
	}
	void solve() {
		dfs(1, 1, 0);
		sort(all(v)), sort(all(qq));
		int cur = 0;
		for(auto i : qq) {
			while(cur < v.size() && i.w >= v[cur].L) {
				int x = (d[v[cur].u] > d[v[cur].v] ? v[cur].u : v[cur].v);
				seg::modify(1, 2 * n, in[x], out[x], v[cur].A);
				cur ++;
			}
			ans[i.id] = seg::query(1, 2 * n, in[i.x]);
		}
		return;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int n, q; cin >> n >> q;
		init_(n, q);
		rep(i, 1, n - 1) {
			int a, b, L, A; 
			cin >> a >> b >> L >> A;
			mp[a].push_back(b);
			mp[b].push_back(a);
			v.push_back({a, b, L, A});
		}
		rep(i, 1, q) {
			int x, w; cin >> x >> w;
			qq.push_back({w, x, i});
		}
		solve();
		cout << "Case #" << tt << ": ";
		rep(i, 1, q) cout << ans[i] << " \n"[i == q];
	}
	
	return 0;
}

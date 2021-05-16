#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MOD 1000000007
#define MAXN 1000005
#define INF 1000000000000000000
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
#define lowbit(x) (x & -x)
int n, m, t;
struct edge {
	int to, cost;
};
struct query {
	int l, r, k, id;
	bool operator<(query b) {
		return k < b.k;
	}
};
int timestamp;
vector<int> ans, in, out, bit;
vector<pii> a;
vector<query> b;
vector<vector<edge>> mp;
void init_() {
	in.assign(n + 1, 0);
	out.assign(n + 1, 0);
	bit.assign(2 * n + 1, 0);
	mp.assign(n + 1, vector<edge>());
	a.clear(), b.clear();
	timestamp = 0;
}
void dfs(int x, int par, int cs = 0) {
	in[x] = ++timestamp;
	a.push_back({cs, timestamp});
	for(auto i : mp[x]) {
		if(i.to == par) continue;
		dfs(i.to, x, i.cost);
	}
	out[x] = ++timestamp;
	a.push_back({cs, timestamp});
	return;
}
void build() {
	dfs(1, 1);
	rep(i, 1, m) {
		int u, v, k, l, r; 
		cin >> u >> v >> k;
		if(out[u] < in[v]) l = out[u], r = in[v];
		else l = out[v], r = in[u];
		b.push_back({l, r, k, i});
	}
	sort(all(b)), sort(all(a));
	return;
}
void modify(int x, int val) {
	for(int i = x; i <= 2 * n; i += lowbit(i)) {
		bit[i] ^= val;
	}
	return;
}
int query(int x) {
	int ans = 0;
	for(int i = x; i > 0; i -= lowbit(i)) {
		ans ^= bit[i];
	}
	return ans;
}
void solve() {
	int cur = 0;
	for(auto i : b) {
		while(cur < a.size() 
			&& i.k >= a[cur].first) {
			modify(a[cur].second, a[cur].first);
			cur ++;		
		}
		ans[i.id] = query(i.r) ^ query(i.l - 1);
	}
	return;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n;
		init_();
		rep(i, 1, n - 1) {
			int u, v, k;
			cin >> u >> v >> k;
			mp[u].push_back({v, k});
			mp[v].push_back({u, k});
		}
		cin >> m;
		ans.assign(m + 1, 0);
		build();
		solve();
		rep(i, 1, m) cout << ans[i] << "\n";
	}
	return 0;
}

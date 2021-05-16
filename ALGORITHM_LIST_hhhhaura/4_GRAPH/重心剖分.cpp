#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define MAXN 1000005
#define MOD 1000000007
#define eps (1e-9)
#define INF 1000000000000000000

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("["+ string(#a) + "] = ", a)
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
vector<int> es, cost, yes;
vector<vector<int>> mp;
struct centroid_deco {
	int n;
	vector<int> sz, mx, pa, dep, vis;
	vector<vector<int>> dis;
	vector<int> cnt, sum, minu;
	void init_(int _n) {
		n = _n;
		sz.assign(n + 1, 0);
		mx.assign(n + 1, 0);
		pa.assign(n + 1, 0);
		dep.assign(n + 1, 0);
		cnt.assign(n + 1, 0);
		sum.assign(n + 1, 0);
		minu.assign(n + 1, 0);
		vis.assign(n + 1, 0);
		dis.assign(32, vector<int>(n + 1, 0));
		deco(1);
		return;
	} 
	void get_sz(int x, int par) {
		sz[x] = 1, mx[x] = 0;
		for(auto i : mp[x]) {
			int to = es[i] ^ x;
			if(to == par || vis[to]) continue;
			get_sz(to, x);
			sz[x] += sz[to];
			mx[x] = max(mx[x], sz[to]);
		}
	}
	int get_cen(int x, int par, int tot) {
		int best = x;
		for(auto i : mp[x]) {
			int to = es[i] ^ x;
			if(to == par || vis[to]) continue;
			int cur = get_cen(to, x, tot);
			if(max(tot - sz[cur], mx[cur]) < 
				max(tot - sz[best], mx[best])) best = cur;
		}
		return best;
	}
	void get_dis(int x, int par, int d, int tot = 0) {
		dis[d][x] = tot;
		for(auto i : mp[x]) {
			int to = es[i] ^ x;
			if(to == par || vis[to]) continue;
			get_dis(to, x, d, tot + cost[i]);
		}
		return;
	}
	void deco(int x, int par = -1, int d = 0) {
		get_sz(x, x);
		int c = get_cen(x, x, sz[x]);
		vis[c] = 1, dep[c] = d, pa[c] = par;
		get_dis(c, c, d);
		for(auto i : mp[c]) {
			int to = es[i] ^ c;
			if(vis[to]) continue;
			deco(to, c, d + 1);
		}
	}
	void modify(int x) {
		int cur = x;
		while(cur != -1) {
			cnt[cur] ++ ;
			sum[cur] += dis[dep[cur]][x];
			if(dep[cur]) minu[cur] += dis[dep[cur] - 1][x];
			cur = pa[cur];
		}
	}
	int query(int x) {
		int cur = x, ans = sum[cur];
		while(pa[cur] != -1) {
			int f = pa[cur], c = cur;
			ans += sum[f] - minu[c]
				+ (cnt[f] - cnt[c]) * dis[dep[f]][x];
			cur = pa[cur]; 
		}
		return ans;
	}

} deco;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q; cin >> n >> q;
	mp.assign(n + 1, vector<int>(0));
	es.clear(), cost.clear();
	yes.assign(n + 1, 0);
	rep(i, 1, n - 1) {
		int a, b, c; 
		cin >> a >> b >> c;
		a ++, b ++;
		es.push_back(a ^ b);
		cost.push_back(c);
		mp[a].push_back(es.size() - 1);
		mp[b].push_back(es.size() - 1);
	}
	deco.init_(n);
	rep(i, 1, q) {
		int t, x; cin >> t >> x;
		x ++;
		if(t == 1) {
			if(yes[x]) continue;
			deco.modify(x);
			yes[x] = 1;
		}
		else cout << deco.query(x) << "\n";
	}
	return 0;
}


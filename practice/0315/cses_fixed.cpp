#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i <= a; i--)
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
struct TDV {
	int n, k, ans;
	vector<vector<int>> mp;
	vector<int> sz, vis, mx, cur, temp;
	void init_(int _n, int _k) {
		n = _n, k = _k, ans = 0;
		mp.assign(n + 1, vector<int>());
		sz.assign(n + 1, 0);
		vis.assign(n + 1, 0);
		mx.assign(n + 1, 0);
	}
	void get_sz(int x, int par) {
		sz[x] = 1, mx[x] = 0;
		for(auto i : mp[x]) {
			if(i == par || vis[i]) continue;
			get_sz(i, x);
			sz[x] += sz[i];
			if(mx[x] < sz[i]) mx[x] = sz[i];
		}
		return;
	}
	int get_cen(int x, int par, int tot) {
		int best = x;
		for(auto i : mp[x]) {
			if(vis[i] || i == par) continue;
			int cur = get_cen(i, x, tot);
			if(max(tot - sz[best], mx[best]) > max(tot - sz[cur], mx[cur])) {
				best = cur;
			}
		}
		return best;
	}
	int do_cen(int c, int mx) {
		if(mx < k) return 0;
		cur.assign(mx + 1, 0);
		cur[0] = 1;
		int ans = 0;
		for(auto i : mp[c]) {
			if(vis[i]) continue;
			temp.clear();
			cal(i, c, 1);
			for(auto j : temp) {
				if(k >= j && k - j <= mx) {
					ans += cur[k - j];
				}
			}
			for(auto j : temp) {
				cur[j] ++;
			}
		}
		return ans;
	}
	void tdv(int x) {
		get_sz(x, x);
		int c = get_cen(x, x, sz[x]);
		vis[c] = 1;
		int cur = do_cen(c, sz[x]);
		ans += cur;
		
		for(auto i : mp[c]) {
			if(vis[i]) continue;
			tdv(i);
		}
	}
	void cal(int x, int par, int d) {
		temp.push_back(d);
		for(auto i : mp[x]) {
			if(i == par || vis[i]) continue;
			cal(i, x, d + 1);
		}
		return;
	}
} ac;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	ac.init_(n, k);
	rep(i, 1, n - 1) {
		int a, b; cin >> a >> b;
		ac.mp[a].push_back(b);
		ac.mp[b].push_back(a);
	}
	ac.tdv(1);
	cout << ac.ans << "\n";
	return 0;
}

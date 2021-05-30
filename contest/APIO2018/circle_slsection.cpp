#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i ,a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)

using namespace std;
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().times_since_epoch().count())

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n;
	vector<int> vis, x, y, r;
	void init_(int _n) {
		n = _n;
		x.assign(n + 1, 0);
		y.assign(n + 1, 0);
		r.assign(n + 1, 0);
		vis.assign(n + 1, 0);
	}
	bool cmp(int a, int b) {
		if(r[a] != r[b]) return r[a] > r[b];
		else return a < b;
	}
	bool comp(int a, int b) {
		int xx = x[a] - x[b];
		int yy = y[a] - y[b];
		int ans = xx * xx + yy * yy;
		int rr = (r[a] + r[b]) * (r[a] + r[b]);
		return ans <= rr;
	}
	void solve() {
		vector<int> ord;
		rep(i, 1, n) ord.push_back(i);
		sort(all(ord), cmp);
		for(auto i : ord) {
			if(vis[i]) continue;
			vis[i] = i;
			rep(j, 1, n) if(!vis[j] && comp(i, j)) vis[j] = i; 
		} 
		rep(i, 1, n) cout << vis[i] << " \n"[i == n];
	}

};
namespace solver1 {
	int n;
	vector<int> vis, x, y, r;
	void init_(int _n) {
		n = _n;
		x.assign(n + 1, 0);
		y.assign(n + 1, 0);
		r.assign(n + 1, 0);
		vis.assign(n + 1, 0);
	}
	bool cmp(int a, int b) {
		if(r[a] != r[b]) return r[a] > r[b];
		else return a < b;
	}
	void solve() {
		vector<int> ord;
		multiset<pii> mp;
		rep(i, 1, n) {
			ord.push_back(i);
			mp.insert({x[i] - r[i], -i});
			mp.insert({x[i] + r[i], i});
		}
		sort(all(ord), cmp);
		for(auto i : ord) if(!vis[i]) {
			auto L = mp.lower_bound({x[i] - r[i], -INF});
			auto R = mp.upper_bound({x[i] + r[i], -INF});
			while(L != mp.end() && L -> first <= x[i] + r[i]) {
				auto cur = L; 
				int id = cur -> second;
				vis[abs(id)] = i;
				auto to = mp.find({cur -> first + (id < 0 ? 1 : -1) * 2 * r[abs(id)], -id});
				mp.erase(to);
				L = next(L);mp.erase(cur);
			}
		}
		rep(i, 1, n) cout << vis[i] << " \n"[i == n];
	}

};
using namespace solver1;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) cin >> x[i] >> y[i] >> r[i];
	solve();
	
	return 0;
}

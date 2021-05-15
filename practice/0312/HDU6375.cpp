#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i ,a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

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
struct AC {
	int n;
	vector<int> rev, id;
	vector<deque<int>> a;
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, deque<int>());
		rev.assign(n + 1, 0);
		id.assign(n + 1, 0);
		rep(i, 1, n) id[i] = i;
	}
	void join(int x, int y, bool yes) {
		int i = x, j = y;
		x = id[i], y = id[j];
		rev[y] ^= yes;
		bool swapped = 0;
		if(a[x].size() < a[y].size()) {
			swap(id[i], id[j]);
			swap(x, y);
			rev[y] ^= 1;
			swapped ^= 1;
		}
		swapped ^= rev[x];
//		print(yes, rev[x], rev[y]);
		while(a[y].size()) {
			int v; 
			if(rev[y]) v = a[y].back(), a[y].pop_back();
			else v = a[y].front(), a[y].pop_front();
			
			if(swapped) a[x].push_front(v);
			else a[x].push_back(v);			
		}
		rev[y] = 0;
	}
	int del(int u, bool yes) {
		u = id[u];
		int ans = 0; yes ^= rev[u];
		if(a[u].size() == 0) return -1;
		if(yes) ans = a[u].back(), a[u].pop_back();
		else ans = a[u].front(), a[u].pop_front();
		return ans;
	}
	void add(int u, int val, bool yes) {
		u = id[u];
		yes ^= rev[u];
		if(yes) a[u].push_back(val);
		else a[u].push_front(val);
	}
} a;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q;
	while(cin >> n >> q) {
		a.init_(n);
		rep(i, 1, q) {
			int op, x, y, z;
			cin >> op >> x >> y;
			if(op == 1) cin >> z, a.add(x, z, y);
			else if(op == 2) cout << a.del(x, y) << "\n";
			else cin >> z, a.join(x, y, z);	
		}
	}
	return 0;
}

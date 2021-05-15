#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
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
struct leechao {
	struct ln {
		int m, k, flag;
		int operator()(int x) {
			if(!flag) return -INF;
			else return m * x + k;
		}
	};
	int n, p, root;
	vector<int> lch, rch;
	vector<ln> seg;
	void init_(int _n) {
		n = _n, p = 0;
		lch.assign(MAXN, 0);
		rch.assign(MAXN, 0);
		seg.assign(MAXN, {0, 0, 0});
		root = get_new();
	}
	int get_new() {
		return ++p;
	}
	void insert(int nd, int L, int R, ln a) {
		if(L == R || !seg[nd].flag) {
			if(a(L) > seg[nd](L)) seg[nd] = a;
			return;
		}
		int mid = (L + R) / 2;
		if(seg[nd].m > a.m) swap(a, seg[nd]);
		if(a(mid) > seg[nd](mid)) {
			swap(a, seg[nd]);
			if(!lch[nd]) lch[nd] = get_new();
			insert(lch[nd], L, mid, a);
		}
		else {
			if(!rch[nd]) rch[nd] = get_new();
			insert(rch[nd], mid + 1, R, a);
		}
	}
	int query(int nd, int L, int R, int x) {
		if(!nd) return -INF;
		else if(L == R) return seg[nd](x);
		else {
			int mid = (L + R) / 2;
			int val = seg[nd](x);
			if(x <= mid) return max(val, query(lch[nd], L, mid, x));
			else return max(val, query(rch[nd], mid + 1, R, x));
		}
	}
	void add(int m, int k) {
		insert(root, 1, n, {m, k, 1});
	}
	int ask(int x) {
		int ans = query(root, 1, n, x);
		print(x, ans);
		return query(root, 1, n, x);
	}
	

};
struct DP {
	struct node {
		int D, P, R, G;
		bool operator<(node b) {
			return D < b.D;
		}
	};
	int n, c, d;
	vector<int> dp;
	vector<node> a;
	leechao st;
	void init_(int _n, int _c, int _d) {
		n = _n, c = _c, d = _d;
		st.init_(1e9);
		dp.assign(n + 1, 0);
		a.assign(n + 1, {0, 0, 0});
	}
	int solve() {
		sort(all(a));
		dp[0] = c, st.add(0, c);
		rep(i, 1, n) {
			dp[i] = st.ask(a[i].D) - a[i].P;
			if(dp[i] < 0) dp[i] = -INF;
			st.add(a[i].G, dp[i] - (a[i].D + 1) * a[i].G + a[i].R);
		}
		int ans = 0;
		rep(i, 0, n) {
			ans = max(ans, dp[i] + (d - a[i].D) * a[i].G + a[i].R);
		}
		return ans;
	}

} dp;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, c, d; cin >> n >> c >> d;
	dp.init_(n, c, d);
	print("init");
	rep(i, 1, n) {
		int D, P, R, G;
		cin >> D >> P >> R >> G;
		dp.a[i] = {D, P, R, G};
	}
	cout << dp.solve() << "\n";
	return 0;
} 

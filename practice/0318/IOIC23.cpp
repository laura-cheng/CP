#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
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
	while(L < R) cerr << *L << " \n"[next(L) == R], ++ L;
}
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct segment_tree {
	int n;
	vector<int> a, sum, mx, chg, add;
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, 0);
		sum.assign(2 * n + 1, 0);
		mx.assign(2 * n + 1, 0);
		chg.assign(2 * n + 1, 0);
		add.assign(2 * n + 1, 0);
	}
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void build(int L, int R) {
		int nd = get(L, R), mid = (L + R) / 2;
		if(L == R) mx[nd] = sum[nd] = a[L];
		else {
			build(L, mid);
			build(mid + 1, R);
			pull(L, R);
		}
	}
	void pull(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int lch = get(L, mid), rch = get(mid + 1, R);
		mx[nd] = max({
			(chg[lch] ? chg[lch] : mx[lch]) + add[lch],
			(chg[rch] ? chg[rch] : mx[rch]) + add[rch]
		}); 
		sum[nd] = (
			((chg[lch] ? chg[lch] * (mid - L + 1) : sum[lch]) + (mid - L + 1) * add[lch]) + 
			((chg[rch] ? chg[rch] * (R - mid) : sum[rch]) + (R - mid) * add[rch])
		);
	}
	void push(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int lch = get(L, mid), rch = get(mid + 1, R);
		if(chg[nd]) {
			chg[lch] = chg[rch] = chg[nd];
			add[lch] = add[rch] = 0;
			mx[nd] = chg[nd];
			sum[nd] = (R - L + 1) * chg[nd];
			chg[nd] = 0;
		}
		if(add[nd]) {
			add[lch] += add[nd];
			add[rch] += add[nd];
			mx[nd] += add[nd];
			sum[nd] += add[nd] * (R - L + 1);
			add[nd] = 0;
		}
	}
	void modify1(int L, int R, int l, int r, int v) { // chg
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return;
		if(L != R) push(L, R);
		if(l <= L && r >= R) {
			add[nd] = 0, chg[nd] = v;
		}
		else {
			modify1(L, mid, l, r, v);
			modify1(mid + 1, R, l, r, v);
			pull(L, R);
		}
	}
	void modify2(int L, int R, int l, int r, int v) { // add
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return;
		if(L != R) push(L, R);
		if(l <= L && r >= R) {
			add[nd] += v;
		}
		else {
			modify2(L, mid, l, r, v);
			modify2(mid + 1, R, l, r, v);
			pull(L, R);
		}
	}
	int query1(int L, int R, int l, int r) { // sum
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return 0;
		if(L != R) push(L, R);
		if(l <= L && r >= R) return (chg[nd] ? (R - L + 1) * chg[nd] : sum[nd]) + add[nd];
		else return query1(L, mid, l, r) + query1(mid + 1, R, l, r);
	}
	int query2(int L, int R, int l, int r) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return -INF;
		if(L != R) push(L, R);
		if(l <= L && r >= R) return (chg[nd] ? chg[nd] : mx[nd]) + add[nd];
		else return max(query2(L, mid, l, r), query2(mid + 1, R, l, r));
	}
	int ask(int tp, int L, int R) {
		if(tp == 3) return query1(1, n, L, R);
		else return query2(1, n, L, R);
	}
	void change(int tp, int L, int R, int val) {
		if(tp == 1) modify1(1, n, L, R, val);
		else modify2(1, n, L, R, val);
	}
} st;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q; cin >> n >> q;
	st.init_(n);
	rep(i, 1, n) cin >> st.a[i];
	st.build(1, n);
	rep(i, 1, q) {
		int tp, a, b, c;
		cin >> tp >> a >> b;
		if(tp == 1 || tp == 2) {
			cin >> c;
			st.change(tp, a, b, c);
		}
		else cout << st.ask(tp, a, b) << "\n";
	}
	return 0;
}



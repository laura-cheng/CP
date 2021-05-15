#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MAXN 1000005
#define eps (1e-9)
#define MOD 1000000007

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
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct leechao {
	int n, p, root;
	struct ln {
		lld m, k; int id;
		ln(lld _m = -INF, lld _k = -INF, int _id = 0) {
			m = _m, k = _k, id = _id;
		}
		lld operator()(lld x) {
			if(!id) return -INF;
			return m * x + k;
		}
	};
	vector<ln> seg;
	vector<int> lch, rch; 
	int get_new() { return ++p; }
	void init_(int _n) {
		n = _n, p = 1, root = 1;
		seg.assign(1e6 + 1, ln());
		
		lch.assign(1e6 + 1, 0);
		rch.assign(1e6 + 1, 0);
	}
	void modify(int nd, int L, int R, ln a) {
		if(L == R) {
			if(a(L) > seg[nd](L)) seg[nd] = a;
			return;
		}
		int mid = (L + R) / 2;
		if(a.m < seg[nd].m) swap(a, seg[nd]);
		if(a(mid) > seg[nd](mid)) {
			swap(a, seg[nd]);
			if(!lch[nd]) lch[nd] = get_new();
			modify(lch[nd], L, mid, a);
		}
		else {
			if(!rch[nd]) rch[nd] = get_new();
			modify(rch[nd], mid + 1, R, a);
		}
		return;

	}
	void insert(int nd, int L, int R, int l, int r, ln a) {
		if(l > R || r < L) return;
		else if(l <= L && r >= R) modify(nd, L, R, a);
		else {
			int mid = (L + R) / 2;
			if(!lch[nd]) lch[nd] = get_new();
			if(!rch[nd]) rch[nd] = get_new();
			insert(lch[nd], L, mid, l, r, a);
			insert(rch[nd], mid + 1, R, l, r, a);
		}	
		return;
	}
	pair<lld, int> query(int nd, int L, int R, int x) {
		if(!nd) return make_pair(-INF, 0);
		else if(L == R) return make_pair(seg[nd](x), -seg[nd].id);
		else {
			int mid = (L + R) / 2;
			pair<lld, int> p, p1;
			if(x <= mid) p = query(lch[nd], L, mid, x);
			else p = query(rch[nd], mid + 1, R, x);
			p1 = make_pair(seg[nd](x), -seg[nd].id);
			return max(p, p1);
		}
	}
	int ask(int x) {
		pair<lld, int> p = query(root, 1, n, x);
		return -p.second;
	}
	void add(int x0, int y0, int x1, int y1, int id) {	
		if(x0 == x1) {
			ln cur = ln(0, max(y0, y1), id);
			insert(root, 1, n, x0, x0, cur);
		}
		else {
			if(x1 < x0) swap(x1, x0), swap(y0, y1);
			lld m = (lld)(y1 - y0) / (lld)(x1 - x0);
			lld k = y0 - m * x0;
			insert(root, 1, n, x0, x1, ln(m, k, id));
		}
	}
} st;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	st.init_(39989);
	int mod1 = 39989, mod2 = 1e9;
	int n, last_ans = 0, cnt = 0; 
	cin >> n;
	rep(i, 1, n) {
		int op; cin >> op;
		if(op == 0) {
			int k; cin >> k;
			k = (k + last_ans - 1 + mod1) % mod1 + 1;
			last_ans = st.ask(k);
			cout << last_ans << "\n";			
		}
		else {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			a = (a + last_ans - 1 + mod1) % mod1 + 1;
			b = (b + last_ans - 1 + mod2) % mod2 + 1;
			c = (c + last_ans - 1 + mod1) % mod1 + 1;
			d = (d + last_ans - 1 + mod2) % mod2 + 1;
			st.add(a, b, c, d, ++ cnt);
		}
	}
	
	
	
	return 0;
}

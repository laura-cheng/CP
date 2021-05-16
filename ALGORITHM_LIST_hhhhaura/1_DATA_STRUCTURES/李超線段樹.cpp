#define wiwihorz
#include <bits/stdc++.h>

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
		lld m, k; 
		int id, flag;
		ln() : m(0), k(0), id(-INF), flag(0) {}
		ln(lld _m, lld _k, int _id) {
			m = _m, k = _k, id = _id, flag = 1;
		}
		lld operator()(lld x) {
			if(!flag) return -INF;
			else return m * x + k;
		}
	};
	int n, p, root;
	vector<ln> seg;
	vector<int> lch, rch;
	void init_(int _n) {
		lch.assign(MAXN, 0);
		rch.assign(MAXN, 0);
		seg.assign(MAXN, ln());
		n = _n, p = 0, root = get_new();
	}
	int get_new() {
		return ++ p;
	}
	void insert(int nd, int L, int R, ln a) {
		if(L == R) {
			if(a(L) > seg[nd](L)) seg[nd] = a;
			return;
		}
		int mid = (L + R) / 2;
		
		if(a.m < seg[nd].m) swap(seg[nd], a);
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
	void modify(int nd, int L, int R, int l, int r, ln a) {
		if(l > R || r < L) return;
		else if(l <= L && r >= R) insert(nd, L, R, a);
		else {
		
			int mid = (L + R) / 2;
			if(!lch[nd]) lch[nd] = get_new();
			if(!rch[nd]) rch[nd] = get_new();
			modify(lch[nd], L, mid, l, r, a);
			modify(rch[nd], mid + 1, R, l, r, a);
		}
	}
	pair<double, int> query(int nd, int L, int R, int x) {
		if(!nd) return {-INF, INF};
		else if(L == R) return {seg[nd](x), -seg[nd].id};
		else {
			int mid = (L + R) / 2;
			pair<double, int> p = {seg[nd](x), -seg[nd].id};
			if(x <= mid) return max(query(lch[nd], L, mid, x), p);
			else return max(query(rch[nd], mid + 1, R, x), p); 
		}
	}
	void add(int x0, int y0, int x1, int y1, int id) {
		if(x0 > x1) swap(x0, x1), swap(y0, y1);
		if(x0 == x1) modify(root, 1, n, x0, x0, ln(0, max(y0, y1), id));
		else {
			lld m = (lld)(y1 - y0) / (lld)(x1 - x0);
			lld k = y0 - m * x0;
			modify(root, 1, n, x0, x1, ln(m, k, id));
		}
	}
	int ask(int x) {
		pair<double, int> p = query(root, 1, n, x);
		return max(0ll, -p.second);
	}

} st;
const int mod1 = 39989, mod2 = 1e9 + 1;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, last_ans = 0, cur = 0; 
	cin >> n;
	st.init_(mod1);
	rep(i, 1, n) {
		int op, a, b, c, d;
		cin >> op;
		if(op == 1) {
			cin >> a >> b >> c >> d;
			a = (a + last_ans - 1 + mod1) % mod1 + 1;
			b = (b + last_ans - 1 + mod2) % mod2 + 1;
			c = (c + last_ans - 1 + mod1) % mod1 + 1;
			d = (d + last_ans - 1 + mod2) % mod2 + 1;
			st.add(a, b, c, d, ++cur);
		}
		else {
			cin >> a;
			a = (a + last_ans - 1 + mod1) % mod1 + 1;
			last_ans = st.ask(a);
			cout << last_ans << "\n";
		}
	}
	return 0;
}  

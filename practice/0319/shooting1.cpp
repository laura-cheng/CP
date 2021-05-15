#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1)/ (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define MAXN 1000005
#define eps (1e-9)

//#define int long long int
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

struct segment_tree {
	int n;
	vector<set<int>> seg;
	void init_(int _n) {
		n = _n;
		seg.assign(2 * n + 1, set<int>());
		return;
	}
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	int query(int L, int R, int x) {
		int nd = get(L, R), mid = (L + R) / 2;
		if(L == R) {
			if(seg[nd].size()) return *prev(seg[nd].end());
			else return 0;
		}
		else {
			int cur = 0;
			if(seg[nd].size()) cur = max(*prev(seg[nd].end()), cur);
			if(x <= mid) cur = max(cur, query(L, mid, x));
			else cur = max(cur, query(mid + 1, R, x));
			return cur;
		}
	}
	void modify(int L, int R, int l, int r, int x) {
		int nd = get(L, R), mid = (L + R) / 2;
		if(l > R || r < L) return;
		else if(l <= L && r >= R) {
			if(x > 0) seg[nd].insert(x);
			else {
				auto it = seg[nd].find(-x);
				assert(it != seg[nd].end());
				seg[nd].erase(it);
			}
		}
		else {
			modify(L, mid, l, r, x);
			modify(mid + 1, R, l, r, x);
		}
		return;
	}
};
struct sb4 {
	int n, m;
	vector<int> s, t, w, v, qq;
	segment_tree st;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		s.assign(n + 1, 0);
		t.assign(n + 1, 0);
		w.assign(n + 1, 0);
		qq.assign(1, 0);
		v.clear();
	}
	void add_seg(int _s, int _t, int _w, int _id) {
		s[_id] = _s, t[_id] = _t, w[_id] = _w;
	}
	void add_query(int x) {
		qq.push_back(x);
	}
	void build() {
		rep(i, 1, n) {
			v.push_back(s[i]);
			v.push_back(t[i]);
		}
		rep(i, 1, m) {
			v.push_back(qq[i]);
		}
		sort(all(v));
		v.resize(unique(all(v)) - v.begin());
		st.init_(v.size() + 1);
		
		rep(i, 1, n) {
			s[i] = lower_bound(v.begin(), v.end(), s[i]) - v.begin() + 1;
			t[i] = lower_bound(v.begin(), v.end(), t[i]) - v.begin() + 1;
			st.modify(1, v.size(), s[i], t[i], i);
		}
		rep(i, 1, m) {
			qq[i] = lower_bound(v.begin(), v.end(), qq[i]) - v.begin() + 1;
		}
	}
	int solve() {
		build();
		int ans = 0;
		rep(i, 1, m) {
			int cur = st.query(1, v.size(), qq[i]);
			ans += w[cur];
			print(cur);
			st.modify(1, v.size(), s[cur], t[cur], -cur);
		}
		return ans;
	}

} ac;
namespace IO {
	const int size = 1e7 + 10;
	char buff[size];
	char *l, *r;
	inline void init() {
		l = buff;
		r = buff + fread(buff, 1, size, stdin);
	}
	inline char gc() {
		if(l == r) init();
		return (l != r) ? *(l++) : EOF;
	}
	void read(int &n) {
		n = 0; char c = gc();
		while(!isdigit(c)) c = gc();
		while(isdigit(c)) n = n * 10 + c - '0', c = gc();
	}
} using IO::read;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	ac.init_(n, m);
	rep(i, 1, n) {
		int s, t, w;
//		read(s), read(t), read(w);
		cin >> s >> t >> w;
		ac.add_seg(s, t, w, i);
	}
	rep(i, 1, m) {
		int x; 
		cin >> x;
		ac.add_query(x);
	}
	cout << ac.solve() << "\n";
	return 0;
}

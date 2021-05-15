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
namespace segment_tree {
	int n;
	vector<vector<int>> seg;
	vector<bool> vis;
	void init_(int _n, int _k) {
		n = _n;
		seg.assign(2 * n + 1, vector<int>());
		vis.assign(_k + 1, 0);
		return;
	}
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	int query(int L, int R, int x) {
		int nd = get(L, R), mid = (L + R) / 2;
		while(seg[nd].size() && vis[seg[nd].back()]) seg[nd].pop_back();
		if(L == R) {
			if(seg[nd].size()) return seg[nd].back();
			else return 0;
		}
		else {
			int cur = 0;
			if(seg[nd].size()) cur = max(seg[nd].back(), cur);
			if(x <= mid) cur = max(cur, query(L, mid, x));
			else cur = max(cur, query(mid + 1, R, x));
			return cur;
		}
	}
	void modify(int L, int R, int l, int r, int x) {
		int nd = get(L, R), mid = (L + R) / 2;
		if(l > R || r < L) return;
		else if(l <= L && r >= R) {
			seg[nd].push_back(x);
		}
		else {
			modify(L, mid, l, r, x);
			modify(mid + 1, R, l, r, x);
		}
		return;
	}
	void insert(int s, int t, int id) {
		modify(1, n, s, t, id);
	}
	int ask(int x) {
		int ans = query(1, n, x);
		vis[ans] = 1;
		return ans;
	}
};
namespace sb4 {
	int n, m;
	vector<int> s, t, w, v, qq;
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
		segment_tree::init_(v.size() + 1, n);
		rep(i, 1, n) {
			s[i] = lower_bound(v.begin(), v.end(), s[i]) - v.begin() + 1;
			t[i] = lower_bound(v.begin(), v.end(), t[i]) - v.begin() + 1;
			segment_tree::insert(s[i], t[i], i);
		}
		rep(i, 1, m) {
			qq[i] = lower_bound(v.begin(), v.end(), qq[i]) - v.begin() + 1;
		}
	}
	int solve() {
		build();
		int ans = 0;
		rep(i, 1, m) {
			int cur = segment_tree::ask(qq[i]);
			ans += w[cur];
		}
		return ans;
	}

};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	sb4::init_(n, m);
	rep(i, 1, n) {
		int s, t, w;
		cin >> s >> t >> w;
		sb4::add_seg(s, t, w, i);
	}
	rep(i, 1, m) {
		int x; cin >> x;
		sb4::add_query(x);
	}
	cout << sb4::solve() << "\n";
	return 0;
}

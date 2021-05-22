#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define all(x) x.begin(), x.end()
using namespace std;
#define lld long double
#define pii pair<int, int>
#define INF 1000000000
namespace utils {
	struct seg {
		int L, R;
		lld m, k;
		lld operator()(lld x) {
			return m*x + k;
		}	
	};
	struct ln {int x, L, R;};
	seg make_seg(pii a, pii b) {
		if(a.first > b.first) swap(a, b);
		lld m = (lld)(b.second - a.second) / (b.first - a.first);
		lld k = a.second - a.first * m;
		return {a.first, b.first, m, k};
	}
	bool comp(seg a, seg b) {
		int L = max(a.L, b.L);
		int R = min(a.R, b.R);
		lld mid = (lld)(L + R) / 2;
		assert(R >= L);
		return a(mid) < b(mid);
	}
	vector<int> ans, cnt;
	vector<pii> pts;
};
using namespace utils;
namespace AA {
	vector<seg> segs, val;
	vector<int> pri, lch, rch, sz;
	int p, root;
	const int MAXN = 2500;
	const lld eps = 1e-9;
	int get_new(seg v) {
		p ++;
		val[p] = v;
		sz[p] = 1;
		pri[p] = rand();
		return p;
	}
	void pull(int nd) {
		sz[nd] = sz[lch[nd]] + sz[rch[nd]] + 1; 
	}
	pii split(int nd, seg s) {
		if(!nd) return {0, 0};
		else if(comp(val[nd], s)) {
			pii p = split(rch[nd], s);
			rch[nd] = p.first;
			pull(nd);
			return {nd, p.second};
		}
		else {
			pii p = split(lch[nd], s);
			lch[nd] = p.second;
			pull(nd);
			return {p.first, nd};
		}
	}
	pii split(int nd, int k) {
		if(!nd) return {0, 0};
		else if(sz[lch[nd]] + 1 <= k) {
			pii p = split(rch[nd], k - sz[lch[nd]] - 1);
			rch[nd] = p.first;
			pull(nd);
			return {nd, p.second};
		}
		else {
			pii p = split(lch[nd], k);
			lch[nd] = p.second;
			pull(nd);
			return {p.first, nd};
		}
	}
	int merge(int pre, int suf) {
		if(!pre) return suf;
		if(!suf) return pre;
		if(pri[pre] > pri[suf]) {
			rch[pre] = merge(rch[pre], suf);
			pull(pre);
			return pre;			
		}
		else {
			lch[suf] = merge(pre, lch[suf]);
			pull(suf);
			return suf;
		}
	}
	void insert(seg s) {
		int cur = get_new(s);
		pii p = split(root, s);
		root = merge(merge(p.first, cur), p.second);
	}
	void erase(seg s) {
		pii p = split(root, s);
		pii p1 = split(p.second, 1);
		root = merge(p.first, p1.second);
	}
	int search(int nd, pii a) {
		if(!nd) return 0;
		if(abs(val[nd](a.first) - a.second) <= eps) return INF;
		else if(val[nd](a.first) > a.second) 
			return min(INF, 1 + sz[rch[nd]] + search(lch[nd], a));
		else return min(search(rch[nd], a), INF);
	}
	struct query {
		int x, tp, id;
		bool operator<(query b) {
			if(x != b.x) return x < b.x;
			else return tp < b.tp; // 0 is erase
		}
	};
	vector<query> qq;
	void solve() {
		p = 0, root = 0;
		val.assign(MAXN, {0, 0, 0, 0});
		pri.assign(MAXN, 0);
		lch.assign(MAXN, 0);
		rch.assign(MAXN, 0);
		sz.assign(MAXN, 0);
		rep(i, 0, signed(pts.size()) - 1) {
			qq.push_back({pts[i].first, 3, i});
		}
		rep(i, 0, signed(segs.size()) - 1) {
			qq.push_back({segs[i].L, 1, i});
			qq.push_back({segs[i].R, 0, i});
		}
		sort(all(qq));
		for(auto i : qq) {
			if(i.tp == 0) erase(segs[i.id]);
			else if(i.tp == 1) insert(segs[i.id]);
			else cnt[i.id] = search(root, pts[i.id]);
		}
	}
};
namespace BB {
	vector<ln> lns;
	struct query {
		int x, tp, id;
		bool operator<(query b) {
			if(x != b.x) return x < b.x;
			else return tp < b.tp;
		}
	};	
	vector<query> qq;
	void solve() {
		rep(i, 0, signed(lns.size()) - 1) {
			qq.push_back({lns[i].x, 2, i});
		}
		rep(i, 0, signed(pts.size()) - 1) {
			qq.push_back({pts[i].first, 1, i});
			qq.push_back({pts[i].first + 1, 0, i});
		}
		sort(all(qq));
		multiset<pii> mp;
		for(auto i : qq) {
			if(i.tp == 0) mp.erase(mp.find({pts[i.id].second, i.id}));
			else if(i.tp == 1) mp.insert({pts[i.id].second, i.id});
			else {
				auto it = mp.lower_bound({lns[i.id].L, -INF});
				for(; it != mp.end() && it -> first 
					<= lns[i.id].R; it = next(it)) {
					ans[it -> second] = 1;
				}
			}			
		}
		qq.clear();
		mp.clear();
	}
};
namespace solver {
	int n, m;
	vector<pii> a;
	set<pii> s;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		a.assign(n, {0, 0});
		pts.assign(m, {0, 0});
		ans.assign(m, 0);
		cnt.assign(m, 0);		
	}
	int solve() {
		rep(i, 0, n - 1) {
			s.insert(a[i]);
			pii L = a[i], R = a[(i + 1) % n];
			if(L.first == R.first) BB::lns.push_back({
				L.first, min(L.second, R.second), max(L.second, R.second)});
			else AA::segs.push_back(make_seg(L, R));
		}
		AA::solve();
		BB::solve();
		int vv = 0;
		rep(i, 0, m - 1) vv += bool(ans[i] || (cnt[i] & 1) || cnt[i] == INF || s.find(pts[i]) != s.end());
		return vv;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n, m);
	rep(i, 0, n - 1) cin >> a[i].first >> a[i].second;
	rep(i, 0, m - 1) cin >> pts[i].first >> pts[i].second;
	cout << solve() << "\n";
	return 0;
}

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
#define ll long long 
#define int long long 
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace mo {
	const int k1 = 320, k2 = 100000, k3 = 32000000;
	int disc, ii, n, op;
	vector<int> a1, a2, mx, cnt;
	vector<int> b1, b2, b3, big_id;
	vector<ll> b4, sum, av1, bv1, bv2;
	stack<vector<pair<int*, int>>> st;
	void init_(int _n) {
		n = _n, op = 0, ii = 0, disc = 0;
		a1.assign(ceil(k2, k1) + 1, 0);
		av1.assign(ceil(k2, k1) + 1, 0);
		a2.assign(k2 + 1, 0);
		mx.assign(k2 + 1, 0);
		cnt.assign(k2 + 1, 0);
		sum.assign(k2 + 1, 0);
		big_id.assign(k2 + 1, 0);
		b1.assign(ceil(k3, k2) + 1, 0);
		bv1.assign(ceil(k3, k2) + 1, 0);
		b2.assign(ceil(k3, k1) + 1, 0);
		bv2.assign(ceil(k3, k1) + 1, 0);
		b3.assign(k3 + 1, 0);
		b4.assign(k1 + 10, 0);
	}
	void save_cur(int a, int w) {
		int ww = min(w, mx[a]);
		vector<pair<int*, int>> cur;
		cur.push_back({&mx[a], mx[a]});
		cur.push_back({&a1[ceil(w, k1)], a1[ceil(w, k1)]});
		cur.push_back({&a2[w], a2[w]});
		cur.push_back({&av1[ceil(w, k1)], av1[ceil(w, k1)]});
		ll i = sum[a], j = sum[a] + w;
		if(i <= k3) {
			cur.push_back({&b1[ceil(i, k2)], b1[ceil(i, k2)]});
			cur.push_back({&b2[ceil(i, k1)], b2[ceil(i, k1)]});
			cur.push_back({&b3[i], b3[i]});
			cur.push_back({&bv1[ceil(i, k2)], bv1[ceil(i, k2)]});
			cur.push_back({&bv2[ceil(i, k1)], bv2[ceil(i, k1)]});
		}
		if(j <= k3) {
			cur.push_back({&b1[ceil(j, k2)], b1[ceil(j, k2)]});
			cur.push_back({&b2[ceil(j, k1)], b2[ceil(j, k1)]});
			cur.push_back({&b3[j], b3[j]});
			cur.push_back({&bv1[ceil(j, k2)], bv1[ceil(j, k2)]});
			cur.push_back({&bv2[ceil(j, k1)], bv2[ceil(j, k1)]});
		}
		cur.push_back({&big_id[a], big_id[a]});
		cur.push_back({&b4[big_id[a]], b4[big_id[a]]});
		cur.push_back({&disc, disc});
		cur.push_back({&ii, ii});
		cur.push_back({&cnt[a], cnt[a]});
		cur.push_back({&sum[a], sum[a]});
		st.push(cur);
		op ++;
	}
	void add(int a, int w) {
		save_cur(a, w);
		cnt[a] ++, disc += bool(cnt[a] == 1);
		ll ww = w;
		if(ww > mx[a]) {
			ll tp = mx[a];
			mx[a] = ww, ww = tp;
		}
		a1[ceil(ww, k1)] ++;
		av1[ceil(ww, k1)] += ww;
		a2[ww] ++;
		
		ll v = sum[a] + w;
		// delete initial
		if(sum[a] <= k3) {
			b1[ceil(sum[a], k2)] --;
			bv1[ceil(sum[a], k2)] -= sum[a];
			b2[ceil(sum[a], k1)] --;
			bv2[ceil(sum[a], k1)] -= sum[a];
			b3[sum[a]] --;
		}
		sum[a] = v;
		if(v > k3) {
			if(!big_id[a]) big_id[a] = ++ii;
			b4[big_id[a]] = v;
		}
		else {
			b1[ceil(v, k2)] ++;
			bv1[ceil(v, k2)] += v;
			b2[ceil(v, k1)] ++;
			bv2[ceil(v, k1)] += v;
			b3[v] ++;
		}	
	}
	void undo() {
		op --;
		vector<pair<int*, int>> cur = st.top();
		st.pop();
		for(auto i : cur) *i.first = i.second;
		return;
	}
	ll solve1(int x) {
		ll ans = 0, aa = 0, bb = 0;
		while(aa + 1 < a1.size() && x > a1[aa + 1]) {
			aa++;
			ans += av1[aa];
			x -= a1[aa];
		}
		bb = aa * k1;
		while(bb + 1 < a2.size() && x > 0) {
			bb ++;
			ans += min(x, a2[bb]) * bb;
			x -= min(x, a2[bb]);
		}
		assert(x == 0);
		return ans;
	}
	ll solve2(int x) {
		ll ans = 0, aa = 0, bb = 0, cc = 0;
		while(aa + 1 < b1.size() && x > b1[aa + 1]) {
			aa++;
			ans += bv1[aa];
			x -= b1[aa];
		}
		bb = aa * k2;
		while(bb + 1 < b2.size() && x > b2[bb + 1]) {
			bb++;
			ans += bv2[bb];
			x -= b2[bb];
		}
		cc = bb * k1;
		while(cc + 1 < b3.size() && x > 0) {
			cc ++;
			ans += min(x, b3[cc]) * cc;
			x -= min(x, b3[cc]);
		}
		if(x > 0) {
			nth_element(b4.begin() + 1, b4.begin() + x, b4.begin() + ii + 1);
			ll cur = b4[x], cnt = 0;
			rep(i, 1, ii) if(b4[i] < cur) {
				ans += b4[i];
				cnt ++;
			}
			ans += (x - cnt) * cur;
		}
		return ans;
	}
};
namespace solver {
	int n, q, bk;
	struct query {
		int l, r, bid, a, b, id;
		bool operator<(query b) {
			if(bid != b.bid) return bid < b.bid;
			return r < b.r;
		}
	};
	vector<query> qq;
	vector<int> a, w;
	vector<ll> ans;
	void init_(int _n, int _q) {
		n = _n, q = _q, bk = 350;
		mo::init_(n);
		a.assign(n + 1, 0);
		w.assign(n + 1, 0);
		qq.clear();
		ans.assign(q + 1, 0);
	}
	void solve() {
		sort(all(qq));
		int cur = 1, r = bk, pre;
		for(auto i : qq) {
			if(cur != i.bid) {
				while(mo::op) mo::undo();
				cur = i.bid, r = bk * cur;
			}
			if(i.r <= bk * cur) {
				pre = mo::op;
				rep(j, i.l, i.r) mo::add(a[j], w[j]);
			}
			else {
				while(i.r > r) ++r, mo::add(a[r], w[r]);
				pre = mo::op;
				rrep(j, i.l, cur * bk) mo::add(a[j], w[j]);
			}
			if(mo::disc > i.b) ans[i.id] = mo::solve2(mo::disc - i.b);
			else if(mo::disc < i.a) ans[i.id] = mo::solve1(i.a - mo::disc);
			while(mo::op != pre) mo::undo();
		}
		return;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q; cin >> n >> q;
	init_(n, q);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> w[i];
	rep(i, 1, q) {
		int l, r, a, b;
		cin >> l >> r >> a >> b;
		qq.push_back({l, r, ceil(l, bk), a, b, i});
	}
	solve();
	rep(i, 1, q) cout << ans[i] << "\n";
	return 0;
}

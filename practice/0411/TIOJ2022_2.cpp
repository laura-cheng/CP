#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimze("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define ll long long int
#define int long long int
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

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
namespace solver {
	int n, q, bk, op;
	const int k1 = 320;
	const int k2 = 100000;
	const int k3 = 32000000;
	vector<int> a, w, a1, a2;
	vector<int> b1, b2, b3, cnt, in_big;
	vector<ll> av1, bv1, bv2, ans, sum, b4;
	int disc, l, r;
	struct query {
		int l, r, bid, id, a, b;
		bool operator<(query b) {
			if(bid != b.bid) return bid < b.id;
			else return r < b.r;
		}
	};
	vector<query> qq;
	void init_(int _n, int _q) {
		n = _n, q = _q;
		bk = pow(n, 0.5) + 1;
		ans.assign(q + 1, 0);
		a.assign(k2 + 1, 0);
		sum.assign(k2 + 1, 0);
		in_big.assign(k2 + 1, -1);
		w.assign(n + 1, 0);
		a1.assign(ceil(100000, k1) + 1, 0);
		av1.assign(ceil(100000, k1) + 1, 0);
		a2.assign(100000 + 1, 0);
		b1.assign(ceil(k3, k2) + 1, 0);
		bv1.assign(ceil(k3, k2) + 1, 0);
		b2.assign(ceil(k3, k1) + 1, 0);
		bv2.assign(ceil(k3, k1) + 1, 0);
		b3.assign(k3 + 1, 0);
		b4.clear();
		cnt.assign(n + 1, 0);
		disc = 0, l = 0, r = 0;
		return;
	}
	void add(int a, int w) {
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
	void del(int x) {
		cnt[a[x]] --;
		if(cnt[a[x]] >= 1) {
			a2[w[x]] --;
			a1[ceil(w[x], k1)] --;
			av1[ceil(w[x], k1)] -= w[x];
		}
		else disc--;
		ll val = sum[a[x]] - w[x];
		if(in_big[a[x]] != -1) {
			if(val <= k3) b4.pop_back(), in_big[a[x]] = -1; 
			else b4[in_big[a[x]]] = val;
		}
		else {
			ll val = sum[a[x]];
			b1[ceil(sum[a[x]], k2)] --;
			b3[sum[a[x]]] --, b2[ceil(sum[a[x]], k1)] --;
			bv1[ceil(val, k2)] -= val;
			bv2[ceil(val, k1)] -= val;
		}
		sum[a[x]] = val;
		if(in_big[a[x]] == -1) {
			b1[ceil(val, k2)] ++;
			b3[val] ++, b2[ceil(val, k1)] ++;
			bv1[ceil(val, k2)] += val;
			bv2[ceil(val, k1)] += val;
		}	
		
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
	void solve() {
		sort(all(qq));
		l = bk + 1, r = bk, disc = 0;
		int cur = 1;
		for(auto i : qq) {
			if(i.bid != cur) {
				while(r >= l) del(r--);
				cur = i.bid;
				l = i.bid * bk + 1, r = l - 1;
			}
			while(r < i.r) add(++r);
			while(l > i.l) add(--l);
			if(disc > i.b) ans[i.id] = solve2(disc - i.b);
			else if(disc < i.a) ans[i.id] = solve1(i.a - disc);
			while(l != cur * bk + 1) del(l++);
		}
	}
};
/*
6 4
3 2 3 1 4 2
2000 40000 3000 100000 2000 20000
1 6 1 3
1 6 4 4
1 6 5 6
2 5 1 1
*/
namespace solver2 {
vector<int> a, w, a1, a2;
	vector<int> b1, b2, b3, cnt, in_big;
	vector<ll> av1, bv1, bv2, ans, sum, b4;

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
		qq.push_back({l, r, ceil(l, bk), i, a, b});
	}
	build(), solve();
	rep(i, 1, q) cout << ans[i] << "\n";

	
	return 0;
}

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

namespace mo1 {
	int disc, n, op;
	const int k2 = 100000;
	vector<int> cnt;
	void init_() {
		disc = 0;
		cnt.assign(k2 + 1, 0);
	}
	void add(int a, int w) {
		cnt[a] ++, disc += bool(cnt[a] == 1);
	}
	void minu(int a, int w) {
		cnt[a] --;
		if(cnt[a] == 0) disc --;
	}
};
namespace mo2 {
	const int k1 = 320, k2 = 100000, k3 = 32000000;
	int op;
	vector<int> a1, a2, mx;
	vector<ll> av1;
	stack<pair<int*, int>> st;
	stack<pair<ll*, ll>> st1;
	void init_() {
		op = 0;
		a1.assign(ceil(k2, k1) + 1, 0);
		av1.assign(ceil(k2, k1) + 1, 0);
		a2.assign(k2 + 1, 0);
		mx.assign(k2 + 1, 0);
	}
	void save_cur(int a, int w) {
		w = min(w, mx[a]);
		st.push({&mx[a], mx[a]});
		st.push({&a1[ceil(w, k1)], a1[ceil(w, k1)]});
		st.push({&a2[w], a2[w]});
		st1.push({&av1[ceil(w, k1)], av1[ceil(w, k1)]});
		op ++;
	}
	void add(int a, int w) {
		save_cur(a, w);
		if(w > mx[a]) swap(w, mx[a]);
		a1[ceil(w, k1)] ++;
		av1[ceil(w, k1)] += w;
		a2[w] ++;
	}
	void undo() {
		op --; 
		rep(i, 1, 3) {
			pair<int*, int> cur = st.top();
			st.pop(), *cur.first = cur.second;
		}
		rep(i, 1, 1) {
			pair<ll*, ll> cur = st1.top();
			st1.pop(), *cur.first = cur.second;
		}
	}
	ll solve(int x) {
		ll ans = 0, aa = 0, bb = 0;
		while(aa + 1 < a1.size() && x > a1[aa + 1]) {
			aa++, ans += av1[aa];
			x -= a1[aa];
		}
		bb = aa * k1;
		while(bb + 1 < a2.size() && x > 0) {
			bb ++, ans += (ll)min(x, a2[bb]) * bb;
			x -= min(x, a2[bb]);
		}
		return ans;
	}
};
namespace mo3 {
	const ll k1 = 320, k2 = 100160, k3 = 32000000;
	int ii;
	vector<int> b1, b2, b3, big_id, ids;
	vector<ll> b4, sum, bv1, bv2;
	void init_() {
		ii = 0;
		sum.assign(k2 + 1, 0);
		big_id.assign(k2 + 1, 0);
		b1.assign(ceil(k3, k2) + 1, 0);
		bv1.assign(ceil(k3, k2) + 1, 0);
		b2.assign(ceil(k3, k1) + 1, 0);
		bv2.assign(ceil(k3, k1) + 1, 0);
		b3.assign(k3 + 100, 0);
		b4.assign(k1 + 5, INF);
		rep(i, 0, k1) ids.push_back(i);
	}
	void add(int a, int w) {
		ll v = sum[a] + w;
		if(sum[a] <= k3 && sum[a] > 0) {
			b1[ceil(sum[a], k2)] --;
			bv1[ceil(sum[a], k2)] -= sum[a];
			b2[ceil(sum[a], k1)] --;
			bv2[ceil(sum[a], k1)] -= sum[a];
			b3[sum[a]] --;
		}
		sum[a] = v;
		if(v > k3) {
			if(!big_id[a]) big_id[a] = ids.back(), ids.pop_back();
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
	void minu(int a, int w) {
		ll v = sum[a] - w;
		if(sum[a] <= k3) {
			b1[ceil(sum[a], k2)] --;
			bv1[ceil(sum[a], k2)] -= sum[a];
			b2[ceil(sum[a], k1)] --;
			bv2[ceil(sum[a], k1)] -= sum[a];
			b3[sum[a]] --;
		}
		else {
			b4[big_id[a]] = v;
			if(v <= k3) {
				ids.push_back(big_id[a]);
				b4[big_id[a]] = INF;
				big_id[a] = 0;
			}
		}
		sum[a] = v;
		if(v <= k3 && v > 0) {
			b1[ceil(v, k2)] ++;
			bv1[ceil(v, k2)] += v;
			b2[ceil(v, k1)] ++;
			bv2[ceil(v, k1)] += v;
			b3[v] ++;
		}
	}
	ll solve(int x) {
		ll ans = 0, aa = 0, bb = 0, cc = 0;
		while(aa + 1 < b1.size() && x > b1[aa + 1]) {
			aa++, ans += bv1[aa];
			x -= b1[aa];
		}
		bb = aa * k2 / k1;
		while(bb + 1 < b2.size() && x > b2[bb + 1]) {
			bb++, ans += bv2[bb];
			x -= b2[bb];
		}
		cc = bb * k1;
		while(cc + 1 < b3.size() && x > 0) {
			cc ++, ans += min(x, b3[cc]) * cc;
			x -= min(x, b3[cc]);
		}
		if(x > 0) {
			vector<ll> temp = b4;
			nth_element(temp.begin(), temp.begin() + x - 1, temp.end());
			rep(i, 0, x - 1) ans += temp[i];
		}
		return ans;
	}
};
namespace solver {
	int n, q, bk;
	struct query {
		int l, r, bid, a, b, id, cnt;
		bool operator<(query b) {
			if(bid != b.bid) return bid < b.bid;
			return r < b.r;
		}
	};
	vector<query> qq, qq1, qq2;
	vector<int> a, w;
	vector<ll> ans;
	void init_(int _n, int _q) {
		n = _n, q = _q, bk = 350;
		mo1::init_();
		mo2::init_();
		mo3::init_();
		a.assign(n + 1, 0);
		w.assign(n + 1, 0);
		qq.clear();
		qq1.clear();
		qq2.clear();
		ans.assign(q + 1, 0);
	}
	void solve() {
		sort(all(qq));
		int cur, l, r, pre;
		l = 1, r = 0;
		for(auto i : qq) {
			while(l > i.l) l--, mo1::add(a[l], w[l]);
			while(r < i.r) r++, mo1::add(a[r], w[r]);
			while(l < i.l) mo1::minu(a[l], w[l]), l++;
			while(r > i.r) mo1::minu(a[r], w[r]), r--;
			if(mo1::disc > i.b) qq2.push_back({i.l, i.r, i.bid, i.a, i.b, i.id, mo1::disc - i.b});
			else if(mo1::disc < i.a) qq1.push_back({i.l, i.r, i.bid, i.a, i.b, i.id, i.a - mo1::disc});
		}
		cur = 1, r = bk, pre;
		for(auto i : qq1) {
			if(cur != i.bid) {
				while(mo2::op) mo2::undo();
				cur = i.bid, r = bk * cur;
			}
			if(i.r <= bk * cur) {
				pre = mo2::op;
				rep(j, i.l, i.r) mo2::add(a[j], w[j]);
			}
			else {
				while(i.r > r) ++r, mo2::add(a[r], w[r]);
				pre = mo2::op;
				rrep(j, i.l, cur * bk) mo2::add(a[j], w[j]);
			}
			ans[i.id] = mo2::solve(i.cnt);
			while(mo2::op != pre) mo2::undo();
		}
		cur = 1, l = 1, r = 0;
		for(auto i : qq2) {
			while(l > i.l) l--, mo3::add(a[l], w[l]);
			while(r < i.r) r++, mo3::add(a[r], w[r]);
			while(l < i.l) mo3::minu(a[l], w[l]), l++;
			while(r > i.r) mo3::minu(a[r], w[r]), r--;
			ans[i.id] = mo3::solve(i.cnt);
		}
		return;
	}
};
namespace io {
    const int SIZE = 1e7 + 10;
    char inbuff[SIZE];
    char *l, *r;
    inline void init() {
        l = inbuff;
        r = inbuff + fread(inbuff, 1, SIZE, stdin);
    }
    inline char gc() {
        if (l == r) init();
        return (l != r) ? *(l++) : EOF;
    }
    void read(int &x) {
        x = 0; char ch = gc();
        while(!isdigit(ch)) ch = gc();
        while(isdigit(ch)) x = x * 10 + ch - '0', ch = gc();
    }
} using io::read;
using namespace solver;
signed main() {
	int n, q; read(n), read(q);
	init_(n, q);
	rep(i, 1, n) read(a[i]);
	rep(i, 1, n) read(w[i]), assert(w[i] >= 0);
	rep(i, 1, q) {
		int l, r, a, b;
		read(l), read(r), read(a), read(b);
		qq.push_back({l, r, ceil(l, bk), a, b, i});
	}
	solve();
	rep(i, 1, q) printf("%lld\n", ans[i]);
	return 0;
}

#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loo-opt(on)

#define rep(i ,a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MAXN 1000005
#define eps (1e-9)

#define int unsigned
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
struct mat {
	int v[4][4];
	mat(int x = 0) {
		rep(i, 0, 3) rep(j, 0, 3) {
			v[i][j] = 0;
		}
		rep(i, 0, 3) v[i][i] = x;
	}
	mat operator*(mat b) {
		mat ans = mat();
		rep(i, 0, 3) rep(j, 0, 3) {
			rep(k, 0, 3) {
				ans.v[i][j] = (ans.v[i][j] + v[i][k] * b.v[k][j]);
			}
		}
		return ans;
	}
};
struct ans {
		int v[4];
		ans() {rep(i, 0, 3) v[i] = 0;}
		ans operator+(ans b) {
			ans a = ans();
			rep(i, 0, 3) a.v[i] = (v[i] + b.v[i]);
			return a;
		}
};
struct AC {
	int n, w;
	vector<mat> tag;
	vector<ans> seg, a;
	void init_(int _n, int _w) {
		n = _n, w = _w;
		tag.assign(2 * w + 1, mat(1));
		seg.assign(2 * w + 1, ans());
		a.assign(w + 1, ans());
		return;
	}
	int get(int L, int R) {
		return (L + R) | (L != R); 
	}
	int ask(int L, int R, int t) {
		ans aa = query(0, w - 1, L, R);
		return aa.v[t];
	}
	void copy(int L, int R, int t1, int t2) {
		mat x = mat(1);
		x.v[t2][t2] = 0, x.v[t1][t2] = 1;
		modify1(0, w - 1, L, R, x);
	}
	void MO(int L, int R, int t, int p1, int p2) {
		mat x = mat(1);
		x.v[t][t] = p1, x.v[3][t] = p2; 
		modify1(0, w - 1, L, R, x);
	}
	void AM(int L, int R, int t1, int t2, int p) {
		mat x = mat(1);
		x.v[t1][t2] = p;
		modify1(0, w - 1, L, R, x);
	}
	int sswap(int L, int R, int t1, int t2) {
		mat x = mat(1);
		x.v[t1][t1] = 0, x.v[t2][t1] = 1;
		x.v[t2][t2] = 0, x.v[t1][t2] = 1;
		modify1(0, w - 1, L, R, x);
	}
	ans query(int L, int R, int l, int r) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return ans();
		push(L, R);
		if(l <= L && r >= R) {
			return seg[nd];
		}
		else {
			ans aa = query(L, mid, l, r);
			ans bb = query(mid + 1, R, l, r);
			return aa + bb;
		}
	}
	ans ddo(ans x, mat tg) {
		ans y = ans();
		rep(i, 0, 3) {
			rep(j, 0, 3) {
				y.v[i] += x.v[j] * tg.v[j][i];
			}
		}
		return y;
	}
	void modify1(int L, int R, int l, int r, mat a) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return;
		push(L, R);
		if(l <= L && r >= R) tag[nd] = tag[nd] * a;
		else {
			modify1(L, mid, l, r, a);
			modify1(mid + 1, R, l, r, a);
			pull(L, R);
		}
	}
	void pull(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int lch = get(L, mid), rch = get(mid + 1, R);
		ans cur = ddo(seg[lch], tag[lch]) + ddo(seg[rch], tag[rch]);
		seg[nd] = cur;
	}
	void push(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int lch = get(L, mid), rch = get(mid + 1, R);
		seg[nd] = ddo(seg[nd], tag[nd]);
		if(L == R) {
			tag[nd] = mat(1);
			return;
		}
		tag[lch] = tag[lch] * tag[nd];
		tag[rch] = tag[rch] * tag[nd];
		tag[nd] = mat(1);
		return;
	}
	void build(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) seg[nd] = a[L];
		else {
			build(L, mid);
			build(mid + 1, R);
			pull(L, R);
		}
		return;
	}
} ac;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, w, q; cin >> n >> w >> q;
	ac.init_(n, w);
	rep(i, 0, w - 1) {
		ac.a[i] = ans();
		rep(j, 0, n - 1) cin >> ac.a[i].v[j];
		ac.a[i].v[3] = 1;
	} 
	ac.build(0, w - 1);
	rep(i, 1, q) {
		char x; int a, b, c, d, e;
		cin >> x;
		if(x == 'Q') {
			cin >> a >> b >> c;
			cout << ac.ask(a, b, c) << "\n";
		}
		else if(x == 'C') {
			cin >> a >> b >> c >> d;
			ac.copy(a, b, c, d);
		}
		else if(x == 'M') {
			cin >> a >> b >> c >> d >> e;
			ac.MO(a, b, c, d, e);
		}
		else if(x == 'A') {
			cin >> a >> b >> c >> d >> e;
			ac.AM(a, b, c, d, e);
		}
		else {
			cin >> a >> b >> c >> d;
			ac.sswap(a, b, c, d);
		}
//		ans aa = ac.seg[ac.get(0, 0)];
//		mat bb = ac.tag[ac.get(0, 0)];
//		print(aa.v[0], aa.v[1], aa.v[2]);
//		rep(i, 0, 3) rep(j, 0, 3) {
//			cerr << bb.v[i][j] << " \n"[j == 3];
//		}
	}
	return 0;
}

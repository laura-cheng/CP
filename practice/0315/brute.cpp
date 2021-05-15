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
#define MOD  4294967296 
#define eps (1e-9)

#define int unsigned int
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
struct ans {
		int v[4];
		ans() {rep(i, 0, 3) v[i] = 0;}
};
struct AC {
	int n, w;
	vector<ans> a;
	void init_(int _n, int _w) {
		n = _n, w = _w;
		a.assign(w + 1, ans());
		return;
	}
	int ask(int L, int R, int t) {
		int ans = 0;
		rep(i, L, R) {
			ans += a[i].v[t];
		}
		return ans;
	}
	void copy(int L, int R, int t1, int t2) {
		rep(i, L, R) {
			a[i].v[t2] = a[i].v[t1];
		}
	}
	void MO(int L, int R, int t, int p1, int p2) {
		rep(i, L, R) {
			a[i].v[t] = (a[i].v[t] *p1+ p2);
		}
		return;
	}
	void AM(int L, int R, int t1, int t2, int p) {
		rep(i, L, R) {
			a[i].v[t2] = (a[i].v[t2] + a[i].v[t1] * p);
		}
	}
	int sswap(int L, int R, int t1, int t2) {
		rep(i, L, R) swap(a[i].v[t1], a[i].v[t2]);
	}
} ac;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, w, q; cin >> n >> w >> q;
	ac.init_(n, w);
	rep(i, 0, w - 1) {
		ac.a[i] = ans();
		rep(j, 0, n - 1) cin >> ac.a[i].v[j];
	} 
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
	
	}
	return 0;
}

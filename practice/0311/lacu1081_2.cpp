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
struct sub3 {
	int n, A, B, lg;
	struct edge {
		int to, cost;
	};
	vector<edge> esa, esb;
	vector<int> h;
	vector<vector<int>>v1, v2, to;
	void init_(int _n) {
		n = _n, lg = 31 - __builtin_clz(n);
		h.assign(n + 1, INF);
		esa.assign(n + 1, {0, 0});
		esb.assign(n + 1, {0, 0});
		v1.assign(lg + 1, vector<int>(n + 1, 0));
		v2.assign(lg + 1, vector<int>(n + 1, 0));
		to.assign(lg + 1, vector<int>(n + 1, 0));
	}
	void update(pii &a, pii &b) {
		if(a.first > b.first) swap(a, b);
	}
	void build() {
		set<pii> s;
		rrep(i, 1, n) {
			auto it = s.lower_bound({h[i], 0});
			auto cur = it;
			pii a = {INF, 0}, b = {INF, 0}, c;
			rep(j, 0, 1) {
				if(cur != s.begin()) {
					cur = prev(cur);
					c = {abs(cur -> first - h[i]), cur -> second};
					update(a, c);
					update(b, c);
				}
			}
			cur = it;
			rep(j, 0, 1) {
				if(cur != s.end()) {
					c = {abs(cur -> first - h[i]), cur -> second};
					update(a, c);
					update(b, c);
				}
				if(cur != s.end()) cur = next(cur);
			}
			if(a.first != INF) esa[i] = {a.second, a.first};
			if(b.first != INF) esb[i] = {b.second, b.first};
//			print(i, esa[i].to, esa[i].cost, esb[i].to, esb[i].cost);
			s.insert({h[i], i});
		}
	}
	void build1() {
		rep(i, 1, n) {
			v1[0][i] = esb[i].cost;
			to[0][i] = esb[i].to;
		} 
		rep(i, 1, n) {
			v1[1][i] = v1[0][i];
			v2[1][i] = esa[to[0][i]].cost;
			to[1][i] = esa[to[0][i]].to;
		}
		rep(i, 2, lg) rep(j, 1, n) {
			v1[i][j] = v1[i - 1][j] + v1[i - 1][to[i - 1][j]];
			v2[i][j] = v2[i - 1][j] + v2[i - 1][to[i - 1][j]];
			to[i][j] = to[i - 1][to[i - 1][j]];
		}
/*		rep(i, 0, lg) {
			print(lg);
			vprint(all(to[i]));
			vprint(all(v1[i]));
			vprint(all(v2[i]));
			
		}
*/
		return;
	}
/*	void go(int s, int x) {
		A = 0, B = 0;
		int cur = s;
		for(int i = 1; i; i ++) {
			if(!(i & 1)) {
				if(esa[cur].to == 0 || A + B + esa[cur].cost > x) return;
				else A += esa[cur].cost, cur = esa[cur].to;
			}
			else {
				if(esb[cur].to == 0 || A + B + esb[cur].cost > x) return;
				else B += esb[cur].cost, cur = esb[cur].to;
			}
		}
		return;
	}
*/
	void go(int s, int x) {
		A = 0, B = 0;
		rrep(i, 0, lg) {
			if(A + B + v1[i][s] + v2[i][s] <= x) {
//				print(i, s);
				B += v1[i][s];
				A += v2[i][s];
				s = to[i][s];
				
			}
		}
		return;
	}
	int solve1(int x) {
		int aa = 0, bb = 1, id = 0;
		rrep(i, 1, n) {
			go(i, x);
			if(bb * A == aa 
			* B && h[id] < h[i]) id = i;
			else if(bb * A > aa * B) id = i, aa = A, bb = B; 
		}
		return id;
	}
}a;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	a.init_(n);
	rep(i, 1, n) cin >> a.h[i];
	a.build(), a.build1();
	int x; cin >> x;
	cout << a.solve1(x) << "\n";
	int m; cin >> m;
	rep(i, 1, m) {
		int s, x; cin >> s >> x;
		a.go(s, x);
		cout << a.B << " " << a.A << "\n";
	}
	return 0;
} 

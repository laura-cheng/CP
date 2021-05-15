#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 10000000000000000000
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
struct prime {
	int n;
	vector<int> p, fac, c;
	void build(int _n) {
		n = _n, p.clear();
		fac.assign(n + 1, 1);
		c.assign(n + 1, 0);
		rep(i, 2, n) {
			if(fac[i] == 1) c[i] = 1, p.push_back(i);
			for(auto j : p) {
				if(i * j > n) break;
				fac[i * j] = j;
				c[i * j] = c[i] + 1;
				if(i % j == 0) {
					c[i * j] --;
					break;
				}
			}
		}
	}
	int cnt(int x) {
		return 1 << c[x]; 
	}
} ;
struct AC {
	prime pm;
	void init_() {
		pm.build(2e7);
	}
	int solve(int c, int d, int x) {
		int ans = 0;
		int k = sqrt(x);
		vector<int> all;
		rep(i, 1, k) {
			if(x % i) continue;
			all.push_back(i);
			if(i != x / i) all.push_back(x / i);
		}
		for(auto i : all) {
			int y = x / i;
			if((i + d) % c) continue;
			int k = (i + d) / c;
			ans += pm.cnt(k);
		}
		return ans;
	}


} ac;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	ac.init_();
	while(t--) {
		int c, d, x; 
		cin >> c >> d >> x;
		cout << ac.solve(c, d, x) << "\n";
	}
	
	return 0;
}

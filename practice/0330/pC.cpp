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
#define eps (1e-9)
#define MAXN 1000005

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
void solve(vector<pii> a, int n) {
	sort(all(a));
	int l = 1, r = n; bool start = 0;
	while(l <= r) {
		int mx = r - l;
		rep(i, 1, min(a[l].first - start, mx)) {
			cout << a[r].second << " ";
			r --;
		}
		cout << a[l].second << " \n"[l == r];
		l ++, start = 1;
		 
	}
	return;
	
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n; cin >> n;
		vector<pii> a(n + 1, {0, 0});
		rep(i, 1, n) {
			int x; cin >> x;
			a[i] = {x, i};
		}
		solve(a, n);
	}
	return 0;
}

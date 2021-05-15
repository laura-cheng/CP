#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a ,b) ((a + b - 1) / (b))

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
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
void solve_big(vector<int> a, int n) {
	set<int> s;
	rep(i, 1, n) s.insert(i);
	rep(i, 1, n) {
		if(s.find(a[i]) != s.end()) {
			cout << a[i] << " \n"[i == n];
			s.erase(s.find(a[i]));
		}
		else {
			auto it = prev(s.lower_bound(a[i]));
			cout << *it << " \n"[i == n];
			s.erase(it);
		}
	}
	return;
}
void solve_small(vector<int> a, int n) {
	set<int> s;
	rep(i, 1, n) s.insert(i);
	rep(i, 1, n) {
		if(s.find(a[i]) != s.end()) {
			cout << a[i] << " \n"[i == n];
			s.erase(s.find(a[i]));
		}
		else {
			auto it = s.begin();
			cout << *it << " \n"[i == n];
			s.erase(it);
			
		}
	}
	return;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n; cin >> n;
		vector<int> a(n + 1, 0);
		rep(i, 1, n) cin >> a[i];
		solve_small(a, n);
		solve_big(a, n);
	}
	return 0;
}


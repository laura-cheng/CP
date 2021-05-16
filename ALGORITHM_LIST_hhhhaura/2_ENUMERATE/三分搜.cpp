#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MOD 1000000007
#define MAXN 1000005
#define INF 1000000000000000000
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
int n;
vector<int> a, b;
lld check(lld x) {
	lld mx = -INF;
	rep(i, 1, n) {
		mx = max(mx, a[i] * x + b[i]);
	}
	return mx;
}
pair<lld, lld> solve() {
	lld l = 0, r = INF;
	rep(i, 1, 200) {
		lld v = (r - l) / 3;
		if(check(l + v) > check(r - v)) l = l + v;
		else r = r - v;
	}
	return {l, max((long double)0.0, check(l))};
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	while(cin >> n && n) {
		a.assign(n + 1, 0);
		b.assign(n + 1, 0);
		rep(i, 1, n) cin >> a[i] >> b[i];
		pair<lld, lld> ans = solve();
		if(ans.second == 0) cout << "0\n";
		else cout << fixed << setprecision(3) << 
			ans.second << " " << ans.first << "\n";
	}	
	return 0;
}

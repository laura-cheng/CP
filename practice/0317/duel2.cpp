#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

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
void vprint(auto L, auto R) {
	while(L < R) cerr << *L << " \n"[next(L) == R], ++ L;
}
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct AC {
	int n, m, h;
	vector<int> a, s1, s2;
	void init_(int _n, int _m) {
		n = _n, m = _m, h = ceil(n, 2);
		a.assign(n + 2, 0);
	}
	int cal(int x, int y) {
		int ans = 0;
		rep(i, 0, h - 1) if((x >> i) & 1) {
			ans += a[y + i];
		}
		return ans % m;
	}
	int solve() {
		rep(i, 0, (1 << h) - 1) {
			s1.push_back(cal(i, 1));
			s2.push_back(cal(i, h + 1));
		}
		sort(all(s1)), sort(all(s2));
		int ans = 0;
		for(auto i : s1) {
			int id = lower_bound(s2.begin(), s2.end(), m - i) - s2.begin() - 1;
			if(id >= 0) ans = max(ans, i + s2[id]);
			ans = max(ans, (s2.back() + i) % m);
		}
		return ans;
	}

} ac;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	ac.init_(n, m);
	rep(i, 1, n) cin >> ac.a[i];
	cout << ac.solve() << "\n";
	
	return 0;
}



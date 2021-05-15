#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a ; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
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
void kout() { cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace SOLVE {
	int n, k, X, A, Y, B;
	vector<int> a;
	void init_(int _n) {
		n = _n; 
		a.assign(n, 0);
	}
	bool check(int x) {
		int C = A * B / __gcd(A, B);
		int ii = 0, ans = 0;
		rep(i, 1, x / C) {
			ans += a[ii ++] / 100 * (X + Y);
		}
		for(int i = A; i <= x; i += A) {
			if(i % B == 0) continue;
			ans += a[ii++] / 100 * X;
		} 
		for(int i = B; i <= x; i += B) {
			if(i % A == 0) continue;
			ans += a[ii ++] / 100 * Y;
		}
		return ans >= k;
	} 
	int solve() {
		int l = 0, r = n + 1;
		if(X < Y) swap(X, Y), swap(A, B);
		sort(all(a)), reverse(all(a));
		while(r - l > 1) {
			int mid = (l + r) / 2;
			if(check(mid)) r = mid;
			else l = mid;
		}
		if(r == n + 1) return -1;
		else return r;
	}


};
using namespace SOLVE;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		cin >> n, init_(n);
		rep(i, 0, n - 1) cin >> a[i];
		cin >> X >> A >> Y >> B >> k;
		cout << solve() << "\n";
	}
	return 0;
}

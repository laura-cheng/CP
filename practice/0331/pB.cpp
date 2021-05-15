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
	int n, k, h;
	vector<int> a, pre;
	void init_(int _n, int _k) {
		n = _n, k = _k, h = ceil(n, 2);
		a.assign(n + 1, 0);
		pre.assign(n + 1, 0);
	}
	int check(int x) {
		int id = lower_bound(a.begin(), a.end(), x) - a.begin() - 1;
		int kk = (id - h + 1) * x - pre[id] + pre[h - 1];
		return kk;
	}
	int solve() {
		sort(all(a));
		rep(i, 1, n) pre[i] = pre[i - 1] + a[i];
		int l = a[ceil(n, 2)], r = 1e9 + 1;
		while(r - l > 1) {
			int mid = (l + r) / 2;
			if(check(mid) <= k) l = mid;
			else r = mid;
		}
		return l;
	}
};
using namespace SOLVE;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	init_(n, k);
	rep(i, 1, n) cin >> a[i];
	cout << solve() << "\n";
	return 0;
}

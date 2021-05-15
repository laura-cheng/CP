//#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

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
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct math {
	int n;
	vector<int> inv, fac;
	void init_(int _n) {
		n = _n;
		inv.assign(n + 1, 1);
		fac.assign(n + 1, 1);
		rep(i, 1, n) fac[i] = fac[i - 1] * i % MOD;
		inv[n] = pow_(fac[n], MOD - 2);
		rrep(i, 0, n - 1) inv[i] = inv[i + 1] * (i + 1) % MOD;
	}
	int pow_(int a, int times) {
		int ans = 1;
		for(;times > 0; times >>= 1, a = a * a % MOD) {
			if(times & 1) ans = ans * a % MOD;
		}
		return ans;
	}
	int C(int n, int m) {
		if(m == 0) return 1;
		if(n < m) return 0;
		return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
	}
};
namespace SOLVE {
	int n;
	vector<int> a, dp, count, pre;
	math m;
	void init_(int _n) {
		n = _n, m.init_(n);
		a.assign(n + 1, -1);
		dp.assign(n + 1, 1);
	}
	int solve() {
		sort(all(a));
		count.push_back(0);
		pre.push_back(0);
		rep(i, 1, n) {
			if(a[i] != a[i - 1]) {
				count.push_back(0);
				pre.push_back(pre.back() + 1);
			}
			else pre[pre.size() - 1] ++;			
		}	
		rep(i, 2, n) dp[i] = i * (i - 1) / 2 % MOD * dp[i - 1] % MOD;
		count[1] = dp[pre[1]];
		rep(i, 2, count.size() - 1) {
			int sz = pre[i] - pre[i - 1];
			rep(j, 0, sz - 1) {
				count[i] = (
					count[i] + count[i - 1] * m.C(pre[i - 1] + j - 1, j) % MOD
					* dp[pre[i] - pre[i - 1]] % MOD * (sz - j)
				) % MOD;
			}
		}
		return count.back();
	}
};
using namespace SOLVE;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) cin >> a[i];
	cout << solve() << "\n";
	
	return 0;

}

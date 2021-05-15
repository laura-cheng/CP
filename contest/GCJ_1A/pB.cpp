#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimze("Ofast")
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
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n;
	vector<int> p, num;
	void init_(int _n) {
		n = _n;
		p.assign(n + 1, 0);
		num.assign(n + 1, 0);
	}
	bool check(int x) {
		vector<int> cnt(n + 1, 0);
		int ans = 0, y = x;
		rep(i, 1, n) {
			while(x % p[i] == 0) {
				cnt[i] ++, x /= p[i];
			}
			if(cnt[i] > num[i]) return 0;
			ans += (num[i] - cnt[i]) * p[i];
		}
		if(x != 1) return 0;
		return (ans == y);
	} 
	int solve() {
		rrep(i, 1, 50000) if(check(i)) return i;
		return 0;
	}
};
namespace solver2 {
	int n, sum = 0;
	vector<int> p, num;
	void init_(int _n) {
		n = _n, sum = 0;
		p.assign(n + 1, 0);
		num.assign(n + 1, 0);
	}
	bool check(int sum, int x) {
		vector<int> cnt(n + 1, 0);
		int ans = 0, y = sum - x;
		rep(i, 1, n) {
			while(y % p[i] == 0) {
				cnt[i] ++, y /= p[i];
			}
			if(cnt[i] > num[i]) return 0;
			ans += cnt[i] * p[i];
		}
		if(y != 1) return 0;
		return (ans == x);
	} 
	int solve() {
		rep(i, 1, n) sum += p[i] * num[i];
		rep(i, 0, min(sum - 1, 50000ll)) if(check(sum, i)) return sum - i;
		return 0;
	}

};
using namespace solver2;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int n; cin >> n;
		init_(n);
		rep(i, 1, n) cin >> p[i] >> num[i];
		cout << "Case #" << tt << ": " << solve() << "\n";
	}
	return 0;
}

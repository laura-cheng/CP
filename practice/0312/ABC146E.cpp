#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i ,a, b) for(int i = b; i >= a; i--)
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
struct AC {
	int n, k;
	vector<int> a, b;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		a.assign(n + 1, 0);
		b.assign(n + 1, 0);
	}
	int solve() {
		map<int, int> cnt;
		int sum = 0, ans = 0; 
		cnt[0] = 1;
		rep(i, 1, n) {
			if(i - k >= 0) cnt[b[i - k]] --; 
			sum += a[i];
			b[i] = ((sum - i) % k + k) % k; 
			
			ans += cnt[b[i]];
			cnt[b[i]] ++;	 
		}
		return ans;
	}
} a;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	a.init_(n, k);
	rep(i, 1, n) cin >> a.a[i];
	cout << a.solve() << "\n";
	return 0;
}

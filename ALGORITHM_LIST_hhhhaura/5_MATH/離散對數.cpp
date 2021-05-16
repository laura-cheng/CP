#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MOD 1000000007
#define INF 1000000000000000000
#define MAXN 1000005
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int,int>
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
int pow_(int a, int times, int mod) {
	int ans = 1;
	for(;times > 0; times >>= 1, a = (a * a) % mod) {
		if(times & 1) ans = (ans * a) % mod;
	}
	return ans;
}
int solve(int a, int b, int n) {
	map<int, int> mp;
	int ans = INF, k = sqrt(n) + 1;
	rrep(i, 0, k) mp[pow_(a, i * k, n)] = i;
	rep(i, 0, k) {
		int cur = b * pow_(a, i, n) % n;
		if(mp.find(cur) != mp.end()) {
			int aa = mp[cur];
			if(aa * k - i >= 0)
			ans = min(ans, aa * k - i);
		}
	}
	if(ans == INF) return -1;
	else return ans;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int a, b, n;
	while(cin >> a >> b >> n) {
		int ans = solve(a, b, n);
		if(ans == -1) cout << "NOT FOUND\n";
		else cout << ans << "\n";
	}
	return 0;
}

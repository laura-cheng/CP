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
int t, n, w = 26;
string s;
vector<int> pre;
vector<string> a;
int check(string a) {
	int cnt = 0, k = 1, h = 0;
	int s1 = s.size(), s2 = a.size();
	for(auto i : a) {
		h = (h + (i - 'a' + 1) * k) % MOD;
		k = (k * w) % MOD; 
	}
	rep(i, 1, s1 - s2 + 1) {
		int cur = pre[i + s2 - 1] - pre[i - 1];
		cur = (cur % MOD + MOD) % MOD;
		if(cur == h) cnt++;
		h = (h * w) % MOD;
	} 
	return cnt;
}
void solve() {
	int sz = s.size(), k = 1;
	pre.assign(sz + 1, 0);
	rep(i, 0, sz - 1) {
		pre[i + 1] = pre[i] + (s[i] - 'a' + 1) * k;
		pre[i + 1] %= MOD;
		k = (k * w) % MOD;
	}
	int ans = 0;
	rep(i, 1, n) 
		cout << check(a[i]) << "\n";  
	return ;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> t;
	while(t--) {
		cin >> s >> n;
		a.assign(n + 1, "");
		rep(i, 1, n) cin >> a[i];
		solve();
	}
	return 0;
}

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
void build(vector<string> &a, string s, int ii, int l, int n) {
	rep(i, 1, n) {
		while(a[i].size() < l) a[i] += s[ii++];
	}
	return;
}
void solve(int n, int l, int k, string s) {
	vector<string> a(n + 1, "");
	sort(all(s));
	int ii = 0, cur = 1;
	if(k == 1) build(a, s, ii, l, n);
	else {
		while(!a[k].size() || a[k].back() == a[k - 1].back()) {
			if(a[k].size() >= l) break;
			rep(i, cur, k) {
				a[i] += s[ii ++];
				if(i > 1 && a[i].back() != a[i - 1].back()) cur = i;
			}
		}
		while(a[k].size() < l) a[k] += s[ii ++];
		build(a, s, ii, l, n);
	}
	rep(i, 1, n) cout << a[i] << "\n";
} 
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, l, k; string s;
	cin >> n >> l >> k >> s;
	solve(n, l, k, s);
	return 0;
}

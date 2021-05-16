#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define MAXN 1000005
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>

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
vector<int> zscore(string a) {
	int n = a.size();
	vector<int> z(n, 0);
	int l = 1, r = 0; // important
	rep(i, 1, n - 1){
		z[i] = max(0ll, min(r - i, z[i - l]));
		while(i + z[i] < n && a[i + z[i]] == a[z[i]]) {
			l = i, r = i + z[i], z[i] ++;
		}
	}
	return z;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		string a, b; int c;
		cin >> a >> c;
		while(c--) {
			cin >> b;
			vector<int> z = zscore(b + "$" + a);
			int ans = 0;
			for(auto i : z) {
				ans += bool(i == b.size());
			}
			cout << ans << "\n";
		}

	}
	return 0;
}

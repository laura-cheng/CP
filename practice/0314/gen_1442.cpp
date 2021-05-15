#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i= b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

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
void vprint(auto L, auto R) {
	while(L < R) cout << *L << " \n"[next(L) == R], ++L;
}
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
random;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n = rnd() % 5 + 1, k = rnd() % 10 + 1;
	cout << n << " " << k << "\n";
	vector<int> cur;
	rep(i, 1, n - 1) {
		int t = rnd()%5  + 1;
		k -= t;
		cout << t << " ";
		cur.clear();
		rep(j, 1, t) cur.push_back(rnd() % 20 + 1);
		sort(all(cur)), vprint(all(cur));
	}	
	int tt = rnd() % 5 + 1;
	cout << max(tt, k) << " ";
	cur.clear();
	rep(i, 1, max(tt, k)) cur.push_back(rnd() % 20 + 1);
	sort(all(cur)), vprint(all(cur));
	return 0;
}

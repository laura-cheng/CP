#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define MAXN 1000005
#define eps (1e-9)

#define int long long int
#define pii pair<int, int>
#define lld long double
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2>  void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...)
#define vprint(...)
#endif

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	vector<int> a(n, 0);
	int *id = &a[0];
	for(auto &i : a) {
		cin >> i;
		if(i >= 0) i = -i - 1; 
		if(i < *id) id = &i;
	}
	if(n & 1) *id = -*id - 1;
	rep(i, 0, n - 1) cout << a[i] << " \n"[i + 1 == n];
 	
	return 0;
}

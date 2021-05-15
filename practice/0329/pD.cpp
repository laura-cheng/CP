#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
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

/*int solve(int l, int r) {
	int one = 1, a = 0, b = 0;
	rrep(i, 0, 62) {
		if(a < b) swap(a, b);
		int mx = b | ((one << (i + 1)) - 1);
		int mn = b | (one << i);
		int mid = a | ((one << i) - 1);
		if(mid < l) a |= one << i;
		if(mx >= l && mn <= r) b |= one << i;
	} 
	return a ^ b;
}*/
int solve(int l, int r) {
	int one = 1;
	rrep(i, 0, 62) {
		int aa = (l >> i) & 1;
		int bb = (r >> i) & 1;
		if(bb & !aa) return (one << (i + 1)) - 1;
	}
	return 0;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int l, r; cin >> l >> r;
	cout << solve(l, r) << "\n";
	return 0;
} 

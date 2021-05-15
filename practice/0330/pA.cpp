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
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
bool check(int n) {
	if(!n) return 0;
	while(n) {
		if((n % 10) != 7 && (n % 10) != 4) return 0;
		n /= 10;
	}
	return 1;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	bool yes = 0;
	rep(i, 1, n) {
		if(check(i) && (n % i == 0)) yes = 1;
	}
	if(yes) cout << "YES\n";
	else cout << "NO\n";
	return 0;
}

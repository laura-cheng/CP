#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

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
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n; cin >> n;
		int ans = n / 4 * 4 * 10;
		if(!(n / 4)) {
			if(n % 4 == 1) ans = 1;
			if(n % 4 == 2) ans = 6;
			if(n % 4 == 3) ans = 12;
		}
		else {
			if(n % 4 == 1) ans = ans - 12 + 1;
			if(n % 4 == 2) ans = ans - 8 + 6;
			if(n % 4 == 3) ans = ans - 4 + 12;
			if(n % 4 == 0) ans = ans - 16;
		}
		cout << n * 21 - ans << "\n";
	}
	
	return 0;

}

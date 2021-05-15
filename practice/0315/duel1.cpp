#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loo-opt(on)

#define rep(i ,a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MAXN 1000005
#define MOD 1000000007
#define eps (1e-9)

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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, h, a, b, k;
	cin >> n >> h >> a >> b >> k;
	while(k--) {
		int t1, f1, t2, f2;
		cin >> t1 >> f1 >> t2 >> f2;
		if(t1 == t2) cout << abs(f1 - f2) << "\n";
		else if(f1 > b) {
			cout << f1 - b + abs(t1 - t2) + abs(b - f2) << "\n";
		}
		else if(f1 >= a && f1 <= b) {
			cout << abs(t1 - t2) + abs(f1 - f2) << "\n";
		}
		else {
			cout << a - f1 + abs(t1 - t2) + abs(a - f2) << "\n";
		}
	} 	
	
	return 0;
}

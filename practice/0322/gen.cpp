#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 10000000000000000000
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
random;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n = rnd() % 5 + 1;
	set<int> s;
	cout << n << "\n";
	rep(i, 1, n) {
		
		int x; x = rnd() % n + 1;
		s.insert(x);
		cout << x << " \n"[i == n];
	}
	rep(i, 1, n) {
		int x = rnd() % n + 1;
		while(!s.count(x)) x = rnd() % n + 1;
		cout << x << " \n"[i == n];
	}
	
	return 0;
}

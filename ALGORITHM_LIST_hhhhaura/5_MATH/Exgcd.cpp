#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MOD 1000000007
#define MAXN 1000005
#define INF 1000000000000000000
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
pii exgcd(int a, int b) {
	if(b == 0) return {a, 0};
	else {
		pii p = exgcd(b, a % b);
		return {p.second, p.first - a / b * p.second};
	}
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int A, B;
	while(cin >> A >> B) {
		int gcd = __gcd(A, B);
		A /= gcd, B /= gcd;
		pii ans = exgcd(A, B);
		cout << ans.first << " " 
			<< ans.second << " " << gcd << "\n";
	}
	return 0;
}

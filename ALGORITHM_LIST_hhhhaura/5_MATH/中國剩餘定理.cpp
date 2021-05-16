#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MOD 1000000007
#define INF 1000000000000000000
#define MAXN 1000005
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int,int>
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
vector<int> a, r;
pii exgcd(int a, int b) {
	if(b == 0) return pii(a > 0 ? 1 : -1, 0);
	else {
		pii p = exgcd(b, a % b);
		return pii(p.second, p.first - a / b * p.second);
	}
}
int __gcd(int a, int b) {
	if(b == 0) return a;
	else return __gcd(b, a%b);
}
int crt(int n) {
	int aa = 1, rr = 0;
	rep(i, 1, n) {
		pii p = exgcd(aa, -a[i]);
		int c = r[i] - rr, gcd = __gcd(aa, a[i]);
		if(c % gcd) return -1;
		p.first = p.first * (c / gcd) % a[i];
		rr = aa * p.first + rr;
		aa = aa / gcd * a[i];
		rr = rr % aa;
	}
	return (rr + aa) % aa;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n;
	while(cin >> n) {
		a.assign(n + 1, 0);
		r.assign(n + 1, 0);
		rep(i, 1, n) 
			cin >> a[i] >> r[i];
		cout << crt(n) << "\n"; 
	}
	return 0;
}

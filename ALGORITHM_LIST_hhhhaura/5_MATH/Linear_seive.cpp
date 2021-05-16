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
vector<int> fac, p;
void seive() {
	fac.assign(MAXN, 1);
	rep(i, 2, MAXN - 1) {
		if(fac[i] == 1) p.push_back(i);
		for(auto j : p) {
			if(i * j >= MAXN) break;
			fac[i * j] = j;
			if(i % j == 0) break; 
		}
	}
	return;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	seive();
	int x;
	while(cin >> x) {
		bool yes = 1;
		if(x < MAXN) yes = bool(fac[x] == 1);
		else {
			for(auto i : p) {
				if(x % i == 0) {
					yes = 0;
					break;
				} 
				if(i * i > x) break;
			} 
		}
		if(yes) cout << "質數\n";
		else cout << "非質數\n";
	}
	return 0;
}

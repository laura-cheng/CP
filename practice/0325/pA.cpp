//#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MAXN 1000005
#define eps (1e-9)
#define MOD 1000000007

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
struct prime {
	int n;
	vector<int> fac, p;
	void init_(int _n) {
		n = _n, p.clear();
		fac.assign(n + 1, 1);
		rep(i, 2, n) {
			if(fac[i] == 1) p.push_back(i);
			for(auto j : p) {
				if(i * j > n) break;
				fac[i * j] = j;
				if(i % j == 0) break;
			}
		}
	}
	bool isprime(int x) {
		if(x == 1) return 0;
		return fac[x] == 1;
	}
};
namespace SOLVE {
	prime p;
	void init_() {
		p.init_(1e6 + 10);
	}
	int type(int x) {
		int y = x;
		string rev = "";
		while(y) {
			rev += char(y % 10 + '0');
			y /= 10;
		}
		y = stoi(rev);
		if(p.isprime(x) && p.isprime(y) && x != y) return 3;
		else if(p.isprime(x)) return 1;
		else return 2;
	}

};
using namespace SOLVE;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; 
	init_();
	while(cin >> n) {
		int x = type(n);
		if(x == 1) cout << n << " is prime.\n";
		else if(x == 2) cout << n << " is not prime.\n";
		else cout << n << " is emirp.\n";
	}
	
	return 0;
}

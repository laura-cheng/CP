#define wiwihorz
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
	vector<int> p, fac, L, R;
	unordered_map<int, int> big_L, big_R;
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
		big_L.clear(), big_R.clear();
		L.assign(p.size(), 0);
		R.assign(p.size(), 0);
	}	
	int deco(int x, int id) {
		vector<int> ans;
		int k = sqrt(x) + 1, ans = 1;
		rep(i, 0, signed(p.size()) - 1) {
			if(p[i] * p[i] > k) break;
			if(x % p[i] != 0) continue;
			if(R[i] == id - 1) {
				
			}
			else L[i] = R[i] = id;
		}
	}
};
namespace SOLVE {


};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	
	return 0;
}

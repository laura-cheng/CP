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
#define MAXN 1000005
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
namespace SOLVE {
	int n, c;
	void init_(int _n, int _c) {
		n = _n, c = _c;
	}
	int cal(vector<int> a) {
		int ans = 0;
		rep(i, 0, n - 2) {
			int id = i;
			rep(j, i, n - 1) if(a[id] > a[j]) {
				id = j;
			}
			reverse(a.begin() + i, a.begin() + id + 1);
			ans += id - i + 1;
		}
		return ans;
	}
	void solve(int t) {
		vector<int> a;
		rep(i, 1, n) a.push_back(i);
		bool yes = 0;
		do {
			if(cal(a) == c) {
				yes = 1;
				break;
			}
		} while(next_permutation(all(a)));
		cout << "Case #" << t << ": ";
		if(yes) {
			rep(i, 0, n - 1) cout << a[i] << " \n"[i + 1 == n];
		}
		else cout << "IMPOSSIBLE\n";
	}	
};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int n, c; cin >> n >> c;
		SOLVE::init_(n, c);
		SOLVE::solve(tt);
	}
	return 0;
} 

#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i ,a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)

using namespace std;
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
random;
vector<int> ord, val;
bool cmp(int a, int b) {
	return val[a] < val[b];
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; 
	n = rnd() % 5 + 1;
	m = rnd() % ((n * (n - 1)) / 2 + 1);
	cout << n << " " << m << "\n";
	rep(i, 1, m) cout << rnd() % n + 1 << " " << rnd() % n + 1 << "\n";
	
	return 0;
}

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
int a[20000], b[20000];
stack<int> st;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> b[i];
	rrep(i, 1, n) st.push(a[i]);
	int q, ii = 0, cur; 
	cin >> q, q = q * 2 + n;
	bool yes = 1;
	rep(i, 1, q) {
		char c; int x;
		cin >> c;
		if(c == 'T') cur = st.top(), st.pop();
		else if(c == 'P') {
			cin >> x, st.push(x);
		}
		else {
			ii ++;
			if(b[ii] != cur) yes = 0;
		}
	}
	if(yes) cout << "yes\n";
	else cout << "no\n";
	return 0;
}

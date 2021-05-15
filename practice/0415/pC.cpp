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
#define pii pair<int, int>
#define lld long double
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2>  void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...)
#define vprint(...)
#endif

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	string s; cin >> s;
	vector<int> a(n + 1, 0), mn(n + 1, INF);
	rep(i, 1, n) a[i] = a[i - 1] + (s[i - 1] == '(' ? 1 : -1);
	rrep(i, 1, n) mn[i] = min(mn[min(n, i + 1)], a[i]);
	int ans = 0, c = -a[n];
	if(abs(c) != 2) cout << "0\n";
	else {
		rep(i, 1, n) {
			if(s[i - 1] == '(' && c > 0 ||
				s[i - 1] == ')' && c < 0) ;
			else if(mn[i] + c >= 0) ans ++;
			if(a[i] < 0) break;
		}		
		cout << ans << "\n";
 	}
	return 0;
}

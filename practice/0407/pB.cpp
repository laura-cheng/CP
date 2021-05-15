#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

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
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n; cin >> n;
		vector<int> a(n + 1, 0), b(n + 1, 0);
		vector<int> c(n + 1, 0), pre(n + 1, 0);
		rep(i, 1, n) cin >> c[i];
		rep(i, 1, n) cin >> a[i];
		rep(i, 1, n) cin >> b[i];
		rep(i, 1, n) if(a[i] > b[i]) swap(a[i], b[i]);
		int ans = 1, cur = 0;
		rep(i, 2, n - 1) pre[i] = pre[i - 1] + c[i] - (b[i + 1] - a[i + 1] - 1);
		rep(i, 2, n) {
			int ccur = -pre[i - 1] + b[i] - a[i] + 1;
			if(a[i] == b[i]) cur = ccur;
			else cur = max(cur, ccur);
			ans = max(ans, pre[i - 1] + cur + c[i]);
			
		}
		cout << ans << "\n";
	}	
	
	return 0;

}

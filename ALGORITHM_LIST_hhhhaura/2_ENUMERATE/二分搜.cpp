#define hhhhaura
#include <bits/stdc++.h>
#pragma GC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()  
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MAXN 1000005
#define MOD 1000000007
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef hhhhaura
#define print(a...) out("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {while(L < R) cerr << *L << "\n"[next(L) == R], ++L;}
void out() {cerr << endl;}
template<class T1, class... T2> void out(T1 a, T2 ... e) {cerr << a << " ", out(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
int n, k;
vector<int> a;
bool check(int x) {
	int cnt = 1, cur = x;
	rep(i, 1, n) {
		if(a[i] > x) return false;
		if(cur < a[i]) cnt ++, cur = x; 
		cur -= a[i];
	}
	return cnt <= k;
}
int solve() {
	int l = 0, r = 1e9;
	while(r - l > 1) {
		int mid = (l + r) / 2;
		if(check(mid)) r = mid;
		else l = mid;
	}
	return r;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> k , a.assign(n + 1, 0);
	rep(i, 1, n) cin >> a[i];
	cout << solve() << "\n";
	return 0;
}

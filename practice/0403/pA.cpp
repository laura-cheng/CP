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
void solve(int n, string s) {
	int cnt[2], cnt1[2];
	cnt[0] = cnt[1] = 0;
	cnt1[0] = cnt1[1] = 0;
	for(auto i : s) cnt[i - '0'] ++;
	if((cnt[0] & 1) || (cnt[1] & 1) ||
		s[0] == '0' || s.back() == '0') {
		cout << "NO\n";
		return;
	}
	string ans, ans1;
	rep(i, 0, n - 1) {
		int id = s[i] - '0';
		cnt1[id] ++;
		if(id == 1) {
			char c = (cnt1[id] * 2 > cnt[id] ? ')' : '(');
			ans += c, ans1 += c;
		}
		else {
			char c = ((cnt1[id] & 1) ? '(' : ')');
			char c1 = ((cnt1[id] & 1) ? ')' : '(');
			ans += c, ans1 += c1;
		}
	}
	cout << "YES\n" << ans << "\n" << ans1 << "\n";
	return;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n; string s;
		cin >> n >> s;
		solve(n, s);
	}
	
	return 0;

}

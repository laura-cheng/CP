#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define MAXN 1000005
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>

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
vector<int> fail_function(string s) {
	int n = s.size();
	vector<int> ans(n + 1, -1); // give n + 1 a home
	rep(i, 1, n - 1) {
		int cur = ans[i - 1];
		while(cur != -1 && s[cur + 1] != s[i]) {
			cur = ans[cur];
		}
		if(s[cur + 1] == s[i]) cur ++;
		ans[i] = cur;
	}
	return ans;
}
int KMP(string a, string b) {
	int n1 = a.size(), n2 = b.size();
	int cnt = 0, j = -1; // initialize j as -1
	vector<int> f = fail_function(b);
	rep(i, 0, n1 - 1) {
		while(j != -1 && b[j + 1] != a[i]) {
			j = f[j];
		}
		if(b[j + 1] == a[i]) j ++;
		if(j == n2 - 1) cnt ++;
	}
	return cnt;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		string s1, s2; int c;
		cin >> s1 >> c;
		while(c--) {
			cin >> s2;
			cout << KMP(s1, s2) << "\n";
		}
	}
	return 0;
}

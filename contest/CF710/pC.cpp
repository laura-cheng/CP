#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a ,b) ((a + b - 1) / (b))

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
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
int solve(string a, string b, int x) {
	vector<int> pos;
	pos.push_back(-1); 
	rep(i, 0, signed(a.size()) - 1) {
		int j = i + x;
		if(j < 0 || j >= b.size()) pos.push_back(i);
		else if(a[i] != b[j]) pos.push_back(i);
	}
	int ans = 0; 
	pos.push_back(a.size());
	rep(i, 1, signed(pos.size()) - 1) {
		ans = max(ans, pos[i] - pos[i - 1] - 1);
	}
	return a.size() + b.size() - 2 * ans;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		string a, b;
		cin >> a >> b;
		int ans = INF;
		rep(i, -20, 20) {
			ans = min(ans, solve(a, b, i));
		}
		cout << ans << "\n";
	}	
	return 0;
}


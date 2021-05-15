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
#define eps (1e-9)
#define MAXN 1000005

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
int solve(vector<pii> a, int n) {
	map<pii, int> mp;
	for(auto i : a) {
		pii cur;
		if(i.first == 0) {
			if(i.second > 0) mp[pii(0, 1)] ++;
			else mp[pii(0, -1)] ++;
		}
		else {
			int g = __gcd(abs(i.first), abs(i.second));
			i.first /= g, i.second /= g;
			cur = {i.first, i.second};
			mp[cur] ++;
		}
	}
	int ans = 0;
	for(auto i : mp) {
		int x = -i.first.first, y = -i.first.second;
		ans += mp[pii(x, y)] * i.second;
	}
	return ans / 2;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n; cin >> n;
		vector<pii> a;
		rep(i, 1, n) {
			int x, y, u, v;
			cin >> x >> y >> u >> v;
			a.push_back({u - x, v - y});
		} 
		cout << solve(a, n) << "\n";
	}	
	return 0;
}
/*
What I learnt 
1. do not use floating point calculation !!
2. atan2 accepts (y, x), returns 0 ~ 3.14, 0 ~ -3.14
*/

#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MAXN 1000005
#define INF 1000000000000000000
#define MOD 1000000007
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
struct AC {
	struct pt {
		int L, R, x;
	};
	int n;
	vector<int> S, E, dp, a;
	stack<pt> s;
	void init_(int _n) {
		n = _n;
		S.assign(n + 1, INF);
		E.assign(n + 1 , 0);
		dp.assign(n + 1, 0);
		a.assign(n + 1, 0);
		while(s.size()) s.pop();
	}
	int solve() {
		rep(i, 1, n) {
			S[a[i]] = min(S[a[i]], i);
			E[a[i]] = max(E[a[i]], i);
		}
		int ans = 0;
		s.push({0, 0, 0});
		rep(i, 1, n) {
			pt cur = {i, i, a[i]};
			if(E[cur.x] != i) {
				s.push(cur);
				continue;
			}
			while(s.size() && s.top().L >= S[cur.x]) {
				cur.L = s.top().L;
				s.pop();
			}
			dp[i] = dp[s.top().R] + 1;
			s.push(cur);
			ans += dp[i];
		}
//		vprint(all(dp));
		return ans;
	}

} ac;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n; cin >> n;
		ac.init_(n);
		rep(i, 1, n) cin >> ac.a[i];
		cout << ac.solve() << "\n";
	}
	
	return 0;
}

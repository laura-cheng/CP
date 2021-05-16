#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MOD 1000000007
#define INF 1000000000000000000
#define MAXN 1000005
#define eps (1e-9)

//#define int long long int
#define lld long double
#define pii pair<int,int>
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
int n, p;
vector<int> cnt, w, v;
int solve() {
	vector<int> dp(p + 1, 0);
	rep(i, 1, n) {
		rep(j, 0, w[i] - 1) {
			deque<pii> dq;
			for(int k = j; k <= p; k += w[i]) {
				while(dq.size() && 
					k - dq.front().first > cnt[i] * w[i]) {
					dq.pop_front();
				}
				int ans = 0;
				pii cur = {k, dp[k] - k / w[i] * v[i]};
				if(dq.size()) ans = dq.front().second;
				ans += k / w[i] * v[i];
				while(dq.size() && dq.back().second <= cur.second) {
					dq.pop_back();
				}
				dq.push_back(cur);
				dp[k] = max(dp[k], ans);
			} 
		}
	}
	return dp[p];
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> p;
	cnt.assign(n + 1, 0);
	w.assign(n + 1, 0);
	v.assign(n + 1, 0);
	rep(i, 1, n) cin >> cnt[i] >> v[i] >> w[i];
	cout << solve() << "\n";
	return 0;
}

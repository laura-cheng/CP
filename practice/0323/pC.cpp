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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	vector<int> a, b, pos, v, val;
	vector<int> pre, dp;
	a.assign(n + 1, 0);
	b.assign(n + 1, 0);
	pos.assign(n + 1, 0);
	v.assign(n + 1, 0);
	pre.assign(n + 1, 0);
	dp.assign(n + 1, 0);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> b[i];
	rep(i, 1, n) val.push_back(a[i]);
	vprint(all(val));
	sort(all(val));
	rep(i, 1, n) {
		a[i] = lower_bound(val.begin(), val.end(), a[i]) - val.begin() + 1;
		b[i] = lower_bound(val.begin(), val.end(), b[i]) - val.begin() + 1;
	}	
	rep(i, 1, n) pos[b[i]] = i;
	rep(i, 1, n) v[i] = pos[a[i]];
	int ans = 0, p = 0;
	rrep(i, 1, n) {
		dp[i] = 1;
		rep(j, i + 1, n) {
			if(v[i] >= v[j]) continue;
			if(dp[j] + 1 == dp[i]) {
				if(a[pre[i]] < a[j]) {
					pre[i] = j;
				}
			}
			else if(dp[j] + 1 > dp[i]) {
				pre[i] = j;
				dp[i] = dp[j] + 1;
			}  
		}	
		ans = max(ans, dp[i]);
	}	
	rep(i, 1, n) if(ans == dp[i]) {
		if(a[i] > a[p]) p = i;
	}
	rep(i, 1, ans) {
		cout << val[a[p] - 1] << " \n"[i == ans];
		p = pre[p];
	}
	return 0;
}

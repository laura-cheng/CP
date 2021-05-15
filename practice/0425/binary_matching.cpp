#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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

using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
#define sz(x) signed(x.size())
namespace solver {
	string a, b, pattern, suf;
	int st, ans, cnt[2], cnt1[2], ans1;
	vector<vector<int>> l, r, dp;
	void init_(string _a, string _b) {
		a = _a, b = _b;
		st = sz(b), ans = 0, ans1 = INF;
		rep(i, 0, sz(a) - 1) cnt[a[i] - '0'] ++;
		rep(i, 0, sz(b) - 1) cnt1[b[i] - '0'] ++;
		rep(i, 1, sz(b) - 1) {
			bool yes = 1;
			rep(j, i, sz(b) - 1) yes &= (b[j - i] == b[j]);
			if(yes) st = min(st, i);
		}
		if(cnt[0] < cnt1[0] || cnt[1] < cnt1[1]) return;
		if(cnt1[0]) ans1 = min(ans1, cnt[0] / cnt1[0]);
		if(cnt1[1]) ans1 = min(ans1, cnt[1] / cnt1[1]);
		cnt[0] -= cnt1[0], cnt[1] -= cnt1[1];
		pattern = b, ans = 1;
		int x = 0, y = 0;
		rep(i, sz(b) - st, sz(b) - 1) {
			x += bool(b[i] == '0');
			y += bool(b[i] == '1');
		}
		suf = b.substr(sz(b) - st, st);
		while(true) {
			if(cnt[0] >= x && cnt[1] >= y) {
				pattern += suf, ans ++;
				cnt[0] -= x, cnt[1] -= y;
			}
			else break;
		}
		return;
	}
	void build(int s) {
		queue<int> aa, bb;
		l.assign(sz(a) + 1, vector<int>(sz(a) + 1, -1));
		r.assign(sz(a) + 1, vector<int>(sz(a) + 1, -1));
		rep(i, 1, sz(a)) {
			int sum = 0; bool ok = 1;
			while(aa.size()) aa.pop();
			while(bb.size()) bb.pop();
			rep(j, i, sz(a)) {
				if(j - s >= 0 && a[j - 1] == '1') aa.push(j);
				if(j - s < sz(pattern) && j - s >= 0
					&& pattern[j - s] == '1') bb.push(j);
				while(aa.size() && bb.size()) {
					int x = aa.front(); aa.pop();
					int y = bb.front(); bb.pop();
					if(x < y) {
						ok = 0;
						break;
					}
					sum += x - y;
				}
				if(!ok) break;
				if(aa.empty() && bb.empty()) l[i][j] = sum;
				else if(j - s >= sz(pattern) && bb.empty() 
					&& aa.front() > sz(pattern) + s - 1) l[i][j] = sum; 
			} 

		}
		rep(i, 1, sz(a)) {
			int sum = 0; bool ok = 1;
			while(aa.size()) aa.pop();
			while(bb.size()) bb.pop();
			rrep(j, 1, i) {
				if((j - s < sz(pattern)) && a[j - 1] == '1') aa.push(j);
				if((j - s < sz(pattern)) && j - s >= 0
					&& pattern[j - s] == '1') bb.push(j);
				while(aa.size() && bb.size()) {
					int x = aa.front(); aa.pop();
					int y = bb.front(); bb.pop();
					if(x > y) {
						ok = 0;
						break;
					}
					sum += y - x;
				}
				if(!ok) break;
				if(aa.empty() && bb.empty()) r[j][i] = sum;
				else if(j - s < 0&& bb.empty() && aa.front() < s) r[j][i] = sum; 
			}
		}
	}
	int solve() {
		int ans = INF;
		vector<int> have;
		rep(i, 0, sz(a) - 1) if(a[i] == '1') have.push_back(i + 1);
		rep(s, 1, sz(a) - sz(pattern) + 1) {
			dp.assign(sz(a) + 1, vector<int>(2, INF));
			build(s);
			dp[0][0] = 0, dp[0][1] = 0;
			rep(i, 1, sz(a)) rep(j, 0, i - 1) {
				if(r[j + 1][i] != -1) dp[i][0] = min(dp[i][0], dp[j][1] + r[j + 1][i]);
				if(l[j + 1][i] != -1) dp[i][1] = min(dp[i][1], dp[j][0] + l[j + 1][i]);						
			}
			ans = min(ans, min(dp[sz(a)][0], dp[sz(a)][1]));
		}
		return ans;
	}
	int solve1() {
		vector<int> best(sz(a) - sz(b) + 2, INF);
		pattern = b;
		print("yse");
		rep(s, 1, sz(a) - sz(b) + 1) {
			
			dp.assign(sz(a) + 1, vector<int>(2, INF));
			build(s);
			dp[s - 1][0] = 0, dp[s - 1][1] = 0;
			rep(i, s, s + sz(b) - 1) rep(j, s - 1, i - 1){
				if(r[j + 1][i] != -1) dp[i][0] = min(dp[i][0], dp[j][1] + r[j + 1][i]);
				if(l[j + 1][i] != -1) dp[i][1] = min(dp[i][1], dp[j][0] + l[j + 1][i]);
			}
			best[s] = min(dp[s + sz(b) - 1][0], dp[s + sz(b) - 1][1]);
		}
		vprint(all(best));
		dp.assign(sz(a) + 1, vector<int>(ans + 1, INF));
		dp[0][0] = 0;
		rep(i, 1, sz(a)) rep(j, 0, ans) {
			dp[i][j] = dp[i - 1][j];
			if(j > 0 && i - sz(b) >= 0) dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + best[i - sz(b) + 1]);
		}
		return dp[sz(a)][ans];
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	string a, b; cin >> a >> b;
	init_(a, b);
	print(ans1, ans);
	print(solve(), solve1());
	if(ans1 == ans) cout << ans << " " << min(solve(), solve1()) << "\n";
	else cout << ans << " " << solve();
	return 0;
}

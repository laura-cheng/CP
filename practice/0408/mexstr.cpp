#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MAXN 1000005
#define MOD 1000000007
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
namespace solve_ {
	int n;
	vector<bool> vis;
	vector<int> pre;
	stack<int> z, o;
	void init_(string s) {
		reverse(all(s));
		n = s.size();
		while(z.size()) z.pop();
		while(o.size()) o.pop();
		vis.assign(n, 0);
		pre.assign(n, 0);
		
		rep(i, 1, n - 1) {
			pre[i] = pre[i - 1];
			if(s[i] != s[i - 1] && !vis[i - 1]) {
				vis[i] = 1, pre[i] ++;
			}
		}
		rep(i, 0, n - 1) {
			if(s[i] == '0') z.push(i);
			if(s[i] == '1') o.push(i);	
		}
		return;
	}
	string solve() {
		string ans = "1"; 
		int cur = 0, len = 0;
		if(o.size() == 0) return "1";
		if(z.size() == 0) return "0";
		cur = o.top(); o.pop();
		len = pre[max(0ll, cur - 1)] + 2;
		while(o.size() && o.top() >= cur) o.pop();
		while(z.size() && z.top() >= cur) z.pop();
		rrep(i, 2, len - 1) {
			int cz = (z.size() ? z.top() : -1);
			int co = (o.size() ? o.top() : -1);
			if(pre[max(0ll, cz - 1)] + 1 >= i) ans += "1", cur = co;
			else ans += "0", cur = cz;
			while(o.size() && o.top() >= cur) o.pop();
			while(z.size() && z.top() >= cur) z.pop();
		}
		if(z.size()) ans += "1";
		else ans += "0";
		return ans;
	}
};
namespace solve2_ {
	string solve(string s) {
		reverse(all(s));
		int cnt = 0;
		for(auto i : s) cnt += bool((i - '0') == 1);
		if(cnt == s.size()) return "0";
		for(int i = 1; i < (1 << 16); i ++) {
			bitset<15> a(i);
			int ii = 0;
			for(auto j : s) {
				if(ii == 15) break;
				if((j - '0') == a[ii]) ii++;
			}
			if(31 - __builtin_clz(i) >= ii) {
				string ans;
				while(i) ans += char((i & 1) + '0'), i >>= 1;
				reverse(all(ans));
				return ans;
			} 
		}
	}

};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		string s; cin >> s;
		solve_::init_(s);
		cout << solve_::solve() << "\n";
	}
	return 0;
}

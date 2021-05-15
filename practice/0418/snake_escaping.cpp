#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) for(int i = a; i <= b; i++)

#define INF 1000000000000000000
#define MAXN 1000005
#define MOD 1000000007
#define eps (1e-9)

#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a )
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ",kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int L; string s;
	vector<int> sp, sb, cnt;
	void init_(int _L, string _s) {
		L = _L, s = _s;
		sp.assign(1 << L, 0);
		sb.assign(1 << L, 0);
		cnt.assign(1 << L, 0);
		rep(i, 0, (1 << L) - 1) {
			sp[i] = s[i] - '0';
			sb[i] = s[i] - '0';
			cnt[i] = __builtin_popcount(i);
		}
		rep(i, 0, L - 1) {
			rep(j, 0, (1 << L) - 1) 
				if(!((j >> i) & 1)) sp[j] += sp[j ^ (1 << i)];
			rrep(j, 0, (1 << L) - 1) 
				if((j >> i) & 1) sb[j] += sb[j ^ (1 << i)];
		}
	}
	int query(string a) {
		int A = 0, B = 0, C = 0;
		rep(i, 0, L - 1) {
			if(a[i] == '1') B |= (1 << (L - 1 - i));
			else if(a[i] == '0') A |= (1 << (L - 1 - i));
			else C |= (1 << (L - 1 - i));
		}
		int mn = min({cnt[A], cnt[B], cnt[C]});
		if(cnt[A] == mn) { 
			int ans = sp[B];
			for(int i = A; i > 0; i = (i - 1) & A) {
				ans += sp[i | B] * ((cnt[i] & 1) ? -1 : 1);
			}
			return ans;
		}
		else if(cnt[B] == mn) { 
			int ans = sb[C] * ((cnt[B] & 1) ? -1 : 1);
			for(int i = B; i > 0; i = (i - 1) & B) {
				ans += sb[C | i] * (((cnt[B] - cnt[i]) & 1) ? -1 : 1);
			}
			return ans;
		}
		else {
			int ans = s[B] - '0';
			for(int i = C; i > 0; i = (i - 1) & C) {
				ans += s[B | i] - '0';
			}
			return ans;
		}
	} 
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int L, Q; cin >> L >> Q;
	string s; cin >> s;
	init_(L, s);
	rep(i, 1, Q) {
		string cur; cin >> cur;
		cout << query(cur) << "\n";
	}
	return 0;
}

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
struct pt {
	int x, y, id;
	bool operator<(pt b) {
		if(x != b.x) return x < b.x;
		else return y < b.y;
	}
};
vector<int> suffix_array(string s) {
	int n = s.size(), lg = 32 - __builtin_clz(n);
	vector<pt> cur(n, {0, 0, 0});
	vector<int> rk(n + 1, -1); 
	rep(i, 0, n - 1) {
		cur[i] = {s[i], 0, i};
	}
	rep(i, 0, lg) {
		int k = 1 << i;
		sort(all(cur));
		rep(j, 0, n - 1) {
			bool yes = 0;
			if(j) yes = bool(
				cur[j - 1].x == cur[j].x && 
				cur[j - 1].y == cur[j].y
			);
			rk[cur[j].id] = (yes ? rk[cur[j - 1].id]: j);
		}
		rep(j, 0, n - 1) {
			cur[j] = {
				rk[j], rk[min(n, j + k)], j
			};
		}
	}
	sort(all(cur));
	vector<int> ans;
	rep(i, 0, n - 1) ans.push_back(cur[i].id);
	return ans;
}
signed main() {
	string s; getline(cin, s);
	vector<int> arr = suffix_array(s);
	for(auto i : arr) {
		cout << i << "\n";
	}
	return 0;
}

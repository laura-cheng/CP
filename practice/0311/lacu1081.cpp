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
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct sub3 {
	int n, ans;
	vector<int> h, dpa, dpb;
	void init_(int _n) {
		n = _n;
		h.assign(n + 1, 0);
	}
	void solve1(int x0) {
		set<pii> s;
		dpa.assign(n + 1, 0);
		dpb.assign(n + 1, 0);
		ans = 0;
		rrep(i, 1, n) {
			auto it = s.lower_bound({h[i], 0});
			auto cur = it;
			pii a = {INF, 0}, b = {INF, 0}, c = {INF, 0};
			// move left
			if(cur != s.begin()) {
				cur = prev(cur);
				if(abs(cur -> first - h[i]) <= x0) {
					c = {abs(cur -> first - h[i]), cur -> second};
					if(c.first < a.first) b = a, a = c;
					else if(c.first < b.first) b = c;
				}
			}
			if(cur != s.begin()) {
				cur = prev(cur);
				if(abs(cur -> first - h[i]) <= x0) {
					c = {abs(cur -> first - h[i]), cur -> second};
					if(c.first < b.first) b = c;
				} 
			}
			// move right
			cur = it;
			if(cur != s.end()) {
				if(abs(cur -> first - h[i]) <= x0) {
					c = {abs(cur -> first - h[i]), cur -> second};
					if(c.first < a.first) b = a, a = c;
					else if(c.first < b.first) b = c;
				}
			}
			if(cur != s.end()) cur = next(cur);
			if(cur != s.end()) {
				if(abs(cur -> first - h[i]) <= x0) {
					c = {abs(cur -> first - h[i]), cur -> second};
					if(c.first < b.first) b = c;
				}
			}
			// cal answer
			if(a.first != INF) dpa[i] = dpa[a.second] + a.first;
			if(b.first != INF) dpb[i] = dpb[b.second] + b.first;

			int v1 = dpb[i] * dpa[ans], v2 = dpb[ans] * dpa[i];
			if(dpa[i] == 0 || dpb[i] == 0);
			else if(v1 < v2 || v1 == v2 && h[i] > h[ans]) ans = i;

			s.insert({h[i], i});
 		}
 		cerr << "a ";
 		vprint(all(dpa));
 		cerr << "b ";
 		vprint(all(dpb));
	}
	pii solve2(int s, int x) {
		solve1(x);
		return {dpb[s], dpa[s]};
	}
} a;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	a.init_(n);
	rep(i, 1, n) cin >> a.h[i];
	int x; cin >> x;
	a.solve1(x);
	cout << a.ans << "\n";
	int m; cin >> m;
	rep(i, 1, m) {
		int s, x; cin >> s >> x;
		pii ans = a.solve2(s, x);
		cout << ans.first << " " << ans.second << "\n";
	}
	
	return 0;
} 

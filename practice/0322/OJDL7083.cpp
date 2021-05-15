#define wiwihorz
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#pragma GC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define int __int128
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
bool lldmp(lld a, lld b) {
	return abs(a - b) <= eps;
}
struct pt {
	int x, y;
	pt operator-(pt b) { return {x - b.x, y - b.y};}
	pt operator+(pt b) { return {x + b.x, y + b.y};}
	int operator^(pt b) { return x * b.y - y * b.x;}
	int operator*(pt b) { return x * b.x + y * b.y;}
	lld len() { return sqrt(x * x + y * y);}
	bool operator<(pt b) {
		if(x != b.x) return x < b.x;
		else return y < b.y;
	}
};
struct AC {
	int n, m;
	vector<pt> a;
	vector<vector<pt>> b;
	vector<vector<lld>> dp;
	vector<int> id;
	void init_(int _n) {
		n = _n, m = 0;
		dp.clear();
		a.clear();
		b.clear();
		id.clear();
	}
	void add_poly(vector<pt> v) {
		m += v.size();
		int ii = (id.size() ? id.back() + 1: 0);
		for(auto i : v) {
			a.push_back(i);
			id.push_back(ii);
		}
		b.push_back(v);
		return;
	}
	bool onseg(pt o, pt a, pt b) {
		int aa = (a - o) ^ (b - o);
		int bb = (a - o) * (b - o);
		return aa == 0 && bb <= 0;
	}
	int ori(pt o, pt a, pt b) {
		int aa = (a - o) ^ (b - o);
		if(aa == 0) return 0;
		else if(aa < 0) return -1;
		else return 1;
	}
	bool banana(pt a, pt b, pt c, pt d) {
		if(onseg(a, c, d) || onseg(b, c, d) 
			|| onseg(c, a, b) || onseg(d, a, b)) return false;
		if(ori(a, c, d) * ori(b, c, d) == -1 &&
			ori(c, a, b) * ori(d, a, b) == -1) return true;
		else return false;
		
	}
	bool yes(pt aa, pt bb) {
		
		for(auto i : b) {
			rep(j, 0, i.size() - 1) {
				int cur = j, nxt = (j + 1) % i.size();
				if(banana(aa, bb, i[cur], i[nxt])) return false;
			}	
		}
		return true;
	}
	void build() {
		dp.assign(m + 1, vector<lld>(m + 1, INF));
		rep(i, 0, m - 1) rep(j, 0, m - 1) {
			if(id[i] != id[j] && yes(a[i], a[j]) || i == j) dp[i][j] = (a[i] - a[j]).len();
			else dp[i][j] = INF;
 		}
 		rep(k, 0, m - 1) rep(i, 0, m - 1) rep(j, 0, m - 1) {
 			dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
 		}
 		rep(i, 0, m - 1) rep(j, 0, m - 1) print((long long )i, (long long)j, (lld )dp[i][j]);
		return;
	}
	lld query(pt aa, pt bb) {
		lld ans = INF;
		rep(i, 0, m - 1) rep(j, 0, m - 1) {
			if(yes(aa, a[i]) && yes(bb, a[j])) {
				ans = min(ans, (aa - a[i]).len() 
					+ dp[i][j] + (bb - a[j]).len());
			}
		}
		return ans;
	}

} ac;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	signed n, q; cin >> n >> q;
	ac.init_(n);
	rep(i, 1, n) {
		signed k; cin >> k;
		vector<pt> cur;
		rep(j, 1, k) {
			signed x, y; cin >> x >> y;
			cur.push_back({x, y});
		}
		ac.add_poly(cur);
	}
	ac.build();
	rep(i, 1, q) {
		signed x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		cout << fixed << setprecision(6) 
			<< ac.query({x1, y1}, {x2, y2}) << "\n";
	}
	return 0;
}

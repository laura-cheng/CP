//#define wiwihorz
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <cassert>
#pragma GC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1e20
#define MOD 1000000007
#define eps (1e-8)
#define MAXN 1000005

#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define int long long int
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
bool lldcmp(lld a, lld b) {
	return abs(a - b) <= eps;
}
struct pt {
	lld x, y;
	pt operator-(pt b) { return {x - b.x, y - b.y};}
	pt operator+(pt b) { return {x + b.x, y + b.y};}
	lld operator^(pt b) { return x * b.y - y * b.x;}
	lld operator*(pt b) { return x * b.x + y * b.y;}
	lld len() { return sqrt(x * x + y * y);}
	bool operator<(pt b) {
		if(!lldcmp(x, b.x)) return x < b.x;
		else return y < b.y;
	}
};
namespace AC {
	int n, m;
	vector<pt> a;
	vector<vector<pt>> b;
	vector<vector<lld>> dp;
	void init_(int _n) {
		n = _n, m = 0;
		dp.clear();
		a.clear(), b.clear();
	}
	void add_poly(vector<pt> v) {
		m += v.size();
		for(auto i : v) a.push_back(i);
		b.push_back(v);
		return;
	}
	bool onseg(pt o, pt a, pt b) {
		return lldcmp((a - o) ^ (b - o), 0) && ((a - o) * (b - o)) <= 0;
	}
	int ori(pt o, pt a, pt b) {
		lld aa = (a - o) ^ (b - o);
		if(lldcmp(aa, 0)) return 0;
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
	bool on_poly(pt pa, pt pb, int id) {
		bool aa = 0, bb = 0;
		rep(i, 0, signed(b[id].size()) - 1) {
			int cur = i, nxt = (i + 1) ;
			if(cur + 1 == b[id].size()) nxt = 0;
			int ca = onseg(pa, b[id][cur], b[id][nxt]);
			int cb = onseg(pb, b[id][cur], b[id][nxt]);
			if(ca && cb) return true;
			bb |= cb, aa |= ca;
		}
		return (!aa) || (!bb);
	}
	bool pass_poly(pt pa, pt pb, int id) {
		rep(i, 0, signed(b[id].size()) - 1) {
			int cur = i, nxt = (i + 1);
			if(cur + 1 == b[id].size()) nxt = 0;
			if(banana(pa, pb, b[id][cur], b[id][nxt])) return false;
		}
		return true;
	}
	bool pass(pt a, pt b) {
		if(lldcmp(a.x, b.x) && lldcmp(a.y, b.y)) return true;
		rep(i, 0, n - 1) if(!on_poly(a, b, i)) return false;
		rep(i, 0, n - 1) if(!pass_poly(a, b, i)) return false;
		return true; 
	}
	void build() {
		dp.assign(m + 1, vector<lld>(m + 1, INF));
		rep(i, 0, m - 1) rep(j, i, m - 1) {
			if(pass(a[i], a[j])) dp[i][j] = dp[j][i] = (a[i] - a[j]).len();
		}
		rep(k, 0, m - 1) rep(i, 0, m - 1) rep(j, 0, m - 1) {
			dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
		}
	}
	lld query(pt aa, pt bb) {
		if(pass(aa, bb) || !n) return (aa - bb).len();
		lld ans = INF;
		vector<lld> da(m, 0), db(m, 0);
		vector<bool> pa(m, 0), pb(m, 0);
		rep(i, 0, m - 1) {
			da[i] = (a[i] - aa).len();
			db[i] = (a[i] - bb).len();
			pa[i] = pass(a[i], aa);
			pb[i] = pass(a[i], bb);
		}
		rep(i, 0, m - 1) rep(j, 0, m - 1) {
			if(!pa[i] || !pb[j]) continue;
			ans = min(ans, da[i] + db[j] + dp[i][j]);
		}
		return ans;
	}

};
using namespace AC;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	signed n, q; cin >> n >> q;
	init_(n);
	rep(i, 1, n) {
		signed k; cin >> k;
		vector<pt> cur;
		rep(j, 1, k) {
			lld x, y; cin >> x >> y;
			cur.push_back({x, y});
		}
		add_poly(cur);
	}
	build();
	rep(i, 1, q) {
		lld x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		cout << fixed << setprecision(6) << query({x1, y1}, {x2, y2}) << "\n";
	}
	return 0;
}

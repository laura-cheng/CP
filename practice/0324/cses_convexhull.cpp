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
#define eps (1e-9)
#define MAXN 1000005

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random t19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {
	while(L < R) cerr << *L << " \n"[next(L) == R];
}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct pt {
	int x, y;
	bool operator<(pt b) {
		if(x != b.x) return x < b.x;
		return y < b.y;
	}
	int operator*(pt b) {return x * b.x + y * b.y;}
	int operator^(pt b) {return x * b.y - y * b.x;}
	pt operator+(pt b) {return {x + b.x, y + b.y};}
	pt operator-(pt b) {return {x - b.x, y - b.y};}
};
namespace SOLVE {
	int n;
	vector<pt> a, hull;
	void init_(int _n) {
		n = _n;
		a.assign(n, {0 ,0});
		hull.clear();	
	}
	bool check(pt o, pt a, pt b) {
		return ((a - o) ^ (b - o)) >= 0;
	}
	void convex_hull() {
		sort(all(a));
		for(auto i : a) {
			while(hull.size() > 1 && !check(
				hull[hull.size() - 2],
				hull[hull.size() - 1],
				i
			)) hull.pop_back();
			hull.push_back(i);
		}
		int h = hull.size() - 1;
		hull.pop_back();
		reverse(all(a));
		for(auto i : a) {
			while(hull.size() > h && !check(
				hull[hull.size() - 2],
				hull[hull.size() - 1],
				i
			)) hull.pop_back();
			hull.push_back(i);
		}
		hull.pop_back();
		return;
	}
	void solve() {
		convex_hull();
		cout << hull.size() << "\n";
		for(auto i : hull) {
			cout << i.x << " " << i.y << "\n";
		}
	}
};
using namespace SOLVE;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 0, n - 1) {
		cin >> a[i].x >> a[i].y;
	}
	solve();
	
	
	return 0;
}

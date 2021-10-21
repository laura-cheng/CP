#include <iostream>
#include <algorithm>
#include <vector>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define MOD 1000000007
#define MAXN 1000005
#define INF 1000000000000000000
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
	pt() {}
	pt(int _x, int _y) : x(_x), y(_y) {}
	bool operator<(pt b) {
		if(x != b.x) return x < b.x;
		else return y < b.y;
	}
	pt operator+(pt b) {return pt(x + b.x, y + b.y);}
	pt operator-(pt b) {return pt(x - b.x, y - b.y);}
	int operator^(pt b) {return x * b.y - y * b.x;}
	int operator*(pt b) {return x * b.x + y * b.y;}
	int len() {return x * x + y * y;}
};
vector<pt> a, hull;
int h;
bool check(pt o, pt a, pt b) {
	int aa = (a - o) ^ (b - o);
	return aa > 0;
}
vector<pt> convex_hull(vector<pt> a) {
	vector<pt> hull;
	sort(all(a));
	rep(k, 0, a.size() - 1) {
		pt i = a[k];
		while(hull.size() > 1 && !check(
			hull[hull.size() - 2],
			hull[hull.size() - 1],
			i
		)) hull.pop_back();
		hull.push_back(i);
	}
	hull.pop_back();
	h = hull.size();
	reverse(all(a));
	rep(k, 0, a.size() - 1) {
		pt i = a[k];
		while(hull.size() > h + 1 && !check(
			hull[hull.size() - 2],
			hull[hull.size() - 1],
			i
		)) hull.pop_back();
		hull.push_back(i);
	}
	hull.pop_back();
	return hull;
}
bool check1(pt a, pt b, pt c, pt d) {
	int aa = abs((a - c) ^ (b - c));
	int bb = abs((a - d) ^ (b - d));
	return aa < bb;
}
int solve() {
	int ans = 0, d = h, n = hull.size();
	rep(i, 0, n - 1) {
		while(check1(
			hull[i], hull[(i + 1) % n],
			hull[d], hull[(d + 1) % n]
		)) d = (d + 1) % n;
		ans = max(ans, (hull[i] - hull[d]).len());
		ans = max(ans, (hull[(i + 1) % n] - hull[d]).len());
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	rep(i, 1, n) {
		int x, y; cin >> x >> y;
		a.push_back(pt(x, y));
	}
	hull = convex_hull(a);
	cout << solve() << "\n";
	return 0;
}


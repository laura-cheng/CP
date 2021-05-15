#define wiwihorz
#include <bits/stdc++.h>
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
bool lldmp(lld a, lld b) {
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
struct AC {
	int n;
	vector<pt> a;
	vector<vector<lld>> dp;
	void init_(int _n) {
		a.clear();
		n = _n;
		dp.assign(n + 1, vector<int>(n + 1, INF));
	}
	bool check(pt o, pt a, pt b) {	
		lld aa = (a - o) ^ (b - o);
		return aa >= 0;
	}
	void build() {
	
	
	}
	bool banana(pt a, pt b, pt c, pt d) {
		
	}
	lld solve() {
	
	}

} ac;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	
	return 0;
}

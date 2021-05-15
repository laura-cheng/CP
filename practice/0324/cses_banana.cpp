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
		else return y < b.y;
	}
	int operator*(pt b) { return x * b.x + y * b.y; }
	int operator^(pt b) { return x * b.y - y * b.x; }
	pt operator+(pt b) { return {x + b.x, y + b.y}; }
	pt operator-(pt b) { return {x - b.x, y - b.y}; }
};
namespace SOLVE {
	bool onseg(pt o, pt a, pt b) {
		int aa = (a - o) ^ (b - o);
		int bb = (a - o) * (b - o);
		return aa == 0 && bb <= 0;
	}
	int ori(pt o, pt a, pt b) {
		int aa = (a - o) ^ (b - o);
		if(aa == 0) return 0;
		if(aa < 0) return -1;
		if(aa > 0) return 1;
	}
	bool banana(pt a, pt b, pt c, pt d) {
		if(onseg(a, c, d) || onseg(b, c, d) || 
			onseg(c, a, b) || onseg(d, a, b)) return true;
		if(ori(a, c, d) * ori(b, c, d) == -1 && 
			ori(c, a, b) * ori(d, a, b) == -1) return true;
		return false;
	}
};
using namespace SOLVE;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	pt v[4];
	while(t--) {
		rep(i, 0, 3) cin >> v[i].x >> v[i].y;
		if(banana(v[0], v[1], v[2], v[3])) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}

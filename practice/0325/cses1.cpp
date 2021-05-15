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
#define eps (1e-9)
#define MOD 1000000007

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
	pt operator-(pt b) {return {x - b.x, y - b.y};}
	int operator^(pt b) { return x * b.y - y * b.x; }
};
namespace SOLVE {
	string dir(pt a, pt b, pt o) {
		int aa = (b - a) ^ (o - a);
		if(aa == 0) return "TOUCH";
		else if(aa < 0) return "RIGHT";
		else return "LEFT";
	}
};
using namespace SOLVE;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		pt a, b, o;
		cin >> a.x >> a.y;
		cin >> b.x >> b.y;
		cin >> o.x >> o.y;
		cout << dir(a, b, o) << "\n";
	}
	
	return 0;
}

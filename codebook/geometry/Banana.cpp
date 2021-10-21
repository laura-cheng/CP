#define wiwihorz
#include <bits/stdc++.h>
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
	bool operator<(pt b) {
		if(x != b.x) return x < b.x;
		else return y < b.y;
	}
	pt operator+(pt b) {return {x + b.x, y + b.y};}
	pt operator-(pt b) {return {x - b.x, y - b.y};}
	int operator^(pt b) {return x * b.y - y * b.x;}
	int operator*(pt b) {return x * b.x + y * b.y;}
};
vector<pt> a;
bool onseg(pt a, pt b, pt o) {
	int aa = (a - o) ^ (b - o);
	int bb = (a - o) * (b - o);
	return (aa == 0) && (bb <= 0);
}
int dir(pt a, pt b, pt o) {
	int aa = (a - o) ^(b - o);
	if(aa == 0) return 0;
	else if(aa > 0) return 1;
	else return -1;
}
bool banana(pt a, pt b, pt c, pt d) {
	if(onseg(a, b, c) || onseg(a, b, d)) return true;
	if(onseg(c, d, a) || onseg(c, d, b)) return true;
	if(dir(a, b, c) * dir(a, b, d) == -1 && 
		dir(c, d, a) * dir(c, d, b) == -1) return true;
	return false;
}
int n, t;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> t;
	a.assign(4, {0, 0});
	while(t --) {
		rep(i, 0, 3) cin >> a[i].x >> a[i].y;
		if(banana(a[0], a[1], a[2], a[3])) cout << "Yes\n";
		else cout << "No\n";
	}
	return 0;
}


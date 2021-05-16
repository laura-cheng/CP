#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MOD 1000000007
#define INF 1000000000000000000
#define MAXN 1000005
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int,int>
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
int n;
const lld PI = 3.1415926535;
struct pt {
	int x, y;
	bool operator<(pt b) {
		if(x != b.x) return x < b.x;
		else return y < b.y;
	}
	lld rad() {return atan2(y, x);}
	pt operator+(pt b) {return {x + b.x, y + b.y};}
	pt operator-(pt b) {return {x - b.x, y - b.y};}
	int operator^(pt b) {return x * b.y - y * b.x;}
	int operator*(pt b) {return x * b.x + y * b.y;}
	int len() {return x * x + y * y;}
};
bool cmp(pt a, pt b) {
	pt zero = {0, 0};
	bool foo1 = a < zero, foo = b < zero;
	if(foo != foo1) return foo > foo1;
	else return (a ^ b) > 0;
}
vector<pt> a, b, c;
vector<int> cnt;
int solve(pt x) {
	b.clear(), c.clear(), cnt.clear();
	for(auto i : a) {
		pt cur = i - x;
		if(cur.x == 0 && cur.y == 0) continue;
		b.push_back(cur);
	}
	sort(all(b), cmp);
	c.push_back(b[0]), cnt.push_back(1);
	rep(i, 1, signed(b.size()) - 1) {
		if((b[i] * b[i - 1]) > 0 && 
			(b[i] ^ b[i - 1]) == 0) 
			cnt[cnt.size() - 1] ++;
		else cnt.push_back(1), c.push_back(b[i]);
	}
	int sz = c.size();
	rep(i, 0, sz - 1) {
		c.push_back(c[i]);
		cnt.push_back(cnt[i]);
	}
	int ans = 0, r = 0;
	rep(i, 0, sz - 1) {
		while(r < i + sz && (c[i] ^ c[r]) >= 0 && 
			(c[i] * c[r]) > 0) r ++;
		if((c[i] * c[r]) == 0 &&
			(c[i] ^ c[r]) > 0) ans += cnt[i] * cnt[r]; 
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	while(cin >> n && n) {
		a.clear();
		rep(i, 1, n) {
			int x, y; cin >> x >> y;
			a.push_back({x, y});
		}
		int ans = 0;
		rep(i, 0, a.size() - 1) {
			ans += solve(a[i]);
		}
		cout << ans << "\n";
	}
 	return 0;
}
/*
5
1 2
1 3
5 6
2 4
4 3
*/

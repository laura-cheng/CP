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
#define eps (1e-10)
#define MAXN 1000005

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
bool lldcmp(lld a, lld b) {
	return abs(a - b) <= eps;
}
const lld PI = acos(-1);
int solve(vector<pii> a, int n) {
	vector<lld> neg, pos;
	for(auto i : a) {
		lld x = atan2(i.second, i.first);
		if(lldcmp(0, x)) neg.push_back(0);
		else if(x < 0) neg.push_back(-x);
		else pos.push_back(x);
	}
	sort(all(neg)), sort(all(pos));
	if(!neg.size() || !pos.size()) return 0;
	int r = signed(pos.size()) - 1, ans = 0;
	rep(i, 0, signed(neg.size()) - 1) {
		int aa = i, bb = r;
		while(aa < signed(neg.size()) - 1 
			&& lldcmp(neg[aa + 1], neg[i])) aa ++; 
		while(bb >= 0 && !lldcmp(pos[bb], PI - neg[i])) bb --;		
		r = max(bb, 0ll);
		while(r > 0 && lldcmp(pos[r - 1], PI - neg[i])) r --;
		ans += (aa - i + 1) * (bb - r + 1);
		i = aa;
	} 	
	return ans;		
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n; cin >> n;
		vector<pii> a;
		rep(i, 1, n) {
			int x, y, u, v;
			cin >> x >> y >> u >> v;
			a.push_back({u - x, v - y});
		} 
		cout << solve(a, n) << "\n";
	}	
	return 0;
}

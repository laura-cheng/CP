#define wiwihorz
#include <bits/stdc++.h> 
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i  = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1)/ (b))

#define MOD 1000000007
#define MAXN 1000005
#define INF 1000000000000000000ll
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_eince_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) out("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void out() {cerr << endl;}
template<class T1, class ... T2> void out(T1 a, T2 ... e) {cerr << a << " ", out(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
using namespace std;
struct seg {
	int x, l, r;
};
int n, m, x, y;
vector<pii> a, b;
vector<seg> dq;
int area(int i, int j) {
	int ans = (
		(b[j].x - a[i].x) *
		(a[i].y - b[j].y)
	);
	return ans;
}
int bs(int a, int b) {
	int l = -1, r = m + 1;
	while(r - l > 1) {
		int mid = (l + r) / 2;
		if(area(b, mid) >= area(a, mid)) r = mid;
		else l = mid;
	} 
	return r;
}
int solve() {
	int ii = 1;
	dq.assign(n + 5, {0, 0, 0});
	dq[ii] = {0, 0, m};
	rep(i, 1, n) {
		while(ii && area(i, dq[ii].l) 
			>= area(dq[ii].x, dq[ii].l)) ii --;
		if(ii) {
			int aa = bs(dq[ii].x, i);
			dq[ii].r = aa - 1;
			dq[++ii] = {i, aa, m};
		}
		else dq[++ii] = {i, 0, m};
		
	}
	int ans = 0; ii = 1;
	rep(i, 0, m) {
		if(dq[ii].r < i) ii ++;
		ans = max(ans, area(dq[ii].x, i));
	}
	return ans;
} 
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	x = 0, y = 0, a.push_back({0, 0});
	rep(i, 1, n) {
		int aa; cin >> aa;
		if(i & 1) y += aa;
		else x += aa;
		a.push_back({x, y});
	}
	cin >> m;
	x = 0, y = 0, b.push_back({0, 0});
	rep(i, 1, m) {
		int aa; cin >> aa;
		if(i & 1) x += aa;
		else y += aa;
		b.push_back({x, y});
	}
	cout << solve() << "\n";
	return 0;
} 

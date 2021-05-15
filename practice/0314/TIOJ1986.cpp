#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i= b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define MAXN 1000005
#define eps (1e-9)

#define ll long long int
#define lld long double
#define pii pair<int, int> 
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {
	while(L < R) cerr << *L << " \n"[next(L) == R], ++L;
}
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace io {
	const int size = 1e7 + 10;
	char buff[size];
	char *l, *r;
	inline void init() {
		l = buff;
		r = buff + fread(buff, 1, size, stdin);
	}
	inline char gc() {
		if(l == r) init();
		return (l != r) ? *(l++) : EOF;
	}
	void read(int &n) {
		n = 0; char c = gc();
		while(!isdigit(c)) c = gc();
		while(isdigit(c)) n = n * 10 + c - '0', c = gc();
	}
} using io::read;
struct DP3 {
	int n, k;
	vector<ll> a, dp;
	vector<int> cnt;
	struct seg {
		int L, R, id;
	};
	vector<seg> dq;
	struct res {
		ll t, v;
	};
	void init_(int _n, int _k) {
		n = _n, k = _k;
		k = min(k, n);
		dp.assign(n + 1, 0);
		cnt.assign(n + 1, 0);
		a.assign(n + 1, 0);
		dq.assign(n + 10, {0, 0, 0});
		return;
	}
	ll w(int i, int j) {
		int x = (i + 1 + j) / 2, y = ceil(i + 1 + j, 2);
		ll ans1 = INF, ans2 = INF;
		ans1 = a[j] - a[x] - (a[x] - a[x - 1]) * (j - x) +
			(a[x] - a[x - 1]) * (x - i) - a[x] + a[i];
		ans2 = a[j] - a[y] - (a[y] - a[y - 1]) * (j - y) +
			(a[y] - a[y - 1]) * (y - i) - a[y] + a[i];
		return min(ans1, ans2);
	}
	ll f(int i, int j) {
		if(i >= j) return INF;
		ll ans = dp[i]  + w(i, j);
		return ans;
	}
	int bs(int L, int R, int i, int j) {
		R ++;
		while(R - L > 1) {
			int mid = (L + R) / 2;
			if(f(i, mid) > f(j, mid)) R = mid;
			else L = mid;
		}
		return R;
	
	}
	res check(int x) {
		int l = 1, r = 1;
		dq[1] = {0, n, 0}, dp[0] = 0;
		rep(i, 1, n) {
			while(dq[l].R < i) l++;
			dp[i] = f(dq[l].id, i) + x;
			cnt[i] = cnt[dq[l].id] + 1;
			while(l <= r && f(dq[r].id, dq[r].L) 
				> f(i, dq[r].L)) r--;
			if(l <= r) {
				int ii = bs(dq[r].L, dq[r].R, dq[r].id, i);
				dq[r].R = ii - 1;
			}
			if(dq[r].R < n) dq[++r] = {dq[r - 1].R + 1, n, i};
			  
		}
		return {cnt[n], dp[n]};
	}
	ll solve() {
		sort(all(a));
		rep(i, 1, n) a[i] += a[i - 1];
		ll l = 0, r = 1e10;
		while(r - l > 1) {
			int mid = (l + r) / 2;
			res cur = check(mid);
			if(cur.t > k) l = mid;
			else r = mid;	
		}
		res a = check(r), b = check(l);
		if(a.t == b.t) return -a.t * r + a.v;
		else {
			ll sm = a.v - r * a.t, bg = b.v -l * b.t;
			return sm + (bg - sm) * (k - a.t) / (b.t - a.t); 
		}
	} 
} dp;

signed main() {

	int n, k; read(n), read(k);
	dp.init_(n, k);
	rep(i, 1, n) {
		int x; read(x);
		dp.a[i] = x;
	}
	printf("%lld\n", dp.solve());
	return 0;
}

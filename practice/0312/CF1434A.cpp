#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i ,a, b) for(int i = b; i >= a; i--)
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
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct AC {
	int n, yes, a[6];
	vector<int> cnt;
	vector<pii> b;
	void init_(int _n) {
		n = _n, yes = 0;
		cnt.assign(n + 1, 0);
		b.clear();
	}
	int solve() {
		sort(all(b));
		int r = -1, ans = INF;
		rep(i, 0, b.size() - 1) {
			while(r + 1 < b.size() && yes != n) {
				r ++;
				cnt[b[r].second] ++;
				if(cnt[b[r].second] == 1) {
					yes ++;
				}
			}
			if(yes == n) {
				ans = min(ans, b[r].first - b[i].first); 
			}
			cnt[b[i].second] --;
			if(cnt[b[i].second] == 0) yes --;
		}
		return ans;
	}
} ac;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	rep(i, 0, 5) cin >> ac.a[i];
	int n; cin >> n;
	ac.init_(n);
	rep(i, 1, n) {
		int x; cin >> x;
		rep(j, 0, 5) ac.b.push_back({x - ac.a[j], i});
	}
	cout << ac.solve() << "\n";
	return 0;
}

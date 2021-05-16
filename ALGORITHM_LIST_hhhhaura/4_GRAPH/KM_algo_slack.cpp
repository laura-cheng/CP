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
#define MAXN 1000005
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
const int P = 500;
struct KM {
	int n, ii, slack[P];
	int Lx[P], Ly[P], match[P];
	int visx[P], visy[P];
	int a[P][P];
	void init_(int _n) {
		n = _n, ii = 0;
		rep(i, 1, n) {
			slack[i] = INF;
			visx[i] = visy[i] = 0;
			Lx[i] = Ly[i] = 0;
			match[i] = -1;
			rep(j, 1, n) a[i][j] = 0;
		}
	}
	bool dfs(int x, bool aug) {
		if(visx[x] == ii) return false;
		visx[x] = ii;
		rep(i, 1, n) if(visy[i] != ii) {
			int cur = Lx[x] + Ly[i] - a[x][i];
			if(cur == 0) {
				visy[i] = ii;
				if(match[i] == -1 || dfs(match[i], aug)) {
					if(aug) match[i] = x;
					return true;
				}
			}
			else slack[i] = min(slack[i], cur);
		}
		return false;
	}
	bool augment() {
		rep(i, 1, n) if(visy[i] != ii && slack[i] == 0) {
			visy[i] = ii;
			if(match[i] == -1 || dfs(match[i], false)) {
				return true;
			}
		}
		return false;
	}
	void relabel() {
		int ans = INF;
		rep(i, 1, n) if(visy[i] != ii) 
			ans = min(ans, slack[i]);
		rep(i, 1, n) {
			if(visy[i] == ii) Ly[i] += ans;
			else slack[i] -= ans;
			if(visx[i] == ii) Lx[i] -= ans;
		}
	}
	int solve() { 
		rep(i, 1, n) rep(j, 1, n) 
			Lx[i] = max(Lx[i], a[i][j]);
		int ans = 0;
		rep(i, 1, n) {
			rep(j, 1, n) slack[j] = INF;
			ii ++;
			if(dfs(i, true)) continue;
			while(!augment()) relabel();
			ii ++;
			assert(dfs(i, true));
		}
		rep(i, 1, n) ans += a[match[i]][i];
		return ans;
	}
}km;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n;
	while(cin >> n && n) {
		km.init_(n);
		rep(i, 1, n) rep(j, 1, n) {
			int x; cin >> x;
			km.a[i][j] = max(0ll, x);
		}
		cout << km.solve() << "\n";
	}
	return 0;
}
 

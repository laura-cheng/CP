#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optmize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1)/ (b))

#define MAXN 150
#define INF 1000000000000000000
#define eps (1e-9)
#define MOD 1000000007

#define int long long int
#define lld long double
#define pii pair<int ,int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {while(L < R) cerr << *L << " \n"[next(L) == R], ++ L;}
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {cerr << a << " ", kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
int n, mp[MAXN][MAXN], ii;
int match[MAXN], Lx[MAXN], Ly[MAXN];
int visx[MAXN], visy[MAXN];
bool dfs(int x) {
	if(visx[x] == ii) return false;
	visx[x] = ii;
	rep(i, 1, n) {
		if(visy[i] != ii && Lx[x] + Ly[i] == mp[x][i]) {
			visy[i] = ii;
			if(match[i] == -1 || dfs(match[i])) {
				match[i] = x;
				return true;
			}
		}
	}
	return false;
}
bool augment(int x) {
	ii ++;
	return dfs(x); 
}
void relabel() {
	int ans = INF;
	rep(i, 1, n) if(visx[i] == ii) {
		rep(j, 1, n) if(visy[j] != ii) {
			ans = min(ans, Lx[i] + Ly[j] - mp[i][j]);
		}
	}
	rep(i, 1, n) if(visx[i] == ii) Lx[i] -= ans;
	rep(i, 1, n) if(visy[i] == ii ) Ly[i] += ans;
	return;
}
int solve() {
	rep(i, 1, n) rep(j, 1, n) Lx[i] = max(Lx[i], mp[i][j]);
	rep(i, 1, n) while(!augment(i)) relabel();
	int ans = 0;
	rep(i, 1, n) {
		ans += mp[match[i]][i];
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	while(cin >> n && n) {
		ii = 0;
		rep(i, 1, n) rep(j, 1, n) mp[i][j] = 0;
		rep(i, 1, n) Lx[i] = Ly[i] = visx[i] = visy[i] = 0;
		rep(i, 1, n) match[i] = -1;
		rep(i, 1, n) rep(j, 1, n) {
			int x; cin >> x;
			mp[i][j] = max(mp[i][j], x);
		}
		cout << solve() << "\n";
	}
	return 0;
}
/*
4
90 80 80 80
80 20 10 10
85 70 20 10
80 60 80 10
0
*/

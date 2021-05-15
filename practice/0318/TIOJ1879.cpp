#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
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
	while(L < R) cerr << *L << " \n"[next(L) == R], ++ L;
}
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
bool cmp(vector<int> a, vector<int> b) {
	if(a.size() == 0) return 1;
	if(b.size() == 0) return 0;
	return a[0] < b[0];
}
struct BCC {
	int n;
	int timestamp, ii, bccid;
	vector<vector<int>> mp, bcc;
	vector<int> pre, L, D;
	void init_(int _n) {
		n = _n;
		ii = timestamp = bccid = 0;
		mp.assign(n + 1, vector<int>());
		pre.assign(n + 1, 0);
		L.assign(n + 1, 0);
		D.assign(n + 1, 0);
		bcc.assign(1, vector<int>());
	}
	void dfs(int x, int par) {
		L[x] = D[x] = ++ timestamp;
		pre[ii ++] = x;
		for(auto i : mp[x]) {
			if(i == par) continue;
			if(!D[i]) {
				dfs(i, x);
				L[x] = min(L[x], L[i]);
				if(L[i] > D[x]) {
					bccid ++;
					bcc.push_back(vector<int>());
					while(pre[ii] != i) {
						ii --;
						bcc[bccid].push_back(pre[ii]);
					}
 				}
			}
			else L[x] = min(L[x], D[i]);
		}
	}
	void solve() {
		dfs(0, 0);
		bccid++;
		bcc.push_back(vector<int>());
		while(ii) {
			ii --;
			bcc[bccid].push_back(pre[ii]);
		}
		rep(i, 1, bccid) sort(all(bcc[i]));
		sort(all(bcc));
		rep(i, 1, bccid) {
			cout << i << ":";
			for(auto j : bcc[i]) {
				cout << " " << j;
			}
			cout << "\n";
		}
		
	}
} bcc;

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	bcc.init_(n);
	rep(i, 1, m) {
		int a, b; cin >> a >> b;
		bcc.mp[a].push_back(b);
		bcc.mp[b].push_back(a);
	}
	bcc.solve();
	
	return 0;
}



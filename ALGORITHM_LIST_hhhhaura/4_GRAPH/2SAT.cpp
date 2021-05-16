#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MAXN 1000005
#define MOD 1000000007
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
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
int n, m, timestamp, sccid, ii;
vector<int> L, D, id, pre, instack;
vector<vector<int>> mp;
void init_() {
	L.assign(2 * n + 1, 0);
	D.assign(2 * n + 1, 0);
	id.assign(2 * n + 1, 0);
	pre.assign(2 * n + 1, 0);
	instack.assign(2 * n + 1, 0);
	mp.assign(2 * n + 1, vector<int>());
	timestamp = sccid = ii = 0;
}
int get(int x, int t) {
	return t * n + x;
}
void dfs(int x) {
	L[x] = D[x] = ++ timestamp;
	pre[ii ++] = x, instack[x] = 1;
	for(auto i : mp[x]) {
		if(!D[i]) {
			dfs(i);
			L[x] = min(L[x], L[i]);
		}
		else if(instack[i]) {
			L[x] = min(L[x], D[i]);
		}
	}
	if(L[x] == D[x]) {
		sccid ++;
		while(pre[ii] != x) {
			ii --, id[pre[ii]] = sccid;
			instack[pre[ii]] = 0;
		}
	}
	return;
}
bool solve() {
	rep(i, 1, 2 * n) {
		if(!D[i]) dfs(i);
	}
	rep(i, 1, n) {
		if(id[i] == id[i + n]) return false;
	}
	return true;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n >> m;
		init_();
		rep(i, 1, m) {
			string a, b; cin >> a >> b;
			int ai, ta, bi, tb;
			ai = stoi(a.substr(1, a.size() - 1));
			bi = stoi(b.substr(1, b.size() - 1));
			ta = (a[0] == 'h');
			tb = (b[0] == 'h');
			mp[get(ai, !ta)].push_back(get(bi, tb));
			mp[get(bi, !tb)].push_back(get(ai, ta));
		}
		if(solve()) cout << "GOOD\n";
		else cout << "BAD\n";
	}
	return 0;
}
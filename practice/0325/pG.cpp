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
int n, m, timestamp;
vector<int> D, L, ap;
vector<vector<int>> mp;
set<pii> s;
void init_() {
	L.assign(n + 1, 0);
	D.assign(n + 1, 0);
	mp.assign(n + 1, vector<int>());
	ap.clear();
	timestamp = 0;
	s.clear();
	return;
} 
void dfs(int x, int par) {
	D[x] = L[x] = ++timestamp;
	int ch = 0, isap = 0;
	for(auto i : mp[x]) {
		if(i == par) continue;
		if(!D[i]) {
			dfs(i, x), ch ++;
			L[x] = min(L[x], L[i]);
			if(L[i] >= D[x]) isap = 1;
		}
		else L[x] = min(L[x], D[i]);
		
	}
	if(x == par && ch < 2) isap = 0;
	if(isap) ap.push_back(x);
}
signed main() {
//	ios::sync_with_stdio(false), cin.tie(0);
	vector<int> ans;
	while(cin >> n && n) {
		init_(); int cur;
		while(cin >> cur && cur) {
			int x; char c = getchar(); 
			while(c != '\n') {
				x = 0;
				while(!isdigit(c)) {
					if(c == '\n') break;
					c = getchar();	
				}
				while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
				mp[cur].push_back(x);
				mp[x].push_back(cur);
				if(c == '\n') break;
			}
		}
		dfs(1, 1);
		ans.push_back(ap.size());
	}
	rep(i, 0, signed(ans.size()) - 1) {
		cout << ans[i] << "\n";
	}
	return 0;
}

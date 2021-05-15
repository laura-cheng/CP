//#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MAXN 1000005
#define eps (1e-9)
#define MOD 1000000007

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
struct DSU {
	int n, op, cnt;
	vector<int> par, sz;
	stack<pair<int*, int>> stack_sz, stack_par;
	void init_(int _n) {
		n = _n, op = 0, cnt = n;
		par.assign(n + 1, 0);
		sz.assign(n + 1, 1);
		rep(i, 1, n) par[i] = i;
		while(stack_sz.size()) stack_sz.pop();
		while(stack_par.size()) stack_par.pop();
	}
	int find_par(int a) {
		while(par[a] != a) a = par[a];
		return a;
	}
	void unite(int a, int b) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return;
		op ++, cnt --;
		if(sz[aa] < sz[bb]) swap(aa, bb);
		stack_sz.push({&sz[aa], sz[aa]});
		stack_par.push({&par[bb], par[bb]});
		sz[aa] += sz[bb], par[bb] = aa;
		return;
	}
	void undo() {
		pair<int*, int> aa, bb;
		aa = stack_sz.top(); stack_sz.pop();
		bb = stack_par.top(); stack_par.pop();
		cnt ++, op --;
		*aa.first = aa.second;
		*bb.first = bb.second;
		return;
	}
};
namespace SOLVE {
	int n, m;
	int dirx[] = {1, 0, 0, -1};
	int diry[] = {0, 1, -1, 0};
	vector<vector<char>> mp;
	vector<int> ans;
	DSU a, b;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		mp.assign(n + 1, vector<char>(m + 1, ' '));
		a.init_(n * m);
		b.init_(n * m);
		ans.clear();
	}
	int id(pii x) {
		return (x.first - 1) * m + x.second;
	}
	void solve() {
		rep(i, 1, n) rep(j, 1, m) {
			if(mp[i][j] == '.') continue;
			rep(k, 0, 3) {
				int nx = i + dirx[k];
				int ny = j + diry[k];
				if(nx < 1 || ny < 1 || nx > n || ny > m) continue;
				if(mp[nx][ny] == '.') continue; 
				a.unite(id({i, j}), id({nx, ny}));
			}
		}
		print(a.cnt);
		rep(k, 1, n * m) {
			vector<int> cur;
			rep(i, 1, n) rep(j, 1, m) {
				if(mp[i][j] != 'X' || a.find_par(id({i, j})) != k) continue;
				rep(kk, 0, 3) {
					int nx = i + dirx[kk];
					int ny = j + diry[kk];
					if(nx < 1 || ny < 1 || nx > n || ny > m) continue;
					if(mp[nx][ny] != 'X' || a.find_par(id({nx, ny})) != k) continue; 
					b.unite(id({i, j}), id({nx, ny}));
				}
			}
			rep(i, 1, n) rep(j, 1, m) {
				if(mp[i][j] != 'X' || a.find_par(id({i, j})) != k) continue;
				print(k, i, j);
				cur.push_back(b.find_par(id({i, j})));
			}
			sort(all(cur)), cur.resize(unique(all(cur)) - cur.begin());
			if(cur.size())print(k, cur.size()),vprint(all(cur)), ans.push_back(cur.size());
			while(b.op) b.undo();

		}
		sort(all(ans));
		
	}
	


};
using namespace SOLVE;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t = 0, n, m;
	while(cin >> m >> n && n) {
		init_(n, m), t++;
		rep(i, 1, n) rep(j, 1, m) {
			cin >> mp[i][j];
		}
		solve();
		cout << "Throw " << t << "\n";
		rep(i, 0, signed(ans.size()) - 1) {
			cout << ans[i] << " \n"[i + 1 == ans.size()];
		}
		cout << "\n";
		
	}
	
	return 0;
}

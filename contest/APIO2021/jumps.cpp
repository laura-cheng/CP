#define wiwihorz
#include "jumps.h"
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1e9
#define MOD 1000000007
#define eps (1e-9)

using namespace std;
using namespace __gnu_pbds;

//#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
namespace solver1 {
	void init(int N, vector<int> H) {
		
	}
	int minimum_jumps(int A, int B, int C, int D) {
		int l = max(A, C), r = min(B, D);
		if(l <= r) return 0;
		else if(D < A) return -1;
		else return C - B;
	}
};
namespace solver2 {
	int n, lg, root;
	vector<int> h, L, R, d;
	void init(int N, vector<int> H) {
		h = H, n = N, lg = 31 - __builtin_clz(n);
		root = -1;
		L.assign(n, -1);
		R.assign(n, -1);
		vector<int> st;
		rep(i, 0, n - 1) {
			if(root == -1 || h[root] < h[i]) root = i;
			while(st.size() && h[st.back()] < h[i]) {
				R[st.back()] = i;
				st.pop_back();
			}
			if(st.size()) L[i] = st.back();
			st.push_back(i);
		}
		st.clear();
	}
	int minimum_jumps(int A, int B, int C, int D) {
		vector<int> dis(n, INF);
		queue<int> q;
		rep(i, A, B) {
			dis[i] = 0;
			q.push(i);
		}
		while(q.size()) {
			int cur = q.front(); q.pop();
			if(L[cur] != -1 && dis[L[cur]] == INF) {
				dis[L[cur]] = dis[cur] + 1;
				q.push(L[cur]);
			} 
			if(R[cur] != -1 && dis[R[cur]] == INF) {
				dis[R[cur]] = dis[cur] + 1;
				q.push(R[cur]);
			}
		}
		int ans = INF;
		rep(i, C, D) ans = min(ans, dis[i]);
		if(ans == INF) return -1;
		return ans;
	}
};
namespace solver3 {
	int n, lg, root;
	vector<int> h, L, R, d, vis;
	vector<vector<int>> ac, mp, mp1;
	void dfs(int x, int par, int dd) {
		d[x] = dd, ac[0][x] = par;
		for(auto i : mp[x]) if(i != par) {
			dfs(i, x, dd + 1);
		}
	}
	int LCA(int a, int b) {
		if(d[a] < d[b]) swap(a, b);
		int need = d[a] - d[b];
		rep(i, 0, lg) if((need >> i) & 1) {
			a = ac[i][a];
		}
		if(a == b) return a;
		rrep(i, 0, lg) if(ac[i][a] != ac[i][b]) {
			a = ac[i][a];
			b = ac[i][b];
		}
		return ac[0][a];
	}
	void init(int N, vector<int> H) {
		h = H, n = N, lg = 31 - __builtin_clz(n);
		root = -1;
		L.assign(n, -1);
		R.assign(n, -1);
		mp.assign(n, vector<int>());
		mp1.assign(n, vector<int>());
		ac.assign(lg + 1, vector<int>(n, 0));
		d.assign(n, 0);
		vis.assign(n, 0);
		vector<int> st;
		rep(i, 0, n - 1) {
			if(root == -1 || h[root] < h[i]) root = i;
			while(st.size() && h[st.back()] < h[i]) {
				R[st.back()] = i;
				st.pop_back();
			}
			if(st.size()) L[i] = st.back();
			st.push_back(i);
		}
		st.clear();
		rep(i, 0, n - 1) {
			if(L[i] != -1) mp1[L[i]].push_back(i);
			if(R[i] != -1) mp1[R[i]].push_back(i);
		}
		queue<int> q; q.push(root);
		while(q.size()) {
			int cur = q.front(); q.pop();
			for(auto i : mp1[cur]) if(!vis[i]) {
				mp[i].push_back(cur);
				mp[cur].push_back(i);
				vis[i] = 1;
				q.push(i);
			}
		}
		dfs(root, root, 0);
		rep(i, 1, lg) rep(j, 0, n - 1) {
			ac[i][j] = ac[i - 1][ac[i - 1][j]];
		}
	}
	int minimum_jumps(int A, int B, int C, int D) {
		assert(A == B && C == D);
		int lca = LCA(A, C);
		if(lca != C) return -1;
		return d[A] - d[C];
	}
};
using namespace solver3;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; vector<int> h;
	cin >> n, h.assign(n, 0);
	rep(i, 0, n - 1) cin >> h[i];
	init(n, h);
	int q; cin >> q;
	while(q--) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		cout << minimum_jumps(a, b, c, d) << "\n";
	}
	return 0;
} */

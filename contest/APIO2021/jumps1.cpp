#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define INF 2e9
using namespace std;
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
//namespace solver {
	int n, lg;
	vector<int> h, L, R, dL, dR, deg;
	vector<vector<int>> sp, mp, pa;
	int query(int L, int R) {
		int t = 31 - __builtin_clz(R - L + 1);
		return max(sp[t][L], sp[t][R - (1 << t) + 1]);
	}
	void init(int N, vector<int> H) {
		h = H, n = N, lg = 31 - __builtin_clz(n);
		dL.assign(n, INF);
		dR.assign(n, INF);
		L.assign(n, -1);
		R.assign(n, -1);
		vector<int> st;
		rep(i, 0, n - 1) {
			while(st.size() && h[st.back()] < h[i]) {
				R[st.back()] = i;
				st.pop_back();
			}
			if(st.size()) L[i] = st.back();
			st.push_back(i);
		}
		st.clear();
		deg.assign(n, 0);
		mp.assign(n, vector<int>());
		queue<int> q;
		rep(i, 0, n - 1) if(R[i] != -1) {
			mp[R[i]].push_back(i);
			deg[i] ++;
		}
		rep(i, 0, n - 1) if(!deg[i]) q.push(i), dR[i] = 0;
		while(q.size()) {
			int cur = q.front(); q.pop();
			for(auto i : mp[cur]) if(dR[i] == INF){
				dR[i] = dR[cur] + 1;
				q.push(i);
			}
		}
		
		deg.assign(n, 0);
		mp.assign(n, vector<int>());
		rep(i, 0, n - 1) if(L[i] != -1) {
			mp[L[i]].push_back(i);
			deg[i] ++;
		}
		rep(i, 0, n - 1) if(!deg[i]) q.push(i), dL[i] = 0;
		while(q.size()) {
			int cur = q.front(); q.pop();
			for(auto i : mp[cur]) if(dL[i] == INF){
				dL[i] = dL[cur] + 1;
				q.push(i);
			}
		}
		sp.assign(lg + 1, vector<int>(n, 0));
		rep(i, 0, n - 1) sp[0][i] = h[i];
		rep(i, 1, lg) rep(j, 0, n - 1) {
			sp[i][j] = max(sp[i - 1][j], sp[i - 1][j + (1 <<(i - 1))]);
		}
		
		pa.assign(lg + 1, vector<int>(n, 0));
		rep(i, 0, n - 1) {
			if(L[i] == -1) pa[0][i] = i;
			else pa[0][i] = L[i];
		}
		rep(i, 1, lg) rep(j, 0, n - 1) {
			pa[i][j] = pa[i - 1][pa[i - 1][j]];
		}
		return;
	}
	bool check(int from, int to, int mid) {
		int mid1 = pa[0][mid];
		if(h[to] < h[mid]) return 0;
		if(h[to] < h[mid1]) return 0;
		int aa = dL[from] - dL[mid] + dR[mid] - dR[to];
		int bb = dL[from] - dL[mid1] + dR[mid1] - dR[to];
		return bb < aa;
	}
	int minimum_jumps(int A, int B, int C, int D) {
		assert(A == B && C == D);
		int mx = query(A, C);
		if(mx != h[C]) return -1;
		int cur = A;
		rrep(i, 0, lg) 
			if(check(A, C, pa[i][cur])) 
				cur = pa[i][cur];
//		print(cur);	
		if(check(A, C, cur)) cur = pa[0][cur];
		return dL[A] - dL[cur] + dR[cur] - dR[C];
	}
/*};
using namespace solver;
signed main() {
//	ios::sync_with_stdio(false), cin.tie(0);
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

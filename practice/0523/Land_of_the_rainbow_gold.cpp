//#define wiwihorz
#include <bits/stdc++.h>
#include "rainbow.h"
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define INF 1000000000
using namespace std;
#define ll long long int
#define pii pair<ll, ll>
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
//namespace solver1 {
	ll n, m, Sr, Sc, op; string s;
	vector<vector<ll>> row1, col1;
	vector<vector<pii>> row2, col2;
	unordered_map<char, pii> mp = {
		{'N', {-1, 0}}, {'S', {1, 0}},
		{'E', {0, 1}}, {'W', {0, -1}}
	};
	void init(int R, int C, int sr, int sc, int M, char *S) {
		n = R, m = C, Sr = sr, Sc = sc, op = M, s = string(S);
		row1.assign(n + 1, vector<ll>());
		row2.assign(n + 1, vector<pii>());
		col1.assign(m + 1, vector<ll>());
		col2.assign(m + 1, vector<pii>());
		pii cur = {Sr, Sc};
		row1[cur.x].push_back(cur.y);
		col1[cur.y].push_back(cur.x);
		for(auto i : s) {
			print(cur.x, cur.y);
			cur = {cur.x + mp[i].x, cur.y + mp[i].y};
			row1[cur.x].push_back(cur.y);
			col1[cur.y].push_back(cur.x);
		}
		rep(i, 1, n) {
			sort(all(row1[i]));
			row1[i].resize(unique(all(row1[i])) - row1[i].begin());
			ll cc = -1, val = 0;
			for(auto j : row1[i]) {
				if(cc + 1 != j) {
					if(val) row2[i].push_back({cc, val});
					row2[i].push_back({j, j}), val = j;
				}
				cc = j;
			}
			if(cc != -1)row2[i].push_back({cc, val});
		}
		rep(i, 1, m) {
			sort(all(col1[i]));
			col1[i].resize(unique(all(col1[i])) - col1[i].begin());
			ll cc = -1, val = 0;
			for(auto j : col1[i]) {
				if(cc + 1 != j) {
					if(val) col2[i].push_back({cc, val});
					col2[i].push_back({j, j}), val = j;
				}
				cc = j;
			}
			if(cc != -1)col2[i].push_back({cc, val});
		}
		return;
	}
	ll area(int u, int d, int l, int r) {
		ll ans = 0;
		rep(i, u, d) {
			
			int L = upper_bound(row1[i].begin(), row1[i].end(), l - 1) - row1[i].begin();
			int R = upper_bound(row1[i].begin(), row1[i].end(), r) - row1[i].begin();
			ans += R - L;
		}
		return ans;
	}
	bool occ(int x, int y) {
		int id = lower_bound(row1[x].begin(), row1[x].end(), y) - row1[x].begin();
		return id < row1[x].size() && row1[x][id] == y;
	}
	ll count_row(int id, int L, int R) {
		ll lid = lower_bound(row2[id].begin(), row2[id].end(), pii(L, -INF)) - row2[id].begin();
		ll rid = upper_bound(row2[id].begin(), row2[id].end(), pii(R, INF)) - row2[id].begin() - 1;
		if(lid > rid) return 0;
		if(lid && row2[id][lid - 1].y == row2[id][lid].y) lid --;
		if(rid + 1 < row2[id].size() && row2[id][rid + 1].y == row2[id][rid].y) rid ++;
		assert((rid - lid + 1) % 2 == 0);
		return (rid - lid + 1) / 2;
	}
	ll count_col(int id, int L, int R) {
		ll lid = lower_bound(col2[id].begin(), col2[id].end(), pii(L, -INF)) - col2[id].begin();
		ll rid = upper_bound(col2[id].begin(), col2[id].end(), pii(R, INF)) - col2[id].begin() - 1;
		if(lid > rid) return 0;
		if(lid && col2[id][lid - 1].y == col2[id][lid].y) lid --;
		if(rid + 1 < col2[id].size() && col2[id][rid + 1].y == col2[id][rid].y) rid ++;
		assert((rid - lid + 1) % 2 == 0);
		return (rid - lid + 1) / 2;
	}
	int colour(int ar, int ac, int br, int bc) {
		int u = min(ar, br), d = max(ar, br);
		int l = min(ac, bc), r = max(ac, bc);
		ll count = area(u, d, l, r);
		if(count == ((d - u + 1) * (r - l + 1))) return 0;
		if(l == r) return count_col(l, u, d) + (!occ(u, l) && !occ(d, l));
		if(u == d) return count_row(u, l, r) + (!occ(u, l) && !occ(u, r));
		ll ans = count_row(u, l, r - 1) + count_row(d, l + 1, r) + 
			count_col(l, u + 1, d) + count_col(r, u, d - 1);

		if(occ(u, r - 1) && occ(u, r)) ans --;
		if(occ(d - 1, r) && occ(d, r)) ans --;
		if(occ(d, l) && occ(d, l + 1)) ans --;
		if(occ(u, l) && occ(u + 1, l)) ans --;
		return (ans ? ans : 1);
	}
/*};
using namespace solver1;
signed main() {
//	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, sr, sc, op, q; char* s;
	cin >> n >> m >> sr >> sc >> op >> s;
	init(n, m, sr, sc, op, s);
	cin >> q;
	while(q--) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		cout << colour(a, b, c, d) << "\n";
	}
	
	return 0;
} */

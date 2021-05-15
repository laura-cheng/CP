#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define INF 1000000000000000000
using namespace std;
#define int long long int
#define pii pair<int, int>
namespace NTT {
	const int n = 1 << 20, lg = 20;
	const int MOD = 998244353;
	const int root = 3, buff = 512500;
	vector<int> A, B, C;
	int pow_(int a, int times) {
		int ans = 1;
		for(; times > 0; times >>= 1, a = a * a % MOD) {
			if(times & 1) ans = ans * a % MOD;
		}
		return ans;
	}
	void ntt(vector<int> &P, bool inv) {
		vector<int> temp(n, 0);
		rep(i, 0, n - 1) {
			int rev = 0;
			rep(j, 0, lg - 1) {
				rev <<= 1;
				rev |= ((i >> j) & 1);
			}  
			temp[i] = P[rev];
		}
		P = temp, temp.clear();
		rep(s, 0, lg - 1) {
			int it_w = pow_(root, (MOD - 1) / (2 << s));
			if(inv) it_w = pow_(it_w, MOD - 2);
			for(int i = 0; i < n; i += (2 << s)) {
				int w = 1;
				rep(j, 0, (1 << s) - 1) {
					int cur = P[i + j], t = w * P[i + j + (1 << s)] % MOD;
					P[i + j] = (cur + t) % MOD;
					P[i + j + (1 << s)] = (cur - t) %MOD;
					w = w * it_w % MOD;
				}
			}
		}
		if(inv) {
			int rev = pow_(n, MOD - 2);
			rep(i, 0, n - 1) P[i] = P[i] * rev % MOD; 
		}
		return ;
	}
	void build_(vector<int> &_A, vector<int> &_B) {
		A = _A, B = _B;
		A.resize(n), B.resize(n);
		ntt(A, 0), ntt(B, 0);
		rep(i, 0, n - 1) C.push_back(A[i] * B[i] % MOD); 
		rep(i, 0, 9) cerr << "i " << i << " " <<  C[i] << "\n";
		ntt(C, 1);
		rep(i, 0, n - 1) C[i] = (C[i] % MOD + MOD) % MOD;
	}
	int get(int x, int y) {
		int id = 1024 * x + y + buff;
		return !C[id];
	}
};
namespace solver {
	int R, C, n;
	string s;
	pii S, T, delta;
	vector<vector<bool>> mp;
	vector<vector<int>> a;
	vector<vector<pii>> dis;
	int dirx[] = {-1, 1, 0, 0};
	int diry[] = {0, 0, -1, 1};
	void init_(int _R, int _C, int _n) {
		R = _R, C = _C, n = _n;
		mp.assign(R + 1, vector<bool>(C + 1, 0));
		dis.assign(R + 1, vector<pii>(C + 1, {INF, INF}));
		a.assign(n + 1, vector<int>(4, INF));
	}
	void build(string _s, pii _S, pii _T) {
		s = _s, S = _S, T = _T;
		rrep(i, 0, n - 1) {
			rep(j, 0, 3) a[i][j] = a[i + 1][j];
			if(s[i] == 'U') a[i][0] = i;
			if(s[i] == 'D') a[i][1] = i;
			if(s[i] == 'L') a[i][2] = i;
			if(s[i] == 'R') a[i][3] = i;
		}
		vector<int> A(1 << 20, 1), B(1 << 20, 0);
		rep(i, 1, R) rep(j, 1, C) {
			if(!mp[i][j]) A[i* 1024 + j] = 0;
		}
		
		int x = 0, y = 0;
		B[NTT::buff] = 1;
		rep(i, 0, n - 1) {
			if(s[i] == 'U') x --;
			if(s[i] == 'D') x ++;
			if(s[i] == 'L') y --;
			if(s[i] == 'R') y ++;
			if(abs(x) >= R || abs(y) >= C) {
				NTT::C.assign(1 << 20, 1);
				return;
			}
			B[NTT::buff - x * 1024 - y] = 1;
		}
		delta = {x, y};
		NTT::build_(A, B);
	}
	int solve() {
		priority_queue<pair<pii, pii>, vector<pair<pii, pii>>, greater<pair<pii, pii>>> pq;
		dis[S.first][S.second] = {0, n};
		pq.push({{0, n}, S});
		while(pq.size()) {
			pii cost, cur; int x, y;
			tie(cost, cur) = pq.top(); pq.pop();
			x = cur.first, y= cur.second;
			if(cost != dis[x][y]) continue;
			if(NTT::get(x, y)) {
				int nx = x + delta.first;
				int ny = y + delta.second;
				if(nx < 1 || nx > R || ny < 1 || ny > C) continue;
				if(dis[nx][ny] > cost) {
					dis[nx][ny] = {cost.first, n};
					pq.push({{cost.first, n}, {nx, ny}});
				} 
			}
			rep(i, 0, 3) {
				int nx = x + dirx[i];
				int ny = y + diry[i];
				if(nx < 1 || nx > R || ny < 1 || ny > C || mp[nx][ny]) continue;
				if(a[cost.second][i] == INF && a[0][i] != INF) {
					pii v = pii(cost.first + 1, a[0][i] + 1);
					if(dis[nx][ny] > v) {
						dis[nx][ny] = v;
						pq.push({v, {nx, ny}});
					}
				}
				else if(a[cost.second][i] != INF) {
					pii v = pii(cost.first, a[cost.second][i] + 1);
					if(dis[nx][ny] > v) {
						dis[nx][ny] = v;
						pq.push({v, {nx, ny}});
					}
				}
			}
			
		}
		if(dis[T.first][T.second].first == INF) return -1;
		return dis[T.first][T.second].first;
 	}
};
using namespace solver;
signed main() {
	vector<int> a = {1, 0, 1, 0, 1};
	vector<int> b = {0, 1, 0, 1, 0};
	NTT::build_(a, b);
	rep(i, 0, 9) cerr << NTT::C[i] << "\n";;
	return 0;
	ios::sync_with_stdio(false), cin.tie(0);
	int R, C, n; string s;
	cin >> R >> C >> n;
	init_(R, C, n);
	pii S, T;
	rep(i, 1, R) rep(j, 1, C) {
		char x; cin >> x;
		if(x == 'S') S = {i, j};
		if(x == 'T') T = {i, j};
		if(x == '#') mp[i][j] = 1;
	}
	cin >> s;
	build(s, S, T);
	cout << solve() << "\n";
	return 0;
}

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
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
string query1(int x, int y) {
	cout << 1 << " " << x << " " << y << endl;
	string ans; cin >> ans;
	return ans;
}
string query2(int u, int d, int l, int r) {
	cout << 2 << " " << u << " " << l << " " << d << " " << r << endl;
	cout.flush();
	string ans; cin >> ans;
	return ans;
}
random;
namespace subtask1 {
	int cnt = 0, q;
	void init_(int _q) {
		q = _q, cnt = 0;
	}
	void solve() {
		int u = -1e18 - 1, d = 1e18 + 1;
		int l = -1e18 - 1, r = 1e18 + 1;
		while(r - l > 0 || d - u > 0) {
			int mid1 = (l + r) / 2;
			int mid2 = (d + u) / 2;
			assert(++cnt <= q);
			string ans = query1(mid1, mid2);
			
			if(ans == "O") return;
			if(ans[0] == 'X') l = mid1, r = mid1;
			else if(ans[0] == 'P') l = mid1 + 1;
			else r = mid1 - 1;
			if(ans[1] == 'Y') u = mid2, d = mid2;
			else if(ans[1] == 'P') u = mid2 + 1;
			else d = mid2 - 1;
		}
		cnt ++;
		string ans = query1(l, u);
		assert(cnt <= q);
		assert(ans == "O");
		return;
	}

};
namespace subtask2 {
	int q, cnt;
	void init_(int _q) {
		q = _q, cnt = 0;
	}
	void move(int &u, int &d, int &l, int &r, string ans, int mid1, int mid2) {
		if(ans[0] == 'P') l = mid1, r = r + 1;
		else if(ans[0] == 'X') l = mid1 - 1, r = mid1 + 1;
		else l = l - 1, r = mid1;
		
		if(ans[1] == 'P') u = mid2, d = d + 1;
		else if(ans[1] == 'Y') u = mid2 - 1, d = mid2 + 1;
		else u = u - 1, d = mid2;
	}
	void solve() {
		int u = -1e18, d = 1e18;
		int l = -1e18, r = 1e18;
		while(d - u > 3|| r - l > 3) {
			int mid1 = (l + r) / 2;
			int mid2 = (d + u) / 2;
			print(u, d, l, r);
			string ans = query1(mid1, mid2);
			cnt ++;
			if(ans == "O") return;
			else move(u, d, l, r, ans, mid1, mid2); 
		}
		while(d - u > 2 || r - l > 2) {
			int op = rnd() & 1;
			int x = min(d, (op + u + d) / 2);
			int y = min(r, (l + r + op) / 2);
			string ans = query1(y, x);
			print(u, d, l, r);
			if(ans == "O") return ;
			else move(u, d, l, r, ans, y, x);
		}
		string ans = query2(u, d, l, r);
		if(ans == "O") return;
		else {
			ans = query2(u, d, l, r);
			assert(ans == "O");
		}
	}

};
signed main() {
	int t, q, d; cin >> t >> q >> d;
	while(t --) {		
		subtask1::init_(q);
		subtask1::solve();

	}
	return 0;
}

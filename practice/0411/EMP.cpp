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
int dirx[] = {1, 0, 0, -1};
int diry[] = {0, -1, 1, 0};
int cx, cy;
random;
void change() {
	int op = rnd() % 4;
	cx += dirx[op], cy += diry[op];
	return;
}
string query1(int x, int y) {
	cout << 1 << " " << x << " " << y << "\n";
	cout.flush();
	string ans; cin >> ans;
	return ans;
}
string query2(int l, int u, int r, int d) {
	
	cout << 2 << " " << l << " " << u << " " << r << " " << d << "\n";
	cout.flush();
	string ans; cin >> ans;
	return ans;
}
void solve1() {
	int u = -1e18 - 1, d = 1e18 + 1;
	int l = -1e18 - 1, r = 1e18 + 1;
	while(r - l > 1 || d - u > 1) {
		r = max(r, l + 1);
		d = max(d, u + 1);
		int mid1 = (l + r) / 2;
		int mid2 = (d + u) / 2;
		string ans = query1(mid1, mid2);
		if(ans == "O") return;
		if(ans[0] == 'N') l = mid1 + 1;
		else if(ans[0] == 'X') l = mid1, r = l + 1;
		else r = mid1;
		if(ans[1] == 'N') u = mid2 + 1;
		else if(ans[1] == 'Y') u = mid2, d = u + 1;
		else d = mid2;
	}
	string ans = query1(l, u);
	if(ans != "O") while(1);
	return;
}

void move(int &u, int &d, int &l, int &r, string ans, int mid1, int mid2) {
	if(ans[0] == 'N') l = mid1, r = r + 1;
	else if(ans[0] == 'X') l = mid1 - 1, r = mid1 + 1;
	else l = l - 1, r = mid1;
	
	if(ans[1] == 'N') u = mid2, d = d + 1;
	else if(ans[1] == 'Y') u = mid2 - 1, d = mid2 + 1;
	else u = u - 1, d = mid2;
}
void solve2() {
	int u = -1e18, d = 1e18;
	int l = -1e18, r = 1e18;
	int cnt = 0;
	while(d - u > 3|| r - l > 3) {
		int mid1 = (l + r) / 2;
		int mid2 = (d + u) / 2;
		string ans = query1(mid1, mid2);
		if(ans == "O") return;
		else move(u, d, l, r, ans, mid1, mid2); 
	}
	if(r - l < 3) l --;
	if(d - u < 3) u --; 
	string ans;
	ans = query2(l, u, l + 2, d);
	if(ans == "O") return;
	else if(ans == "OUT") l = l + 2, r = r + 1;
	else r = l + 2;
	ans = query2(l, u + 1, r, d);
	if(ans == "O") return;
	else if(ans == "OUT") d = u + 1, u = u - 1;
	else u = u + 1;
	ans = query2(l, u, r, d);
	return; 	 
}

signed main() {
	int t, q, d; cin >> t >> q >> d;
	while(t --) {		
		if(d == 0) solve1();
		else solve2();
	}
	return 0;
}

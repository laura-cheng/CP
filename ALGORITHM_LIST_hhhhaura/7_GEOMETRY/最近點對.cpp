#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define MOD 1000000007
#define MAXN 1000005
#define INF 1000000000000000000
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
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else
#define print(...) 0
#define vprint(...) 0
#endif
#define x first
#define y second
int n;
vector<pii> a, temp;
int len(pii a, pii b) {
	pii c = {a.x - b.x, a.y - b.y};
	return (c.x * c.x) + (c.y * c.y);
}
bool cmp(pii a, pii b) {
	return a.y < b.y;
}
int solve(int l, int r) {
	if(l == r) return INF;
	int mid = (l + r) / 2, ln = a[mid].x;
	int ans = min(
		solve(l, mid), 
		solve(mid + 1, r)
	);
	temp.assign(r - l + 1, {0, 0});
	merge(
		a.begin() + l, a.begin() + mid + 1,
		a.begin() + mid + 1, a.begin() + r + 1,
		temp.begin(), cmp
	);
	rep(i, l, r) a[i] = temp[i - l];
	temp.clear();
	rep(i, l, r) {
		if(abs(a[i].x - ln) * abs(a[i].x - ln) < ans) 
			temp.push_back(a[i]);
	}
	rep(i, 0, signed(temp.size()) - 1) {
		rep(j, i + 1, signed(temp.size()) - 1) {
			ans = min(ans, len(temp[i], temp[j]));
			if(abs(temp[j].y - temp[i].y) 
				* abs(temp[j].y- temp[i].y) >= ans) break; 
		}
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	int sum = 0;
	rep(i, 1, n) {
		int x, y; cin >> x >> y;
		a.push_back({x, y});
	}
	sort(all(a));
	cout << solve(0, a.size() - 1) << "\n";
	return 0;
}


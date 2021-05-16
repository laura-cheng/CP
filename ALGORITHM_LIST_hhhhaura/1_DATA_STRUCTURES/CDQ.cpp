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
#define lowbit(x) (x & -x)
int n;
struct pt {
	int x, y, z, id;
	bool operator<(pt b) {
		if(x == b.x) return y < b.y;
		else return x > b.x;
	}
};
vector<pt> a, b;
vector<int> ans, bit;
bool cmp(pt a, pt b) {
	return a.y > b.y;
}
void modify(int x, int val) {
	for(int i = x; i <= n; i += lowbit(i)) {
		bit[i] += val;
	}
	return;
}
int query(int x) {
	int ans = 0;
	for(int i = x; i > 0; i -= lowbit(i)) {
		ans += bit[i];
	}
	return ans;
}
void solve(int l, int r) {
	if(l == r) return;
	int mid = (l + r) / 2;
	solve(l, mid), solve(mid + 1, r);
	stack<int> op;
	int cur = l;
	rep(i, mid + 1, r) {
		while(cur < mid + 1 && a[cur].y > a[i].y) {
			modify(a[cur].z, 1);
			op.push(a[cur].z);
			cur ++;
		}
		ans[a[i].id] += query(n) - query(a[i].z);
	} 
	while(op.size()) {
		int c = op.top(); op.pop();
		modify(c, -1);
	}
	b.assign(r - l + 1, {0, 0, 0});
	merge(
		a.begin() + l, a.begin() + mid + 1,
		a.begin() + mid + 1, a.begin() + r + 1,
		b.begin(), cmp
	);
	rep(i, l, r) a[i] = b[i - l];
	return;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	rep(i, 1, n) {
		int x, y, z;
		cin >> x >> y >> z;
		a.push_back({x, y, z, i});
	}
	ans.assign(n + 1, 0);
	bit.assign(n + 1, 0);
	sort(all(a)), solve(0, a.size() - 1);
	rep(i, 1, n) cout << ans[i] << "\n";
	return 0;
}


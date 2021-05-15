#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define pii pair<int, int>
using namespace std;
namespace solver {
	int n;
	vector<int> a;
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, 0);
	}
	void solve2(int L, int R, int val) {
		if(L == R) return;
		int mid = (L + R) / 2;
		solve2(L, mid, val);
		solve2(mid + 1, R, val);
		int curL = mid + 1, curR = mid;
		while(curR + 1 <= R && a[curR + 1] <= val) curR++;
		while(curL - 1 >= L && a[curL - 1] > val) curL --;
		if(curR > curL) {
			cout << curL << " " << curR << "\n";
			reverse(a.begin() + curL, a.begin() + curR + 1);
		}
		return;
	}
	void solve1(int L, int R) {
		if(L == R) return;
		vector<int> b;
		int mid = (L + R) / 2;
		rep(i, L, R) b.push_back(a[i]);
		nth_element(b.begin(), b.begin() + (mid - L), b.end());
		solve2(L, R, b[mid - L]);
		solve1(L, mid), solve1(mid + 1, R);
		return;
	}
	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	vector<pii> b;
	rep(i, 1, n) {
		 cin >> a[i];
		 b.push_back({a[i], i});
	}
	sort(all(b));
	rep(i, 0, n - 1) a[b[i].second] = i + 1; 
	solve1(1, n);
	return 0;
}

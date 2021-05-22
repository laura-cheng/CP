#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
using namespace std;
#define int long long int
namespace solver {
	int ans;
	vector<int> b;
	void init_() {
		ans = 0;
		b.assign(64, 0);
	} 
	void insert(int x) {
		rrep(i, 0, 63) if((x >> i) & 1) {
			if(!x) return;
			if(b[i]) x ^= b[i];
			else {
				ans ++;
				b[i] = x;
				return;
			}
		}
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_();
	rep(i, 1, n) {
		int x; cin >> x;
		insert(x);
	}
	cout << (1ull << ans) - n << "\n";
	return 0;
} 


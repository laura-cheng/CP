int n;
vector<int> a, base;
int solve() {
	if(a[n] == 0) return -1;
	base.assign(31, 0);
	rep(i, 1, n) {
		rrep(j, 0, 30) {
			if(!(a[i] >> j)) continue;
			if(!base[j]) {
				base[j] = a[i];
				break;
			}
			a[i] ^= base[j];
		}
	}
	int cnt = 0;
	rep(i, 0, 30) cnt += bool(base[i]);
	return cnt;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	a.assign(n + 1, 0);
	rep(i, 1, n) {
		cin >> a[i];
		a[i] ^= a[i - 1];
	}
	cout << solve() << "\n";
	return 0;
}

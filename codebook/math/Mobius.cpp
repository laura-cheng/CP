int n;
vector<int> a, fac, p, mu;
vector<int> cnt;
void build() {
	fac.assign(MAXN, 1);
	mu.assign(MAXN, 1);
	rep(i, 2, MAXN - 1) {
		if(fac[i] == 1) {
			p.push_back(i);
			mu[i] = -1;
		}
		for(auto j : p) {
			if(i * j >= MAXN) break;
			fac[i * j] = j;
			mu[i * j] = -mu[i];
			if(i % j == 0) {
				mu[i * j] = 0;
				break;
			} 
		}
	}
	return;
}
int pow_(int a, int times) {
	int ans = 1;
	for(;times > 0; times >>= 1, a = (a * a) % MOD) {
		if(times & 1) ans = (ans * a) % MOD;
	}
	return ans;
}
int solve() {
	cnt.assign(MAXN, 0);
	rep(i, 1, n) {
		int nn = sqrt(a[i]);
		rep(j, 1, nn) {
			if(a[i] % j == 0) {
				cnt[a[i] / j] ++;
				cnt[j] ++;
			}
		}
		if(nn * nn == a[i]) cnt[nn] --;
	}
	int ans = 0;
	rep(i, 1, MAXN - 1) {
		ans = (ans + (pow_(2, cnt[i]) - 1) * mu[i]) % MOD;
	}
	return (ans % MOD + MOD) % MOD;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n, build();
	a.assign(n + 1, 0);
	rep(i, 1, n) cin >> a[i];
	cout << solve() << "\n";
	return 0;
}

vector<int> a, r;
pii exgcd(int a, int b) {
	if(b == 0) return pii(a > 0 ? 1 : -1, 0);
	else {
		pii p = exgcd(b, a % b);
		return pii(p.second, p.first - a / b * p.second);
	}
}
int __gcd(int a, int b) {
	if(b == 0) return a;
	else return __gcd(b, a%b);
}
int crt(int n) {
	int aa = 1, rr = 0;
	rep(i, 1, n) {
		pii p = exgcd(aa, -a[i]);
		int c = r[i] - rr, gcd = __gcd(aa, a[i]);
		if(c % gcd) return -1;
		p.first = p.first * (c / gcd) % a[i];
		rr = aa * p.first + rr;
		aa = aa / gcd * a[i];
		rr = rr % aa;
	}
	return (rr + aa) % aa;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n;
	while(cin >> n) {
		a.assign(n + 1, 0);
		r.assign(n + 1, 0);
		rep(i, 1, n) 
			cin >> a[i] >> r[i];
		cout << crt(n) << "\n"; 
	}
	return 0;
}

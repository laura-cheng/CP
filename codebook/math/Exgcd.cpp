pii exgcd(int a, int b) {
	if(b == 0) return {a, 0};
	else {
		pii p = exgcd(b, a % b);
		return {p.second, p.first - a / b * p.second};
	}
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int A, B;
	while(cin >> A >> B) {
		int gcd = __gcd(A, B);
		A /= gcd, B /= gcd;
		pii ans = exgcd(A, B);
		cout << ans.first << " " 
			<< ans.second << " " << gcd << "\n";
	}
	return 0;
}

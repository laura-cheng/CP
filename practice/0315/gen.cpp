#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loo-opt(on)

#define rep(i ,a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MAXN 1000005
#define MOD 1000000007
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
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
random;
signed main() {
//	ios::sync_with_stdio(false), cin.tie(0);
	int n, w, q;
	n = rnd() % 2 + 2;
	w = rnd() % 10 + 1;
	q = rnd() % 10 + 1;
	cout << n << " " << w << " " << q << "\n";
	rep(i, 1, w) {
		rep(j, 1, n) {
			cout << rnd() % 50 + 1 << " ";
		}
		cout << "\n";
	}
	rep(i, 1, q) {
		int op = rnd() % 5;
		if(op == 1) {
			cout << 'Q' << " ";
			int L = rnd() % w, R = rnd() % (w - L) + L;
			cout << L << " " << R << " " << rnd() % n << "\n";
		}
		else if(op == 2) {
			int L = rnd() % w, R = rnd() % (w - L) + L;
			int t1 = rnd() % n, t2 = t1;
			while(t2 == t1) t2 = rnd() % n;
			cout << "C " << L << " " << R << " " << t1 << " " << t2 << "\n";
		}
		else if(op == 3) {
			int L = rnd() % w, R = rnd() % (w - L) + L;
			int t1 = rnd() % n, t2 = t1;
			while(t2 == t1) t2 = rnd() % n;
			int p = rnd() % 50 + 1;
			cout << "A " << L << " " << R << " " << t1 << " " << t2 << " " << p << "\n"; 			
		}
		else if(op == 4) {
			int L = rnd() % w, R = rnd() % (w - L) + L;
			int t1 = rnd() % n;
			cout << "M " << L << " " << R << " " << t1 << " " << rnd() % 50 + 1 << " " << rnd() % 50 + 1 << "\n";
		}
		else {
			int L = rnd() % w, R = rnd() % (w - L) + L;
			int t1 = rnd() % n, t2 = t1;
			while(t2 == t1) t2 = rnd() % n;
			cout << "S " << L << " " << R << " " << t1 << " " << t2 << "\n";					
		}
	}
	
	return 0;
}

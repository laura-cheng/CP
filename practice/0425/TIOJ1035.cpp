#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define eps (1e-9)
#define MAXN 1000005

using namespace std;
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt199374 rnd(chrono::steady_clock::now().time_since_epoch().count())

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace NTT {
	const int n = 1 << 17, lg = 17;
	const int MOD = 998244353;
	const int root = 3, buff = 512500;
	vector<int> A, B, C(n, 0);
	int pow_(int a, int times) {
		int ans = 1;
		for(; times > 0; times >>= 1, a = a * a % MOD) {
			if(times & 1) ans = ans * a % MOD;
		}
		return ans;
	}
	void ntt(vector<int> &P, bool inv) {
		vector<int> temp(n, 0);
		rep(i, 0, n - 1) {
			int rev = 0;
			rep(j, 0, lg - 1) {
				rev <<= 1;
				rev |= ((i >> j) & 1);
			}  
			temp[i] = P[rev];
		}
		P = temp;
		rep(s, 0, lg - 1) {
			int it_w = pow_(root, (MOD - 1) / (2 << s));
			if(inv) it_w = pow_(it_w, MOD - 2);
			for(int i = 0; i < n; i += (2 << s)) {
				int w = 1;
				rep(j, 0, (1 << s) - 1) {
					int cur = P[i + j], t = w * P[i + j + (1 << s)] % MOD;
					P[i + j] = (cur + t) % MOD;
					P[i + j + (1 << s)] = (cur - t + MOD) %MOD;
					w = w * it_w % MOD;
				}
			}
		}
		if(inv) {
			int rev = pow_(n, MOD - 2);
			rep(i, 0, n - 1) P[i] = P[i] * rev % MOD; 
		}
		return ;
	}
	void build_(vector<int> &A, vector<int> &B) {
		A.resize(n), B.resize(n);
		ntt(A, 0), ntt(B, 0);
		rep(i, 0, n - 1) C[i] = A[i] * B[i] % MOD; 
		ntt(C, 1);
	}
};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	string a, b; 
	cin >> a >> b, reverse(all(b));
	vector<int> ans(NTT::n, 0);
	rep(i, 0, 9) {
		vector<int> aa, bb;
		for(auto j : a) aa.push_back(j == char(i + 'a') ? 1 : 0);
		for(auto j : b) bb.push_back(j == char(i + 'a') ? 1 : 0);
		NTT::build_(aa, bb);
		rep(i, 0, NTT::n - 1) ans[i] += NTT::C[i];
	}
	int mx = 0;
	rep(i, 0, NTT::n - 1) mx = max(mx, ans[i]);
	cout << mx << "\n";
	return 0;
}

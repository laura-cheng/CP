#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MAXN 1000005
#define INF 1000000000000000000
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
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
string op[6] = {
	"ADD",
	"INSERT",
	"REVOLVE",
	"REVERSE",
	"DELETE",
	"MIN",
};
random;
int sz;
pii get() {
	int l = rnd() % sz + 1;
	int len = rnd() % (sz - l + 1);
	return {l, len + l};
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n = rnd() % 100000 + 1, m = rnd() % 100000 + 1;
	sz = n;
	cout << n << " \n";
	rep(i, 1, n) {
		cout << rnd() << " ";
	} 
	cout << "\n";
	cout << m << "\n";
	rep(i, 1, m) {
		int opp = rnd() % 6;
		cout << op[opp] << " ";
		if(!sz && opp != 1) {
			i--;
			continue;
		}
		if(opp ==0 || opp == 2) {
			pii p = get();
			cout << p.first << " " << p.second << " " << rnd() << "\n"; 
		}
		else if(opp == 1) {
			cout << rnd() % (sz + 1) << " " << rnd()<< "\n";
		}
		else if(opp == 3 || opp == 5) {
			pii p = get();
			cout << p.first << " " << p.second << "\n";
		}
 		else {
			cout << rnd() % sz + 1 << "\n";
		}	
		sz += (opp == 1);
		sz -= (opp == 4);
	}
	return 0;
}

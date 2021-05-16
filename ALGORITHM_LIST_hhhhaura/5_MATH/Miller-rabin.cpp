#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a;i--)
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
int pow_(int a, int times, int mod) {
    int ans = 1;
    for(;times > 0;times>>=1, a = a * a % mod) {
        if(times & 1) ans = ans * a % mod;
    }
    return ans;
}
bool miller_rabin(int n, int d) {
    int a = rnd() % (n - 1) + 1;
    int x = pow_(a, d, n);
    if(x == 1 || x == n - 1) return true;
    else {
        while(d != (n - 1)) {
            d <<= 1;
            x = x * x % n;
            if(x == n - 1) return true;
        }
    }
    return false;
}
bool prime(int n) {
    if(n == 2) return true;
    if(!(n & 1) || n == 1) return false;
    int x = n - 1;
    while(!(x & 1)) x >>= 1;
    rep(i, 1, 10) {
        if(!miller_rabin(n, x)) return false;
    }
    return true;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int n;
    while(cin >> n) {
        if(prime(n)) cout << "質數\n";
        else cout << "非質數\n";
    }
    return 0;
}

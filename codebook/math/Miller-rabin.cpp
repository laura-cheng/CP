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
        if(prime(n)) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}

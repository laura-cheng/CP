#include <iostream>
#include <queue>
#define int long long int 
#define MAXN 200
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define INF 1000000000000000000
#define pii pair<int, int>
using namespace std;
int n, mp[MAXN][MAXN];
int dis[MAXN], vis[MAXN];
int solve() {
	rep(i, 1, n) dis[i] = INF;
	rep(i, 1, n) vis[i] = 0;
	dis[1] = 0;
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push(pii(0, 1));
	int ans = 0;
	while(pq.size()) {
		int cur = pq.top().second; pq.pop();
		if(vis[cur]) continue;
		ans += dis[cur], vis[cur] = 1;
		rep(i, 1, n) {
			if(!vis[i] && dis[i] > mp[cur][i]) {
				dis[i] = mp[cur][i];
				pq.push(pii(dis[i], i));
			}
		}
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	while(cin >> n) {
		rep(i, 1, n) rep(j, 1, n) {
			cin >> mp[i][j];
		}
		cout << solve() << "\n";
	}
	return 0;
}

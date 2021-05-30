#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>

typedef long long LL;

const int LOG = 20;
const int MAXN = 500000;
const int MAXM = 1000000;

int N, M;
std::vector<int> G[MAXN + 5];

int SqrCnt;
std::vector<int> T[MAXN * 2 + 5];

void AddEdge(int u, int v) {
	T[u].push_back(v), T[v].push_back(u);
}

LL Ans, tot;
int W[MAXN + 5];
int Size[MAXN + 5];

void Dfs(int u, int fa) {
	Size[u] = u <= N;
	for (int i = 0; i < int(T[u].size()); i++) {
		int v = T[u][i];
		if (v != fa) {
			Dfs(v, u);
			Ans += 2ll * W[u] * Size[u] * Size[v];
			Size[u] += Size[v];
		}
	}
	Ans += (LL)2ll * W[u] * Size[u] * (tot - Size[u]);
}

std::stack<int> S;
int Dfn[MAXN + 5], Low[MAXN + 5], DfnCnt;

void Tarjan(int u, int fa) {
	S.push(u); ++tot;
	Dfn[u] = Low[u] = ++DfnCnt;
	for (int i = 0; i < int(G[u].size()); i++) {
		int v = G[u][i];
		if (v == fa)
			continue;
		if (!Dfn[v]) {
			Tarjan(v, u);
			Low[u] = std::min(Low[u], Low[v]);
			if (Low[v] >= Dfn[u]) {
				AddEdge(u, ++SqrCnt); W[SqrCnt]++;
				while (!S.empty()) {
					int x = S.top(); S.pop();
					AddEdge(x, SqrCnt); W[SqrCnt]++;
					if (x == v)
						break;
				}
			}
		}
		else
			Low[u] = std::min(Low[u], Dfn[v]);
	}
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(v), G[v].push_back(u);
	}
	SqrCnt = N;
	for (int i = 1; i <= N; i++)
		W[i] = -1;
	for (int i = 1; i <= N; i++) {
		if (!Dfn[i]) {
			tot = 0;
			Tarjan(i, 0);
			S.pop();
			Dfs(i, 0);
		}
	}
	printf("%lld\n",  Ans);
	return 0;
}


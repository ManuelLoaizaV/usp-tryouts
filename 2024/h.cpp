#include <bits/stdc++.h>
#define debug(x) cerr << #x << " = " << x << endl
using namespace std;
typedef long long Long;
typedef long double Double;
typedef pair<Long, Long> Pair;
const Long INF = 1e18;
const Double EPS = 1e-9;

struct Edge {
  int v;
  Long x;
  Long y;

  Edge(void) {}

  Edge(int _v, Long _x, Long _y) {
    this->v = _v;
    this->x = _x;
    this->y = _y;
  }

  Long weight(Long t) {
    Long cycle = this->x + this->y;
    Long r = t % cycle;
    if (r < this->x) {
      return 0;
    }
    return cycle - r;
  }
};

const int N = 1e5;
vector<Edge> adj[N];
Long d[N];

void Dijkstra(int s, Long d_0) {
  for (int i = 0; i < N; i++) d[i] = INF;
  d[s] = d_0;
  priority_queue<Pair, vector<Pair>, greater<Pair>> q;
  q.push({d[s], s});
  while (!q.empty()) {
    Pair path = q.top();
    int u = path.second;
    q.pop();
    if (d[u] != path.first) continue;
    for (Edge e : adj[u]) {
      int v = e.v; Long w = e.weight(d[u]);
      if (d[u] + w < d[v]) {
        d[v] = d[u] + w;
        q.push({d[v], v});
      }
    }
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  Long t_0;
  cin >> t_0;
  for (int i = 0; i < m; i++) {
    int u, v;
    Long x, y;
    cin >> u >> v >> x >> y;
    u--;
    v--;
    adj[u].push_back(Edge(v, x, y));
    adj[v].push_back(Edge(u, x, y));
  }
  Dijkstra(0, t_0);
  cout << d[n - 1] << endl;
  return 0;
}
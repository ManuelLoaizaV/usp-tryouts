#include <bits/stdc++.h>
#define debug(x) cerr << #x << " = " << x << endl
using namespace std;
const int MAX_N = 10000;
const int MAX_M = 5000;

struct MaxQueue {
  stack<pair<int, int>> s, t;
  int f(int a, int b) { return max(a, b); }
  void Push(int e) {
    int mn = s.empty() ? e : f(e, s.top().second);
    s.push(make_pair(e, mn));
  }
  int Pop(void) {
    if (t.empty()) {
      while (!s.empty()) {
        int e = s.top().first;
        s.pop();
        int mn = t.empty() ? e : f(e, t.top().second);
        t.push(make_pair(e, mn));
      }
    }
    int r = t.top().first;
    t.pop();
    return r;
  }
  int Max(void) {
    if (s.empty()) return t.top().second;
    else if (t.empty()) return s.top().second;
    return f(s.top().second, t.top().second);
  }
  int Size(void) { return s.size() + t.size(); }
  void Clear(void) {
    s = stack<pair<int, int>>();
    t = stack<pair<int, int>>();
  }
};

int p[MAX_N];
int prefixes[MAX_N];
int dp[MAX_M + 1][MAX_N + 1];

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N, M, W;
  cin >> N >> M >> W;
  for (int i = 0; i < N; i++) cin >> p[i];
  
  for (int i = 0; i < N; i++) {
    if (i > 0) {
      prefixes[i] = prefixes[i - 1];
    }
    prefixes[i] += p[i];
  }
  
  MaxQueue q;
  for (int g = 1; g <= M; g++) {
    for (int i = N - 1; i >= 0; i--) {
      int prev_prefix = (i > 0) ? prefixes[i - 1] : 0LL;
      dp[g][i] = 0LL;
      if (i + W < N && g > 1 && W > 1) {
        q.Push(dp[g - 2][i + W + 1] + prefixes[i + W]);
        while (q.Size() >= W) {
          q.Pop();
        }
      }
      if (i + W - 1 < N) {
        dp[g][i] = max(dp[g][i], max(dp[g][i + 1], prefixes[i + W - 1] - prev_prefix + dp[g - 1][i + W]));
        if (i + W < N && g > 1 && W > 1) {
          int L = i + W;
          int R = min(i + 2 * W - 2, N - 1);
          dp[g][i] = max(dp[g][i], q.Max() - prev_prefix);
        }
      }
    }
    q.Clear();
  }

  cout << dp[M][0] << endl;

  return 0;
}
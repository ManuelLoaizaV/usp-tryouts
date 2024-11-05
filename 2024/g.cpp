#include <bits/stdc++.h>
#define debug(x) cerr << #x << " = " << x << endl
using namespace std;
typedef long long Long;
typedef long double Double;
typedef pair<Long, Long> Pair;
const int N = 1001;
const Long INF = 1e18;
const Double EPS = 1e-9;

Long a[N];
Long dp[N][N];
bool done[N][N];
int n;

// DP(i, t): min travel cost [i..n] with teleport at a[t]
Long DP(int i, int t) {
  if (i == n) return 0;
  if (done[i][t]) return dp[i][t];
  dp[i][t] = min(abs(a[i + 1] - a[i]) + DP(i + 1, t), abs(a[i + 1] - a[t]) + DP(i + 1, i));
  done[i][t] = true;
  return dp[i][t];
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  a[0] = 0;
  for (int i = 1; i <= n; i++) cin >> a[i];
  cout << DP(0, 0) << endl;
  return 0;
}
#include <bits/stdc++.h>
#define debug(x) cerr << #x << " = " << x << endl
using namespace std;
typedef long long Long;
typedef long double Double;
typedef pair<Long, Long> Pair;
const int N = 1e6;
const Long INF = 1e18;
const Double EPS = 1e-9;
int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<Long> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  sort(v.begin(), v.end());
  Long best_price = -1;
  Long max_profit = -1;
  for (int i = 0; i < n; i++) {
    Long current_profit = v[i] * (n - i);
    if (current_profit > max_profit) {
      max_profit = current_profit;
      best_price = v[i];
    }
  }
  cout << best_price << " " << max_profit << endl;
  return 0;
}
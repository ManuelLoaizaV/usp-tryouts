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
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  int n_even = 0;
  int n_odd = 0;
  int ones = 0;
  int zeroes = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] == 0) {
      zeroes++;
    } else if (a[i] == 1) {
      ones++;
    } else if (a[i] & 1) {
      n_odd++;
    } else {
      n_even++;
    }
  }

  n -= zeroes;

  if (ones == n || n_even == n) {
    cout << 1 << endl;
  } else {
    cout << 2 << endl;
  }

  return 0;
}
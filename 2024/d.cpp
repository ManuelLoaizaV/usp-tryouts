#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#define debug(x) cerr << #x << " = " << x << endl
using namespace std;
typedef long long Long;
typedef long double Double;
typedef pair<Long, Long> Pair;
const int N = 1e6;
const Long INF = 1e18;
const Double EPS = 1e-7;

typedef struct P {
  Double x;
  Double y;
  Double z;

  P(void) {
    x = y = z = 0.0L;
  }

  P(Double _x, Double _y, Double _z) {
    x = _x;
    y = _y;
    z = _z;
  }

  Double Norm(void) {
    return sqrt(x*x + y*y + z*z);
  }

  void Read(void) {
    cin >> x >> y >> z;
  }
} point_t;

point_t operator - (const point_t& A, const point_t& B) {
  return point_t(A.x - B.x, A.y - B.y, A.z - B.z);
}

Double Distance(const point_t& a, const point_t& b) {
  point_t c = a - b;
  return c.Norm();
}

bool Check(const Double& R, const vector<Double>& d, const point_t& theo, const Double& r) {
  for (int i = 0; i < 8; i++) {
    vector<Double> c(3, 0.0L);
    for (int j = 0; j < 3; j++) {
      if ((i >> j) & 1) {
        c[j] = R;
      } else {
        c[j] = d[j] - R;
      }
    }
    point_t bound(c[0], c[1], c[2]);
    if (Distance(bound, theo) >= R + r) {
      return true;
    }
  }
  return false;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  vector<Double> d(3);
  for (int i = 0; i < 3; i++) {
    cin >> d[i];
  }
  
  point_t theo;
  theo.Read();

  Double r;
  cin >> r;

  Double L = 0.0L;
  Double R = *min_element(d.begin(), d.end()) / 2.0L;

  if (Check(R, d, theo, r)) {
    L = R;
  } else {
    while (R - L > EPS) {
      Double M = (L + R) / 2.0L;
      if (Check(M, d, theo, r)) {
        L = M;
      } else {
        R = M;
      }
    }
  }
  cout << fixed << setprecision(15) << L << endl;
  return 0;
}
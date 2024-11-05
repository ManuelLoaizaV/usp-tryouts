#include <bits/stdc++.h>
#define debug(x) cerr << #x << " = " << x << endl
using namespace std;
typedef long long Long;
typedef long double Double;
typedef pair<Long, Long> Pair;
const int N = 1e6;
const Long INF = 1e18;
const Double EPS = 1e-9;

struct Guest {
  Long t;
  Long m;
  bool c;
  int id;

  Guest(Long _t, Long _m, bool _c, int i) {
    this->t = _t;
    this->m = _m;
    this->c = _c;
    this->id = i + 1;
  }

  bool operator < (Guest const& other) {
    return this->t < other.t;
  }
};

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<Guest> guests;
  for (int i = 0; i < n; i++) {
    Long t, m;
    bool c;
    cin >> t >> m >> c;
    guests.push_back(Guest(t, m, c, i));
  }
  sort(guests.begin(), guests.end());

  Long current_time = 0LL;
  queue<pair<Long, int>> playlist;
  vector<int> sad_guests;
  for (int i = 0; i < n; i++) {
    while (
      !playlist.empty() &&
      current_time + playlist.front().first <= guests[i].t
    ) {
      current_time += playlist.front().first;
      playlist.pop();
    }
    if (!playlist.empty()) {
      if (guests[i].c) {
        sad_guests.push_back(playlist.front().second);
        playlist.front().first = guests[i].m;
        playlist.front().second = guests[i].id;
      } else {
        Long listening_time = guests[i].t - current_time;
        playlist.front().first -= listening_time;
        playlist.push(make_pair(guests[i].m, guests[i].id));
      }
    } else {
      playlist.push(make_pair(guests[i].m, guests[i].id));
    }
    current_time = guests[i].t;
  }

  int n_sad_guests = (int)sad_guests.size();
  cout << n_sad_guests << endl;
  for (int i = 0; i < n_sad_guests; i++) {
    if (i > 0) cout << ' ';
    cout << sad_guests[i];
  }
  cout << endl;
  return 0;
}
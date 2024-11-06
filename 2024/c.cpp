#include <bits/stdc++.h>
#define debug(x) cerr << #x << " = " << x << endl
using namespace std;
typedef long long Long;
typedef long double Double;
typedef pair<Long, Long> Pair;

const Long INF = 1e18;
const Double EPS = 1e-9;

struct SegmentChange {
  static const Long SENTINEL = numeric_limits<Long>::max();
  Long to_add;
  SegmentChange(Long _to_add = 0LL) : to_add(_to_add) {}
  bool HasChange(void) const { return to_add != 0; }
  void Merge(const SegmentChange &other) {
    to_add += other.to_add;
  }
};
struct Segment {
  Long minimum;
  Segment(Long _minimum = numeric_limits<Long>::max()) : minimum(_minimum) {}
  void Merge(const Segment &other) {
    minimum = min(minimum, other.minimum);
  }
  void Merge(const Segment &left, const Segment &right) {
    *this = left;
    Merge(right);
  }
  void Apply(int start, int end, const SegmentChange &change) {
    minimum += change.to_add;
  }
};
struct SegmentTree {
  int initial_n = 0;
  int tree_n = 0;
  vector<Segment> tree;
  vector<SegmentChange> changes;
  SegmentTree(int n = -1) { if (n >= 0) Init(n); }
  void Init(int n) {
    initial_n = n;
    tree_n = 2 * initial_n;
    tree.assign(tree_n, Segment());
    changes.assign(tree_n, SegmentChange());
  }
  void Build(const vector<Segment> &initial, int segment_id, int start, int end) {
    if (start == end) {
      tree[segment_id].Merge(initial[start]);
      return;
    }
    int mid = (start + end) / 2;
    int left_segment_id = segment_id + 1;
    int right_segment_id = segment_id + 2 * (mid - start + 1);
    Build(initial, left_segment_id, start, mid);
    Build(initial, right_segment_id, mid + 1, end);
    tree[segment_id].Merge(tree[left_segment_id], tree[right_segment_id]);
  }
  void Build(const vector<Segment> &initial) { // O(n)
    int n = (int)initial.size();
    Init(n);
    Build(initial, 1, 0, n - 1);
  }
  void ApplyAndMerge(int segment_id, int start, int end, const SegmentChange &change) {
    tree[segment_id].Apply(start, end, change);
    changes[segment_id].Merge(change);
  }
  void Push(int segment_id, int start, int end) {
    if (!changes[segment_id].HasChange()) return;
    int mid = (start + end) / 2;
    int left_segment_id = segment_id + 1;
    int right_segment_id = segment_id + 2 * (mid - start + 1);
    ApplyAndMerge(left_segment_id, start, mid, changes[segment_id]);
    ApplyAndMerge(right_segment_id, mid + 1, end, changes[segment_id]);
    changes[segment_id] = SegmentChange();
  }
  Segment Query(int query_start, int query_end, int segment_id, int start, int end) {
    if (query_start <= start && end <= query_end) return tree[segment_id];
    int mid = (start + end) / 2;
    int left_segment_id = segment_id + 1;
    int right_segment_id = segment_id + 2 * (mid - start + 1);
    Push(segment_id, start, end);
    if (query_end <= mid) return Query(query_start, query_end, left_segment_id, start, mid);
    if (mid < query_start) return Query(query_start, query_end, right_segment_id, mid + 1, end);
    Segment response = Query(query_start, query_end, left_segment_id, start, mid);
    response.Merge(Query(query_start, query_end, right_segment_id, mid + 1, end));
    return response;
  }
  Segment Query(int query_start, int query_end) { return Query(query_start, query_end, 1, 0, initial_n - 1); }
  Segment QueryFull(void) { return tree[1]; }
  void Update(int update_start, int update_end, const SegmentChange &change, int segment_id, int start, int end) {
    if (end < update_start || update_end < start) return;
    if (update_start <= start && end <= update_end) {
      ApplyAndMerge(segment_id, start, end, change);
      return;
    }
    int mid = (start + end) / 2;
    int left_segment_id = segment_id + 1;
    int right_segment_id = segment_id + 2 * (mid - start + 1);
    Push(segment_id, start, end);
    Update(update_start, update_end, change, left_segment_id, start, mid);
    Update(update_start, update_end, change, right_segment_id, mid + 1, end);
    tree[segment_id].Merge(tree[left_segment_id], tree[right_segment_id]);
  }
  void Update(int update_start, int update_end, const SegmentChange &change) { Update(update_start, update_end, change, 1, 0, initial_n - 1); }
};

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;
  int Q;
  cin >> Q;
  vector<Long> b(N);
  for (int i = 0; i < N; i++) cin >> b[i];
  vector<Long> c(N);
  for (int i = 0; i < N; i++) cin >> c[i];

  vector<Segment> segments;
  Long prefix_sum = 0LL;
  for (int i = 0; i < 2 * N; i++) {
    prefix_sum += b[i % N] - c[i % N];
    segments.push_back(Segment(prefix_sum));
  }

  SegmentTree st(2 * N);
  st.Build(segments);

  while (Q--) {
    int t;
    int i;
    cin >> t >> i;
    i--;
    if (t != 1) {
      Long x;
      cin >> x;
      Long delta = 0;
      if (t == 2) {
        delta = x - b[i];
        b[i] = x;
      } else {
        delta = c[i] - x;
        c[i] = x;
      }
      SegmentChange to_add(delta);
      st.Update(i, 2 * N - 1, to_add);
      st.Update(i + N, 2 * N - 1, to_add);
    } else {
      Long prev_prefix = i == 0 ? 0LL : st.Query(i - 1, i - 1).minimum;
      int L = i;
      int R = i + N - 1;
      if (st.Query(L, L).minimum - prev_prefix < 0) {
        cout << 1 + L << endl;
      } else if (st.Query(L, R).minimum - prev_prefix >= 0) {
        cout << -1 << endl;
      } else {
        while (R - L > 1) {
          int M = (L + R) / 2;
          if (st.Query(i, M).minimum - prev_prefix >= 0) {
            L = M;
          } else {
            R = M;
          }
        }
        int last = 1 + R % N;
        cout << last << endl;
      }
    }
  }
  return 0;
}
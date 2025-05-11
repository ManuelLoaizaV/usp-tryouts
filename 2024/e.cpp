#include <algorithm>
#include <cmath>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <set>
#include <tuple>
#include <vector>

using Long = long long;
using Double = long double;

const Double EPS = 1e-4;

class Edge {
private:
    int u;
    int v;
    Long a;
    Long b;
    Long c;
public:
    void Read(void) {
        std::cin >> this->u;
        std::cin >> this->v;
        (this->u)--;
        (this->v)--;
        std::cin >> this->a;
        std::cin >> this->b;
        std::cin >> this->c;
    }

    Double Weight(Double t) const {
        return (this->a) * t * t + (this->b) * t + (this->c);
    }

    std::tuple<Long, Long, Long> Parabole(void) const {
        return {this->a, this->b, this->c};
    }

    std::pair<int, int> Endpoints(void) const {
        return {this->u, this->v};
    }

    std::tuple<Long, Long, Long> operator-(const Edge& other) const {
        auto p = this->Parabole();
        auto q = other.Parabole();
        return {
            std::get<0>(p) - std::get<0>(q),
            std::get<1>(p) - std::get<1>(q),
            std::get<2>(p) - std::get<2>(q)
        };
    }
};

std::vector<Double> FindRoots(const std::tuple<Long, Long, Long>& p) {
    const auto [a, b, c] = p;
    if (a == 0LL) {
        if (b == 0LL) {
            return {};
        }
        return {(-1.0L) * c / b};
    }
    Long d = b * b - 4LL * a * c;
    if (d < 0) {
        return {};
    }
    Double den = 2.0L * a;
    if (d == 0) {
        return {-b / den};
    }
    auto s = std::sqrt((Double)d);
    return {(-b - s) / den, (-b + s) / den};
}

int N, M;
std::vector<Edge> edges;

struct DisjointSets {
    std::vector<int> parent;
    std::vector<int> size;
    void MakeSet(int u) {
        parent[u] = u;
        size[u] = 1;
    }
    void Build(int n) {
        parent.resize(n);
        size.resize(n);
        for (int i = 0; i < n; ++i) {
            MakeSet(i);
        }
    }
    int Find(int u) {
        if (parent[u] == u) return u;
        return (parent[u] = Find(parent[u]));
    }
    void Join(int u, int v) {
        u = Find(u);
        v = Find(v);
        if (u != v) {
            if (size[u] > size[v]) std::swap(u, v);
            parent[u] = v;
            size[v] += size[u];
        }
    }
    bool SameSet(int u, int v) { return Find(u) == Find(v); }
    int GetSize(int u) { return size[Find(u)]; }
} dsu;

Double MST(Double t) {
    dsu.Build(N);
    Double cost{0.0L};
    sort(edges.begin(), edges.end(), [&](const Edge& e, const Edge& f) {
        return e.Weight(t) < f.Weight(t);
    });
    for (const Edge& edge: edges) {
        const auto [u, v] = edge.Endpoints();
        auto w = edge.Weight(t);
        if (!dsu.SameSet(u, v)) {
            dsu.Join(u, v);
            cost += w;
        }
    }
    return cost;
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> N >> M;
    edges.resize(M);
    for (auto& edge : edges) edge.Read();

    std::set<Double> timestamps;
    timestamps.insert(-100000000.0L);
    timestamps.insert(100000000.0L);
    for (int i = 0; i < M - 1; ++i) {
        for (int j = i + 1; j < M; ++j) {
            auto p = edges[i] - edges[j];
            auto roots = FindRoots(p);
            for (const auto& r : roots) timestamps.insert(r);
        }
    }

    Double min_cost = std::numeric_limits<long double>::infinity();
    for (auto lit = timestamps.begin(); lit != timestamps.end(); ++lit) {
        auto rit = lit;
        ++rit;
        if (rit == timestamps.end()) break;
        auto L = *lit;
        auto R = *rit;
        while (R - L > EPS) {
            auto M1 = L + (R - L) / 3.0L;
            auto M2 = R - (R - L) / 3.0L;
            if (MST(M1) < MST(M2)) {
                R = M2;
            } else {
                L = M1;
            }
        }
        auto best = (L + R) / 2.0L;
        min_cost = std::min(min_cost, MST(best));
    }
    std::cout << std::fixed << std::setprecision(6) << min_cost << std::endl;
    return 0;
}
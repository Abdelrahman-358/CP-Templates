
// Range-update + range-query for invertible operations using two BITs
// Supported operations: addition/subtraction (sum)
struct Fenwick {
    int n;
    vector<long long> f;

    Fenwick(int n) : n(n), f(n + 1) {}

    // point update: f[i] = f[i] + v
    void update(int i, int v) {
        for (; i <= n; i += i & -i)
            f[i] = f[i] + v;
    }

    // prefix query: sum(1..i)
    int query(int i) const {
        int s = 0;
        for (; i > 0; i -= i & -i)
            s = s + f[i];
        return s;
    }
};

struct RangeBITSum {
    Fenwick B1, B2;

    RangeBITSum(int n) : B1(n), B2(n) {}

    void range_add(int l, int r, int v) {
        // B1: +v at l, -v at r+1
        B1.update(l, v);
        B1.update(r + 1, -v);
        // B2: +v*(l-1) at l, -v*r at r+1
        B2.update(l, v * (l - 1));
        B2.update(r + 1, -v * r);
    }

    // prefix sum [1..x]
    int prefix_sum(int x) const {
        return B1.query(x) * x - B2.query(x);
    }

    // range sum [l..r]
    int range_sum(int l, int r) const {
        return prefix_sum(r) - prefix_sum(l - 1);
    }
};

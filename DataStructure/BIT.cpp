struct BIT {
    int mx;
    vector<int> bit;
    BIT(int n) {
        mx = n;
        bit.assign(n + 5, 0);
    }
    void build(vector<int> &a) {  // o(n)
        for (int i = 1; i <= (int) a.size(); i++) {
            bit[i] += a[i - 1];
            int r = i + (i & -i);
            if (r <= mx) bit[r] += bit[i];
        }
    }
    void update(int i, int delta) {
        while (i <= mx) {
            bit[i] = (bit[i] + delta);
            i += (i & -i);
        }
    }
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum = (sum + bit[i]);
            i -= (i & -i);
        }
        return sum;
    }
    int query(int l, int r) {
        return (query(r) - query(l - 1));
    }

    // find smallest idx such that prefix_sum(idx) >= target ---
    int lower_bound(int target) const {
        int idx = 0;
        // compute the largest power of two ≤ mx
        int pw = 1;
        while ((pw << 1) <= mx) pw <<= 1;
        int rem = target;
        for (int step = pw; step > 0; step >>= 1) {
            int nxt = idx + step;
            if (nxt <= mx && bit[nxt] < rem) {
                rem -= bit[nxt];
                idx = nxt;
            }
        }
        // idx is now the largest pos where prefix < target
        return idx + 1;
    }
};
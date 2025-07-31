
struct SuffixArray {
    // o(nlog(n))
    int n;
    vector<int> suff, lcp, rank;
    vector<int> cc[25];

    SuffixArray(int sz) {
        n = sz + 1;
        suff.resize(n);
        lcp.resize(n);
        rank.resize(n);
    }

    void countingSort(vector<int> &p, vector<int> &c) {
        vector<int> cnt(n);
        for (int i: c)
            cnt[i]++;

        vector<int> pos(n);
        for (int i = 1; i < n; ++i)
            pos[i] = pos[i - 1] + cnt[i - 1];

        vector<int> newP(n);
        for (int i: p)
            newP[pos[c[i]]++] = i;

        p = newP;
    }

    void build(string s) {
        s += '$';
        vector<int> c(n);
        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; ++i)
            a[i] = {s[i], i};

        sort(a.begin(), a.end());

        vector<int> p(n);
        for (int i = 0; i < n; ++i)
            p[i] = a[i].second;

        for (int i = 1; i < n; ++i)
            c[a[i].second] = c[a[i - 1].second] + (a[i].first != a[i - 1].first);

        int k = 0;
        cc[k] = c;
        while ((1 << k) < n) {
            int bit = 1 << k;
            for (int i = 0; i < n; ++i)
                p[i] = (p[i] - bit + n) % n;

            countingSort(p, c);
            vector<int> newC(n);
            for (int i = 1; i < n; ++i) {
                int currL = p[i], currR = (p[i] + bit) % n;
                int preL = p[i - 1], preR = (p[i - 1] + bit) % n;
                bool add = (c[currL] != c[preL]) || (c[currR] != c[preR]);
                newC[p[i]] = newC[p[i - 1]] + add;
            }
            c = newC;
            ++k;
            cc[k] = c;
        }
        suff = p;
        //build rank of indecies
        for (int i = 0; i < suff.size(); ++i) {
            rank[suff[i]] = i;
        }
        // Build LCP
        k = 0;
        for (int i = 0; i < n - 1; ++i) {
            int pi = c[i];
            if (pi == 0) {
                k = 0;
                continue;
            }
            int j = p[pi - 1];
            while (s[i + k] == s[j + k])
                ++k;
            lcp[pi] = k;
            k = max(0LL, k - 1);
        }
    }
};

---
Some of the applications on suffix array


vector<int> LCP_two_strings(string &s, string &t) {
    int n = (int) s.size(), m = (int) t.size();
    string tem = s + '#' + t;
    SuffixArray sf((int) tem.size());
    sf.build(tem);
    vector<int> f(m, 0);
    stack<int> st;
    for (int i = 0; i < sf.suff.size(); i++) {
        if (sf.suff[i] < n) {
            int mn = sf.lcp[i];
            while ((int) st.size()) {
                int pos = sf.suff[st.top()];
                if (pos >= n + 1 and pos - (n + 1) < m) {
                    f[pos - (n + 1)] = mn;
                }
                mn = min(mn, sf.lcp[st.top()]);
                st.pop();
            }
        } else if (sf.suff[i] > n) {
            st.push(i);
        }
    }
    stack<int> st2;
    for (int i = (int) sf.suff.size() - 1; i >= 0; i--) {
        if (sf.suff[i] > n) {
            st2.push(i);
        } else if (sf.suff[i] < n) {
            int mn = n + m + 5;
            while ((int) st2.size()) {
                int pos = sf.suff[st2.top()];
                if (pos >= n + 1 && pos - (n + 1) < m) {
                    mn = min(mn, sf.lcp[st2.top()]);
                    f[pos - (n + 1)] = max(mn, f[pos - (n + 1)]);
                }
                st2.pop();
            }
        }
    }
    // f[i] -> The longest common prefix between s and t
    //         that starts at position i in string t
    return f;
}


void sortSubstrings() {
    string s;
    cin >> s;
    SuffixArray sf((int) s.size());
    sf.build(s);
    struct Q {
        int l, r, idx;
    };
    int q;
    cin >> q;
    vector<Q> v(q);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        v[i] = {l, r, i};
    }
    vector<int> flog(s.size() + 2, 0);
    for (int i = 2; i <= s.size(); i++) {
        flog[i] = flog[i / 2] + 1;
    }
    auto comp = [&](const Q &a, const Q &b) {
        int l1 = a.l, r1 = a.r, len1 = r1 - l1 + 1;
        int l2 = b.l, r2 = b.r, len2 = r2 - l2 + 1;
        int L = min(len1, len2);
        int k = flog[L];
        pair<int, int> p1 = {sf.cc[k][l1], sf.cc[k][l1 + L - (1 << k)]};
        pair<int, int> p2 = {sf.cc[k][l2], sf.cc[k][l2 + L - (1 << k)]};
        if (p1 != p2)return p1 < p2;
        if (len1 != len2)return len1 < len2;
        if (l1 != l2)return l1 < l2;
        return r1 < r2;
    };
    sort(v.begin(), v.end(), comp);
    for (auto i: v)cout << i.l + 1 << ' ' << i.r + 1 << endl;
}


void calcAllBordersForAllSubstrings() {
    // Border is a prefix that also a suffix
    struct DSU {
        vector<int> parent, sz;

        DSU(int n) {
            parent = vector<int>(n + 1);
            iota(parent.begin(), parent.end(), 0);
            sz = vector<int>(n + 1, 1);
        }

        int find(int u) {
            if (parent[u] == u)return u;
            return parent[u] = find(parent[u]);
        }

        int merge(int u, int v) {
            int leader1 = find(u);
            int leader2 = find(v);
            if (leader1 == leader2)return 0;
            int before = sz[leader2] * (sz[leader2] - 1) / 2 + sz[leader1] * (sz[leader1] - 1) / 2;
            if (sz[leader1] > sz[leader2]) swap(leader2, leader1);
            parent[leader1] = leader2;
            sz[leader2] += sz[leader1];
            int after = sz[leader2] * (sz[leader2] - 1) / 2;
            return after - before;
        }
    };
    string s;
    cin >> s;
    int n = (int) s.size();
    SuffixArray sf(n);
    sf.build(s);
    s+='$';
    vector<int> bucket[s.size() + 1], bucketLen[s.size() + 1];
    for (int i = 0; i < sf.lcp.size(); ++i) {
        int len = n - sf.suff[i];
        if (len > 0) bucketLen[len].push_back(i);
        bucket[sf.lcp[i]].push_back(i);
    }
    vector<int> active(s.size() + 1, 0);
    DSU ds(n + 3);
    int ans = n * (n + 1) / 2;
    for (int i = (int) s.size() - 1; i >= 1; i--) {
        active[bucketLen[i].back()] = 1;
        for (auto j: bucket[i]) {
            if (active[j] and active[j - 1]) {
                ans += (ds.merge(j, j - 1) * i);
            }
        }
    }
    cout << ans << endl;
}
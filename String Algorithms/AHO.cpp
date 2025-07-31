struct Aho {
    int N, A, st;
    vector<vector<int>> nxt, out;
    vector<int> link, out_link;

    Aho(int A = 26, char st = 'a') :
            N(0), A(A), st(st) { node(); }

    int node() {
        nxt.emplace_back(A, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(0);
        return N++;
    }

    int get(char ch) { return ch - st; }

    void add_pattern(const string &p, int idx) {
        int u = 0;
        for (auto &c: p) {
            if (!nxt[u][get(c)])
                nxt[u][get(c)] = node();
            u = nxt[u][get(c)];
        }
        out[u].push_back(idx);
    }

    void build() {
        queue<int> q;
        for (q.push(0); !q.empty();) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < A; ++c) {
                int v = nxt[u][c];
                if (!v) nxt[u][c] = nxt[link[u]][c];
                else {
                    link[v] = u ? nxt[link[u]][c] : 0;
                    out_link[v] = out[link[v]].empty() ?
                                  out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }

    string find_smallest_string(int L) {
        // Find the smallest string that does not match any pattern
        string res;
        int u = 0;
        for (int i = 0; i < L; ++i) {
            for (int c = 0; c < 26; c++) {
                int v = nxt[u][c];
                if (out[v].empty()) {
                    res.push_back((c + 'a'));
                    u = v;
                    break;
                }

            }
        }
        return res;
    }

    vector<vector<int>> find_all(string s, vector<string> pat, Aho aho) {
        // Find all occurrences of each pattern
        vector<vector<int>> oc((int) pat.size());
        int cur = 0;
        for (int i = 0; i < s.size(); i++) {
            cur = aho.advance(cur, s[i]);
            for (int v = cur; v; v = aho.out_link[v]) {
                for (auto idx: aho.out[v]) {
                    oc[idx].push_back(i - (int) pat[idx].size() + 1);
                }

            }
        }
        return oc;
    }

    int advance(int u, char c) {
        while (u && !nxt[u][get(c)]) u = link[u];
        return nxt[u][get(c)];
    }
};
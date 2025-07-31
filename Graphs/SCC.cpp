    // SCC Kosaraju’s algorithm
    int n, m;
    cin >> n >> m;
    vector<int> g[n + 1], rg[m + 1];
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        rg[y].push_back(x);
    }
    vector<int> compo;
    vector<int> vis(n + 1, 0);
    function<void(int, int, vector<int>[])> dfs = [&](int u, int p, vector<int> adj[]) {
        vis[u] = 1;
        for (auto v: adj[u]) {
            if (not vis[v]) {
                dfs(v, u, adj);
            }
        }
        compo.push_back(u);
    };
    for (int i = 1; i < n + 1; ++i) {
        if (vis[i])continue;
        dfs(i, i, g);
    }
    reverse(compo.begin(), compo.end());
    vector<int> order = compo;
    int king = 1;  // the leader of each component
    vector<int> id(n + 1);
    vis.assign(n + 1, 0);
    for (int u: order) {
        if (vis[u])continue;
        compo.clear();
        dfs(u, u, rg);
        for (auto x: compo)id[x] = king;
        king++;
    }
    cout << king - 1 << endl;  // number of components
    for (int i = 0; i < n; ++i) {
        cout << id[i + 1] << ' ';
    }
    cout << endl;


    // SCC Targan's
    const int N = 2e5;
    vector<vector<int>> adj, dag, comps;
    int comp[N], inStack[N], lowLink[N], dfn[N], deg[N];
    stack<int> st;
    int ndfn;

    void tarjan(int u) {
        dfn[u] = lowLink[u] = ndfn++;
        inStack[u] = true;
        st.push(u);
        for (auto &v: adj[u]) {
            if (dfn[v] == -1) {
                tarjan(v);
                lowLink[u] = min(lowLink[u], lowLink[v]);
            } else if (inStack[v]) {
                lowLink[u] = min(lowLink[u], dfn[v]);
            }
        }
        if (dfn[u] == lowLink[u]) {
            // head of component
            int x = -1;
            comps.emplace_back(vector<int>());
            while (x != u) {
                x = st.top();
                st.pop();
                inStack[x] = 0;
                comps.back().emplace_back(x);
                comp[x] = comps.size() - 1;
            }
        }
    }

    void genDag() {
        dag.resize(comps.size());
        for (int u = 0; u < adj.size(); u++) {
            for (auto &v: adj[u]) {
                if (comp[u] != comp[v]) {
                    dag[comp[u]].emplace_back(comp[v]);
                    deg[comp[v]]++;
                }
            }
        }
    }

    void SCC(int n) {
        ndfn = 0;
        comps.clear();
        for (int i = 0; i < n; ++i) {
            dfn[i] = -1;
            lowLink[i] = inStack[i] = deg[i] = 0;
        }
        for (int i = 0; i < n; i++)
            if (dfn[i] == -1) tarjan(i);
        genDag();
    }

    void solve() {
        int n, m;
        cin >> n >> m;
        adj.resize(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            adj[u].emplace_back(v);
        }
        SCC(n);
        cout << comps.size() << endl;  // Number of components
        for (int i = 0; i < n; i++) {
            cout << comp[i] + 1 << " ";
        }
        cout << endl;
    }
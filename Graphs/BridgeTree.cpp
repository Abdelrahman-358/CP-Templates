    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
    }
    vector<int> vis(n + 1, 0), low(n + 1, 1e9), depth(n + 1, 0), is_bridge(m + 1), is_cutPoint(n + 1, 0);
    int bridges = 0;
    function<void(int, int)> dfs1 = [&](int v, int p) {
        vis[v] = 1;
        int kids = 0;
        for (auto [u, e]: adj[v]) {
            if (u == p)continue;
            if (vis[u]) {
                low[v] = min(low[v], depth[u]);
                continue;
            }
            kids++;
            depth[u] = depth[v] + 1;
            dfs1(u, v);
            low[v] = min(low[v], low[u]);
            if (low[u] > depth[v]) {
                bridges++;
                is_bridge[e] = 1;
            }
            if (low[u] >= depth[v]) {
                is_cutPoint[u] = (p != -1 || kids > 1);
            }
        }
    };
    dfs1(1, -1);
    int cur = 0;
    vector<int> id(n + 1, -1);
    function<void(int)> dfs = [&](int v) {
        id[v] = cur;
        for (auto [u, e]: adj[v]) {
            if (is_bridge[e] or id[u] != -1)continue;
            dfs(u);
        }
    };
    for (int i = 1; i <= n; i++) {
        if (id[i] != -1)continue;
        dfs(i);
        cur++;
    }

    vector<vector<int>> bridge_Tree(n + 1);
    for (int v = 1; v <= n; v++) {
        for (auto [u, e]: adj[v]) {
            if (id[v] != id[u]) {
                bridge_Tree[id[v]].push_back(id[u]);
            }
        }
    }
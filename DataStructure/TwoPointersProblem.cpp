void solve() {
    // Given an array of n integers ai Let's say that a segment of this array a[l..r]
    // is good if on this segment it is possible to choose a certain set of numbers whose sum is equal to s
    // Your task is to find the shortest good segment. n=1e5 and s=1000
    int n, x;
    cin >> n >> x;
    vector<int> v(n);
    for (auto &i: v)cin >> i;
    int freq[2005] = {0};
    vector<vector<int>> remove(n + 1);
    freq[0] = 1;
    int ans = INT_MAX;
    int l = 0;
    for (int r = 0; r < n; r++) {
        if (v[r] <= x)
            for (int i = x - v[r]; i >= 0; i--) {
                freq[i + v[r]] += freq[i];
            }
        while (freq[x]) {
            for (int i = 0; i + v[l] <= x; ++i) {
                freq[v[l] + i] -= freq[i];
            }
            ans = min(ans, r - l + 1);
            l++;
        }
    }
    cout << (ans == INT_MAX ? -1 : ans) << endl;
}
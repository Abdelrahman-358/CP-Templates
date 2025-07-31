pair<string, vector<int>> Manachers(string t) {
    string s = "#";
    for (int i = 0; i < t.size(); ++i) {
        s += '*';
        s += t[i];
    }
    s += "*^";
    int n = (int) s.size();
    vector<int> p(n, 0);  // p[i] -> max palindrome length centered at i
    for (int i = 1, l = 0, r = 0; i < n - 2; i++) {
        if (i < r) {
            p[i] = min(p[l - (i - l)], r - i);
        }
        while (s[i + p[i] + 1] == s[i - p[i] - 1])p[i]++;
        if (i + p[i] > r) {
            l = i;
            r = i + p[i];
        }
    }
    // start of palindrome = (i - p[i] + 1)
    return make_pair((s.substr(1, s.size() - 2)), vector<int>(begin(p) + 1, end(p) - 1));
}
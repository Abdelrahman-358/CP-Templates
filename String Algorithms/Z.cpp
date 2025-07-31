vector<int> zFunction(string t) {
    string s = t;
    int n = s.size();
    vector<int> z(n + 1, 0);
    for (int i = 1, l = 0, r = 0; i < s.size(); i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (s[i + z[i]] == s[z[i]])z[i]++;
        if (i + z[i] - 1 > r) {
            l = i, r = i + z[i] - 1;
        }
    }
    return z;
}
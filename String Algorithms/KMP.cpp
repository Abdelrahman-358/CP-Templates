vector<int> piFunction(string s) {
    vector<int> pi(s.size() + 1, 0);
    int len = 0;
    for (int i = 1; i < s.size(); i++) {
        while (len > 0 and s[i] != s[len])
            len = pi[len - 1];
        if (s[i] == s[len])len++;
        pi[i] = len;
    }
    return pi;
}
//  for any prefix of string s which matches a suffix of string s,
//  print the number of times it occurs in string s as a substring.
void compute(string s) {
    string s;
    cin >> s;
    vector<int> pi = piFunction(s);
    vector<int> fre(s.size());
    for (int i = 0; i < s.size(); ++i) {
        fre[pi[i]]++;
    }
    for (int i = s.size() - 1; i > 0; i--) {
        fre[pi[i - 1]] += fre[i];
    }
    for (int i = 0; i < s.size(); ++i) {
        fre[i]++;
    }
    vector <pair<int, int>> ans;
    int i = pi[s.size() - 1];
    while (i > 0) {
        ans.push_back({i, fre[i]});
        i = pi[i - 1];
    }
    reverse(all(ans));
    cout << ans.size() + 1 << endl;
    for (auto [i, j]: ans)cout << i << ' ' << j << endl;
    cout << s.size() << ' ' << 1 << endl;
}

void compute_automaton(string s, vector <vector<int>> &aut) {
    s += '#';
    int n = (int) s.size();
    vector<int> pi = piFunction(s);
    aut.assign(n, vector<int>(26));
    aut[0][s[0] - 'a'] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (s[i] - 'a' == j) aut[i][j] = i + 1;
            else aut[i][j] = aut[pi[i - 1]][j];
        }
    }
}
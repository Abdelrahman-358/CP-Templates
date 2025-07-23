// Returns the starting index of the lexicographically minimal rotation of s 
// O(N) 
int booth(const string &s) {
    int n = s.size();
    string S = s + s;
    vector<int> f(n * 2, -1);     // failure function
    int k = 0;                  // least rotation of S[0..i]
    for (int j = 1; j < 2 * n; ++j) {
        int i = f[j - k - 1];
        while (i != -1 && S[j] != S[k + i + 1]) {
            if (S[j] < S[k + i + 1])
                k = j - i - 1;
            i = f[i];
        }
        if (S[j] != S[k + i + 1]) {
            if (S[j] < S[k]) k = j;
            f[j - k] = -1;
        } else {
            f[j - k] = i + 1;
        }
    }
    return k;
}
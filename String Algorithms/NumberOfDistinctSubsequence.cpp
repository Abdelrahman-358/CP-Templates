int countDistinctSubSequence(string s) {
    int n = (int) s.size();
    vector<int> dp(n + 2, 0);
    vector<int> last(27, -1);
    dp[0] = 1; // empty subsequence
    for (int i = 1; i <= n; i++) {
        dp[i] = 2 * dp[i - 1];
        dp[i] %= MOD;
        if (last[s[i - 1] - 'a'] != -1) {
            dp[i] = (dp[i] + MOD - (dp[last[s[i - 1] - 'a']])) % MOD;
        }
        last[s[i - 1] - 'a'] = i - 1;
    }
    return dp[n];
}

int MAXN = 1e7;
vector<int> spf(MAXN, 1);

void sieve() { // o(log(log(n)))
    spf[0] = 0;
    for (int i = 2; i <= MAXN; i++) {
        if (spf[i] == 1) {
            for (int j = i; j <= MAXN; j += i) {
                if (spf[j] == 1) spf[j] = i;
            }
        }
    }
}

vector<int> getPrimeFactors(int n) {  // o(log(n))
    vector<int> f;
    while (n > 1) {
        f.push_back(spf[n]);
        n /= spf[n];
    }
    return f;
}

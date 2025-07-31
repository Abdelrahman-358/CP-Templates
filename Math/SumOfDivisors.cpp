long long numberOfDivisors(long long num) {
    long long total = 1;
    for (int i = 2; (long long)i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);
            total *= e + 1;
        }
    }
    if (num > 1) {
        total *= 2;
    }
    return total;
}


long long SumOfDivisors(long long num) {
    long long total = 1;

    for (int i = 2; (long long)i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);

            long long sum = 0, pow = 1;
            do {
                sum += pow;
                pow *= i;
            } while (e-- > 0);
            total *= sum;
        }
    }
    if (num > 1) {
        total *= (1 + num);
    }
    return total;
}


SumOfDivisorsFrom_1_to_n
using ll = long long;
const ll MOD = 1000000007;

// Compute x mod MOD safely
inline ll modmul(ll a, ll b){
    return (a % MOD) * (b % MOD) % MOD;
}
// Sum of integers from L to R modulo MOD
inline ll rangeSum(ll L, ll R){
    // (L + R) * (R - L + 1) / 2 mod MOD
    ll cnt = (R - L + 1) % MOD;
    ll sumLR = ( (L % MOD) + (R % MOD) ) % MOD;
    ll res = modmul(sumLR, cnt);
    // divide by 2 modulo:
    if (res & 1) res += MOD;
    return (res / 2) % MOD;
}

void sumDivFrom_1_to_n(int n){
    ll D = floor(sqrtl(n));
    ll ans = 0;

    // Part 1: d from 1..D
    for(ll d = 1; d <= D; d++){
        ll t = n / d;
        ans = (ans + modmul(d, t)) % MOD;
    }
    // Part 2: group by k = floor(n/d), for k = 1..n/(D+1)
    ll maxk = n / (D + 1);
    for(ll k = 1; k <= maxk; k++){
        ll L = n / (k + 1) + 1;
        ll R = n / k;
        if (L > R) continue;
        ans = (ans + modmul(k % MOD, rangeSum(L, R))) % MOD;
    }
    cout << ans << endl;
}
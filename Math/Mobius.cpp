int mobius[N];

void Mobius() {
    // nlog(n)
    mobius[1] = -1;
    for (int i = 1; i < N; i++) {
        if (mobius[i]) {
            mobius[i] = -mobius[i];
            for (int j = 2 * i; j < N; j += i) { mobius[j] += mobius[i]; }
        }
    }
}
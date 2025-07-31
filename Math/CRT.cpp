//If we can solve 2 cong equations and merge in 1, we can solve sequentially
// T = x mod N     -> T=N*K + x
// T = y mod M     -> T=M*p + y
// N*K + x= M*p+y  -> N*K - M*p = y-x -> Linear Diophantine equation
ll solveSystemOfCongruences_Not_Relatives(vector<int> &rems, vector<int> &mods) {
    int rem = rems[0], mod = mods[0];
    // solve with prev equation
    for (int i = 1; i < (int) rems.size(); i++) {
        int x, y, a = mod, b = -mods[i], c = rems[i] - rem;
        int g;
        bool found = find_any_solution(a, b, c, x, y, g);
        if (!found)return -1;

        rem += mod * x;  // Evaluate previous congruence
        mod = mod / g * mods[i];  // merged mod : lcm modes so far
        rem = (rem % mod + mod) % mod; // merged rem
    }
    return rem;
}
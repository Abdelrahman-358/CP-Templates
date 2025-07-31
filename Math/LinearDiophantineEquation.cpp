int gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

void shift_solution(int &x, int &y, int a, int b, int cnt) {
    x += cnt * b;
    y -= cnt * a;
}

int find_all_solutions(int a, int b, int c, int minx, int maxx, int miny, int maxy) {
    int x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return 0;
    a /= g;
    b /= g;

    int sign_a = a > 0 ? +1 : -1;
    int sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx)
        shift_solution(x, y, a, b, sign_b);
    if (x > maxx)
        return 0;
    int lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx)
        shift_solution(x, y, a, b, -sign_b);
    int rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny)
        shift_solution(x, y, a, b, -sign_a);
    if (y > maxy)
        return 0;
    int lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy)
        shift_solution(x, y, a, b, sign_a);
    int rx2 = x;

    if (lx2 > rx2)
        swap(lx2, rx2);
    int lx = max(lx1, lx2);
    int rx = min(rx1, rx2);

    if (lx > rx)
        return 0;
    return (rx - lx) / abs(b) + 1;
}


void solve() {
    ll a, b, c, x1, x2, y1, y2;
    cin>>a>>b>>c>>x1>>x2>>y1>>y2;
    c=-c;                                                       //we are solving in Ax+By=C format but the i/p is in ax+by+c=0 format hence we reverse c's sign.
    if(a==0 && b==0 && c==0) cout<<(x2-x1+1)*(y2-y1+1)<<endl;   //this is the trivial case 0+0=0 and all numbers in the interval will satisfy the equation
    else if(a==0 && b==0) cout<<0<<endl;                        //only a and b are 0 => 0=C
    else if(a==0){                                              //only a is 0, By=C
        if(c%b!=0 || y1>c/b || y2<c/b) cout<<0<<endl;           //Ans is 0 when y doesn't exist ie. C doesn't divide B; or C does divide B but C/B doesn't fall in the given interval
        else cout<<(x2-x1+1)<<endl;                             //if such a y exists in the given interval, then it can be paired with any x in the given interval     }
    }
    else if(b==0){                                              //Ax=C, same thing as above.
        if(c%a!=0 || x1>c/a || x2<c/a) cout<<0<<endl;
        else cout<<(y2-y1+1)<<endl;
    }
    else cout<<find_all_solutions(a, b, c, x1,x2,y1,y2)<<endl; //Above were the edge cases. Onto the real problem!
}

// find any solution for many parameters
// Extended Euclidean algorithm: finds x,y such that a*x + b*y = gcd(a,b)
ll extgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = (a >= 0 ? 1 : -1);
        y = 0;
        return llabs(a);
    }
    ll x1, y1;
    ll g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Compute gcd and coefficients for n numbers: returns (g, u) such that sum(a[i]*u[i]) = g
pair<ll, vector<ll>> multi_extgcd(const vector<ll> &a) {
    if (a.size() == 1)
        return { llabs(a[0]), { a[0] >= 0 ? 1 : -1 } };
    auto tail = vector<ll>(a.begin() + 1, a.end());
    auto [g2, u2] = multi_extgcd(tail);
    ll x, y;
    ll g = extgcd(a[0], g2, x, y);
    vector<ll> u(a.size());
    u[0] = x;
    for (size_t i = 1; i < a.size(); i++)
        u[i] = y * u2[i - 1];
    return { g, u };
}
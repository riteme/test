
    for(ll i = n; i; ) {
        i /= pi;
        k += i;
    }
    for(ll i = m; i; ){
        i /= pi;
        k -= i;
    }
    for(ll i = n - m; i; ){
        i /= pi;
        k -= i;
    }
ll fp2(ll a, ll b, ll m) {
    ll ans = 1;
    m--;
    while(b)
    {
        if(b & 1)ans = ans * a & m;
        b >>= 1;
        a = a * a & m;
    }
    return ans;
}

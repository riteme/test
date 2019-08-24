#include <bits/stdc++.h>
 
const int N = 1000;
const int M = N * N;
typedef long long ll;
typedef std::pair <int, int> pii;
 
struct P{
    int x, y, id;
 
    explicit P (int x = 0, int y = 0, int id = 0):x(x), y(y), id(id){}
    P operator -(const P &p)const{return P(x - p.x, y - p.y, 0);}
 
    bool operator <(const P &p)const{
        return y == p.y ? x < p.x : y < p.y;
    }
};
 
struct P1{
    double x, y;
 
    explicit P1 (double x = 0, double y = 0):x(x), y(y){}
 
    P1 operator + (const P1 &p)const{return P1 (x + p.x, y + p.y);}
    P1 operator - (const P1 &p)const{return P1 (x - p.x, y - p.y);}
    P1 operator * (const double &p)const{return P1 (x * p, y * p);}
    double operator %(const P1 &p)const{ return x * p.x + y * p.y;}
    double abs2()const{return *this % *this;}
};
 
struct L{
    P1 p, v;
 
    L (){}
    L (P1 a, P1 b):p(a), v(b - a){}
};
 
P1 proj(L l, P1 p){
    return l.p + l.v * (l.v % ((p - l.p) * (1 / l.v.abs2())));
}
 
P p[N], oriP[N];
std::map <ll, std::vector <P>> map[M];
std::map <pii, int> map1;
int perm[N], inv[N];
 
int getMapId(int x, int y){
    auto u = map1.find({x, y});
    if (u == map1.end()){
        int sz = map1.size();
        map1[{x, y}] = sz;
        return sz;
    }
    return u -> second;
}
 
int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
        int x, y;
        scanf("%d%d", &x, &y);
        x += (int) 1e6 + 1;
        y += (int) 1e6 + 1;
        p[i] = P (x, y, i);
        oriP[i] = p[i];
    }
    for (int i = 0; i < n; ++ i){
        for (int j = i + 1; j < n; ++ j){
            P p1 = p[i] - p[j];
            int x = p1.x, y = p1.y;
            if (y < 0){
                x = -x, y = -y;
            }
            else if (y == 0){
                x = std::abs(x);
            }
            int gcd = std::abs(std::__gcd(x, y));
            x /= gcd, y /= gcd;
            ll pos = 1ll * y * p[i].x - 1ll * x * p[i].y;
            auto &vec = map[getMapId(x, y)][pos];
            vec.push_back(p[i]);
            vec.push_back(p[j]);
        }
    }
    double ans = 0.0;
    std::vector <pii> tangents;
    for (auto u : map1){
        tangents.push_back(u.first);
    }
    std::sort(tangents.begin(), tangents.end());
    tangents.erase(std::unique(tangents.begin(), tangents.end()), tangents.end());
    std::sort(tangents.begin(), tangents.end(), [](const pii &p1, const pii &p2) {
        return 1ll * p1.first * p2.second - 1ll * p1.second * p2.first > 0;
    });
    std::sort(p, p + n);
    for (int i = 0; i < n; ++ i){
        perm[i] = p[i].id;
        inv[p[i].id] = i;
    }
    for (int i = 0, sz = tangents.size(); i <= sz; ++ i){
        P p1 = oriP[perm[(n - 1) >> 1]], p2 = oriP[perm[((n - 1) >> 1) + 1]];
        pii tang1 = !i ? (pii) {1, 0} : tangents[i - 1], tang2 = i < sz ? tangents[i] : (pii){-1, 0};
        L l1, l2;
        l1.p = l2.p = P1 (0, 0);
        l1.v = P1 (-tang1.second, tang1.first), l2.v = P1(-tang2.second, tang2.first);
        std::vector <L> ls = {l1, l2};
        P line1(-tang1.second, tang1.first), line2(-tang2.second, tang2.first);
        P maxLine = p2 - p1;
        if (1ll * line1.x * maxLine.y - 1ll * line1.y * maxLine.x >= 0){
            if (1ll * maxLine.x * line2.y - 1ll * maxLine.y * line2.x >= 0){
                L l;
                l.p = P1(0, 0);
                l.v = P1(maxLine.x, maxLine.y);
                ls.push_back(l);
            }
        }
        maxLine = P (-maxLine.x, -maxLine.y);
        if (1ll * line1.x * maxLine.y - 1ll * line1.y * maxLine.x >= 0){
            if (1ll * maxLine.x * line2.y - 1ll * maxLine.y * line2.x >= 0){
                L l;
                l.p = P1(0, 0);
                l.v = P1(maxLine.x, maxLine.y);
                ls.push_back(l);
            }
        }
        for (auto l : ls){
            P1 proj1 = proj(l, P1 (p1.x, p1.y)), proj2 = proj(l, P1 (p2.x, p2.y));
            ans = std::max(ans, std::sqrt((proj2 - proj1).abs2()) * 0.5);
        }
        if (i == sz){
            break;
        }
        int id = getMapId(tangents[i].first, tangents[i].second);
        for (auto &u : map[id]){
            auto &vec = u.second;
            std::sort(vec.begin(), vec.end(), [](const P &p1, const P &p2){
                return p1.y == p2.y ? p1.x < p2.x : p1.y < p2.y;
            });
            vec.erase(std::unique(vec.begin(), vec.end(), [](const P &p1, const P &p2){
                return p1.id == p2.id;
            }), vec.end());
            std::vector <int> ids;
            for (auto v : vec){
                ids.push_back(v.id);
            }
            for (int j = 0, sz = ids.size(); j < sz >> 1; ++ j){
                int &pos1 = inv[ids[j]], &pos2 = inv[ids[sz - 1 - j]];
                std::swap(perm[pos1], perm[pos2]);
                std::swap(pos1, pos2);
            }
        }
    }
    printf("%.15f\n", ans);
    return 0;
}

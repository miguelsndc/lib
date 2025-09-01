#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

#define vc vector

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
    Point operator+(const Point& a) const { return Point(x + a.x, y + a.y); }
    Point operator-(const Point& a) const { return Point(x - a.x, y - a.y); }
    ll operator*(const Point& a) const { return (x * a.x + y * a.y); }  // DOT product  // norm // lenght^2 // inner
    ll operator%(const Point& a) const { return (x * a.y - y * a.x); }  // Cross // Vector product
    Point operator*(ll c) const { return Point(x * c, y * c); }
    Point operator/(ll c) const { return Point(x / c, y / c); }

    /********************
    // FOR DOUBLE POINT //
    const ld EPS = 1e-9;
    bool eq(ld a, ld b){ return abs(a-b) < EPS; } // ==
    bool lt(ld a, ld b){ return a + EPS < b;    } // <
    bool gt(ld a, ld b){ return a > b + EPS;    } // >
    bool le(ld a, ld b){ return a < b + EPS;    } // <=
    bool ge(ld a, ld b){ return a + EPS > b;    } // >=
    bool operator==(const PT&a) const{ return eq(x, a.x) && eq(y, a.y); }				// for double point
    bool operator< (const PT&a) const{ return eq(x, a.x) ? lt(y, a.y) : lt(x, a.x); }	// for double point
    bool operator<<(PT&a){ PT&p=*this; return eq(p%a, 0) ? lt(p*p, a*a) : lt(p%a, 0);  } //angle(this) < angle(a)
    //Change LL to LD and uncomment this
    //Also, consider replacing comparisons with these functions
    *********************/

    bool operator==(const Point& a) const { return x == a.x && y == a.y; }
    bool operator<(const Point& a) const { return x != a.x ? x < a.x : y < a.y; }
    bool operator<<(const Point& a) const {
        Point p = *this;
        return (p % a == 0) ? (p * p < a * a) : (p % a < 0);
    }  // angle(p) < angle(a)
};

vector<Point> ch(vector<Point> pts, bool sorted = false) {
    if (!sorted) sort(begin(pts), end(pts));
    pts.resize(unique(begin(pts), end(pts)) - begin(pts));
    if (pts.size() <= 1) return pts;
    int s = 0, n = pts.size();
    vector<Point> h(2 * n + 1);
    for (int i = 0; i < n; h[s++] = pts[i++])
        while (s > 1 && (pts[i] - h[s - 2]) % (h[s - 1] - h[s - 2]) > 0)
            s--;
    for (int i = n - 2, t = s; ~i; h[s++] = pts[i--])
        while (s > t && (pts[i] - h[s - 2]) % (h[s - 1] - h[s - 2]) > 0)
            s--;
    h.resize(s - 1);
    return h;
}

/* Checks if a point is inside the convex hull: O(log(n))*/

bool inside_triangle(Point a, Point b, Point c, Point point) {
    ll s1 = abs((b - a) % (c - b));
    ll area1 = abs((point - a) % (point - b));
    ll area2 = abs((point - b) % (point - c));
    ll area3 = abs((point - c) % (point - a));
    ll s2 = area1 + area2 + area3;
    return s1 == s2;
}
bool strictly_inside_triangle(Point a, Point b, Point c, Point point) {
    ll area = abs((b - a) % (c - a));
    ll area1 = abs((point - a) % (point - b));
    ll area2 = abs((point - b) % (point - c));
    ll area3 = abs((point - c) % (point - a));
    return area1 != 0 && area2 != 0 && area3 != 0 && area1 + area2 + area3 == area;
}

bool is_inside(vector<Point>& hull, Point p) {
    int n = hull.size();
    if (n == 1) return (hull.front() == p);

    int l = 1, r = n - 1;
    while (abs(r - l) > 1) {
        int mid = (r + l) / 2;
        Point to_mid = hull[mid] - hull[0];
        Point to_p = p - hull[0];
        if ((to_p % (to_mid)) < 0)
            r = mid;
        else
            l = mid;
    }
    return strictly_inside_triangle(hull[0], hull[l], hull[r], p);
}

void solve() {
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[i] = {x, y};
    }
    vector<Point> ans = ch(a);
    cout << ans.size() << '\n';
    for (auto [x, y] : ans) {
        cout << x << ' ' << y << '\n';
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T = 1;  // cin >> T;
    while (T--) solve();
}
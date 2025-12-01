#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// GEOMETRY TEMPLATE - COMPLETE & DEBUGGED
// =========================================================================

// Constantes e Precisão
const double INF = 1e18;
const double PI  = acos(-1.0);
const double EPS = 1e-9;

// Função de sinal: 1 se positivo, -1 se negativo, 0 se zero (dentro do EPS)
inline int sgn(double x) {
    return (x < -EPS) ? -1 : (x > EPS);
}

// =========================================================================
// 1. ESTRUTURA BÁSICA (PONTO / VETOR)
// =========================================================================
struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    // Operações Aritméticas
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
    Point operator/(double k) const { return Point(x / k, y / k); }

    // Comparadores (Necessário para ordenação e Convex Hull)
    // Prioriza X menor, depois Y menor
    bool operator<(const Point& p) const {
        if (sgn(x - p.x) != 0) return x < p.x;
        return sgn(y - p.y) < 0;
    }
    bool operator==(const Point& p) const {
        return sgn(x - p.x) == 0 && sgn(y - p.y) == 0;
    }

    // Magnitude e Normalização
    double norm2() const { return x*x + y*y; } // Norma ao quadrado
    double norm() const { return sqrt(norm2()); } // Norma real (hipotenusa)
    Point unit() const { return *this / norm(); } // Vetor unitário

    // Rotação (Anti-horário)
    Point rotate(double rad) const {
        return Point(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad));
    }
    Point perp() const { return Point(-y, x); } // Rotaciona 90 graus

    // Auxiliares de IO
    void read() { cin >> x >> y; }
};

// =========================================================================
// 2. PRODUTOS VETORIAIS (CORE)
// =========================================================================

// Dot Product (Escalar): Ângulos e Projeções
double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }

// Cross Product (Vetorial): Área e Orientação (Z-axis)
double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
double cross(Point o, Point a, Point b) { return cross(a - o, b - o); }

// Distância Euclidiana
double dist(Point a, Point b) { return (a - b).norm(); }

// Orientação de A->B->C
// > 0: Esquerda (Anti-horário) | < 0: Direita (Horário) | 0: Colinear
int orientation(Point a, Point b, Point c) { return sgn(cross(a, b, c)); }

// =========================================================================
// 3. LINHAS E SEGMENTOS
// =========================================================================

// Verifica se P está no SEGMENTO AB (inclusive pontas)
bool onSegment(Point p, Point a, Point b) {
    return sgn(cross(a, b, p)) == 0 && sgn(dot(p - a, p - b)) <= 0;
}

// Projeção do ponto P na RETA definida por AB
Point projectPointLine(Point p, Point a, Point b) {
    double r = dot(b - a, b - a);
    if (sgn(r) == 0) return a;
    return a + (b - a) * (dot(p - a, b - a) / r);
}

// Distância de P ao SEGMENTO AB
double distPointSegment(Point p, Point a, Point b) {
    if (a == b) return dist(p, a);
    Point v = b - a, w = p - a;
    double c1 = dot(w, v);
    if (c1 <= 0) return dist(p, a); // Antes de A
    double c2 = dot(v, v);
    if (c2 <= c1) return dist(p, b); // Depois de B
    return dist(p, projectPointLine(p, a, b)); // No meio
}

// Intersecção de RETAS (Reta AB e Reta CD)
// Retorna false se paralelas. Preenche 'res' com o ponto.
bool intersectLineLine(Point a, Point b, Point c, Point d, Point &res) {
    double det = cross(b - a, d - c);
    if (sgn(det) == 0) return false; // Paralelas
    double t = cross(c - a, d - c) / det;
    res = a + (b - a) * t;
    return true;
}

// Intersecção de SEGMENTOS (AB e CD)
bool intersectSegSeg(Point a, Point b, Point c, Point d) {
    int d1 = orientation(c, d, a);
    int d2 = orientation(c, d, b);
    int d3 = orientation(a, b, c);
    int d4 = orientation(a, b, d);

    // Cruzamento "Geral" (Stricto)
    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) return true;

    // Casos Especiais (Colineares e tocando nas pontas)
    if (onSegment(a, c, d)) return true;
    if (onSegment(b, c, d)) return true;
    if (onSegment(c, a, b)) return true;
    if (onSegment(d, a, b)) return true;
    return false;
}

// =========================================================================
// 4. POLÍGONOS E ALGORITMOS AVANÇADOS
// =========================================================================

// Área (Shoelace): Retorna área com sinal (+ CCW, - CW)
double polygonArea(const vector<Point>& p) {
    double area = 0.0;
    for (int i = 0; i < (int)p.size(); i++) 
        area += cross(p[i], p[(i + 1) % p.size()]);
    return area / 2.0;
}

// Ponto dentro do Polígono (Winding Number)
// 0: Fora, 1: Dentro, 2: Borda
int pointInPolygon(Point p, const vector<Point>& poly) {
    int wn = 0;
    for (int i = 0; i < (int)poly.size(); i++) {
        Point p1 = poly[i], p2 = poly[(i + 1) % poly.size()];
        if (onSegment(p, p1, p2)) return 2;
        if (p1.y <= p.y) {
            if (p2.y > p.y && cross(p2 - p1, p - p1) > 0) wn++;
        } else {
            if (p2.y <= p.y && cross(p2 - p1, p - p1) < 0) wn--;
        }
    }
    return wn != 0;
}

// CONVEX HULL (Monotone Chain)
// Retorna os pontos do fecho convexo em ordem Anti-Horária (CCW)
// Remove pontos colineares (use < -EPS na checagem para manter colineares)
vector<Point> convexHull(vector<Point> pts) {
    int n = pts.size(), k = 0;
    if (n <= 2) return pts;
    vector<Point> h(2 * n);
    sort(pts.begin(), pts.end());

    // Build Lower Hull
    for (int i = 0; i < n; ++i) {
        // Mude >= 0 para > 0 se quiser manter pontos colineares na borda
        while (k >= 2 && cross(h[k - 2], h[k - 1], pts[i]) <= 0) k--;
        h[k++] = pts[i];
    }
    // Build Upper Hull
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross(h[k - 2], h[k - 1], pts[i]) <= 0) k--;
        h[k++] = pts[i];
    }
    h.resize(k - 1); // Remove o ponto duplicado do final (que é o inicial)
    return h;
}

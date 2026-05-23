ll cross(const point& a, const point& b) {
    return (ll)a.x * b.y - (ll)a.y * b.x;
};

// Ordenação radial (ccw)
bool cmp(const Point& a, const Point& b) {
    // ah = 0 se estiver na metade superior do plano, 1 se estiver na inferior
    int ah = (a.y < 0 || (a.y == 0 && a.x < 0)) ? 1 : 0;
    int bh = (b.y < 0 || (b.y == 0 && b.x < 0)) ? 1 : 0;
    
    if (ah != bh) return ah < bh;
    
    // Se estiverem na mesma metade, usamos o produto vetorial
    return cross(a, b) > 0;
}

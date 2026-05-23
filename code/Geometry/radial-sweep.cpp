ll cross(const point& a, const point& b) {
    return (ll)a.x * b.y - (ll)a.y * b.x;
};

// Retorna 0 para a metade superior (incluindo o eixo X positivo)
// Retorna 1 para a metade inferior (incluindo o eixo X negativo)
int half(const Point& p) {
    if (p.y < 0 || (p.y == 0 && p.x < 0)) return 1;
    return 0;
}

// Ordenação radial (ccw)
bool cmp(const Point& a, const Point& b) {
    int ha = half(a);
    int hb = half(b);
    
    // Se estão em metades diferentes, a superior vem primeiro
    if (ha != hb) {
        return ha < hb;
    }
    // Se estão na mesma metade, ordenamos pelo produto vetorial
    return cross(a, b) > 0;
}

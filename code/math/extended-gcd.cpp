/*
    Algoritmo Estendido de Euclides (Extended GCD)
    
    Complexidade: O(log(min(a, b)))

    Calcula os coeficientes x e y da equacao diofantina:
        ax + by = gcd(a, b)
    
    Para resolver a equacao ax + by = c, onde c eh um valor dado:
    - Primeiro, eh necessario que c % gcd(a, b) == 0.
    - Se sim, as solucões sao:
        x *= c / gcd(a, b)
        y *= c / gcd(a, b)
    - Solucao geral eh
        x(t) = x0 + (b/gcd(a,b)) * t
        y(t) = y0 - (a/gcd(a,b)) * t
    
*/
using ll = long long;
struct mdc { ll x, y, d; };
mdc euclides_ext(ll a, ll b) {
    if (b == 0) return {1, 0, a};
    mdc p = euclides_ext(b, a % b);
    return {p.y, p.x - a / b * p.y, p.d};
}

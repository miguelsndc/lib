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

int extendedGCD(int a, int b, int &x, int &y){
    if(!b){
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extendedGCD(b, a%b, x1, y1);
    x = y1;
    y = x1 - y1*(a/b);
    return d;
}


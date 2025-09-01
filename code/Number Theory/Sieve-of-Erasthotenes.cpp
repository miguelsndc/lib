/*
Sieve of Erasthotenes
    Consulta rapida de numeros primos
    Complexidade: O(nlog(log(n)))
    Calcula o maior divisor primo de cada numero
*/

bool prime[LIM];
int big_prime[LIM];
void sieve() {
    memset(prime, 1, sizeof prime);
    prime[0] = prime[1] = false;
    for (int i = 2; i < LIM; i++) {
        if (prime[i]) {
            big_prime[i] = i;
            for (int j = i * 2; j < LIM; j += i)
                prime[j] = false, big_prime[j] = i;
        }
    }
}

// Retorna os divisores de `n` O(sqrt(n)) 
vector<int> divisores(int n)
{
    vector<int> d;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            d.push_back(i);
            if (i != n / i) d.push_back(n / i);
        }
    }
    d.push_back(n);
    return d;
}

// Fatoracao prima de `n` com sieve O(log(n))
vector<int> sieve_factorization(int n) {
    vector<int> primes;
    while (n > 1) {
        primes.push_back(big_prime[n]);
        n /= big_prime[n];
    }
    return primes;
}

// Fatoracao prima em O(sqrt(n))
vector<pair<int, int>> prime_factorization(int n) {
    vector<pair<int, int>> primes;
    for (int i = 2; i * i <= n; i++) {
        int cnt = 0;
        while (n % i == 0)
            n /= i, cnt++;
        if (cnt > 0)
            primes.push_back({i, cnt});
    }
    if (n > 1)
        primes.push_back({n, 1});
    return primes;
}

// Soma dos divisores de todos os numero de 1 ateh LIM - 1
ll sumDivisors[LIM];
void sum_div()
{
    for (int i = 1; i < LIM; i++) {
        for (int j = i; j < LIM; j += i) {
            sumDivisors[j] += i;
        }
    }
}

// Numero dos divisores de todos os numero de 1 ateh LIM - 1
ll numDivisors[LIM];
void num_div()
{
    for (int i = 1; i < LIM; i++) {
        for (int j = i; j < LIM; j += i) {
            numDivisors[j]++;
        }
    }
}

#include <bits/stdc++.h>
using namespace std;

#define szo(x) (int)(x).size()

/*
===========================================================================
  [SUFIX ARRAY & LCP] - CHEAT SHEET PARA MÚLTIPLAS STRINGS
===========================================================================
  
  * QUANDO USAR:
    - Encontrar a maior substring comum (LCS).
    - Contar substrings distintas.
    - Achar a substring repetida mais longa.
    - DICA: Se for LCS de apenas 2 strings, NÃO use Two Pointers. Basta 
      iterar o LCP procurando o maior valor entre sufixos adjacentes 
      que pertencem a strings diferentes.

  * COMO FAZER LCS DE K STRINGS (K > 2):
    1. Concatenação Segura: Junte todas as strings usando delimitadores 
       ÚNICOS e não imprimíveis (Ex: s1 + char(1) + s2 + char(2)...). 
       Nunca repita o delimitador para evitar matches fantasmas.
    2. Construa o Suffix Array desta string concatenada.
    3. Construa os vetores de mapeamento (orig_id e sa_id).
    4. Two Pointers + MinQueue: Deslize uma janela [L, R] sobre o array 
       ordenado (usando sa_id) até ter pelo menos um sufixo de cada string.
       O menor valor do LCP dentro dessa janela (obtido em O(1) com MinQueue)
       será um candidato à resposta.
    
  * O VETOR 'orig_id' (ESPAÇO DA STRING FÍSICA):
    - O que é: orig_id[i] responde "O caractere que está na posição 'i' 
      da string gigante concatenada pertence a qual string? (0, 1, 2...)"
    - Como construir: Preencha linearmente um `vector<int> orig_id(n)` 
      enquanto monta a string gigante. Defina os delimitadores como -1.
      
  * O VETOR 'sa_id' (ESPAÇO DO SUFFIX ARRAY ORDENADO):
    - O que é: sa_id[i] responde "O sufixo que caiu na posição 'i' do 
      Suffix Array (depois de ordenado alfabeticamente) veio de qual string?"
    - Como usar: É aqui que o seu Two Pointers vai iterar!
    - A Fórmula de Ouro de Transição:
      sa_id[i] = orig_id[sa[i]] 
===========================================================================
*/

struct SuffixArray {
    vector<int> sa, lcp;
    SuffixArray(string& s, int lim = 256) {  // or basic string<int>
        int n = szo(s) + 1, k = 0, a, b;
        vector<int> x(s.begin(), s.end()), y(n), ws(max(n, lim));
        x.push_back(0), sa = lcp = y, iota(sa.begin(), sa.end(), 0);
        for (int j = 0, p = 0; p < n; j = max(1ll, j * 2), lim = p) {
            p = j, iota(y.begin(), y.end(), n - j);
            for (int i = 0; i < n; i++)
                if (sa[i] >= j) y[p++] = sa[i] - j;
            fill(ws.begin(), ws.end(), 0);
            for (int i = 0; i < n; i++) ws[x[i]]++;
            for (int i = 1; i < lim; i++) ws[i] += ws[i - 1];
            for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            for (int i = 1; i < n; i++)
                a = sa[i - 1], b = sa[i],
                x[b] = (y[a] == y[b] and y[a + j] == y[b + j]) ? p - 1 : p++;
        }
        for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
            for (k and k--, j = sa[x[i] - 1]; s[i + k] == s[j + k]; k++);
    }
};

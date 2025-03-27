/*
    Manacher's algorithm
    Acha o raio do maior palindromo centralizado em i pra cada i
    so acha palindromo impar
    se for pra achar par tb bota um caracter entre cada:
    b$a$a$b
    b$a$a$b
    1124211 
*/
vector<int> manacher(string &S){
  vector<int> R(S.size());
  int i = 0, j = 0;
  while (i < S.size()) {
    while (i-j >= 0 && i+j < S.size() && S[i-j] == S[i+j]) ++j;
    R[i] = j;
    int k = 1;
    while (i-k >= 0 && k+R[i-k] < j) R[i+k] = R[i-k], ++k;
    i += k; j -= k;
  }
  return R;
}
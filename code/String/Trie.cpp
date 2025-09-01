const int ALPHA = 26; // tamanho do alfabeto
/*
    Trie - arvore de Prefixos
    maxn - Soma do tamanho de todas as strings
*/
int trie[maxn][ALPHA], word_end[maxn], z = 1;

// Add(P) - O(|P|)
void add(string &s) {
    int cur = 0;
    for(int i = 0; i < s.size(); i++) {
        if (trie[cur][s[i] - 'a'] == -1) {
            memset(trie[z], -1, sizeof trie[z]);
            trie[cur][s[i] - 'a'] = z++;
        }
        cur = trie[cur][s[i] - 'a'];
    }
    word_end[cur]++;
}

// Query(P) - O(|P|)
int query(string &s){
	int cur = 0;
	for(int i = 0; i < s.size(); i++){
		if(trie[cur][s[i] - 'a'] == -1) return 0;
		cur = trie[cur][s[i] - 'a'];
	}
	return word_end[cur];
}

// Sempre inicializar antes
void init(){
	memset(trie[0], -1, sizeof trie[0]);
    memset(word_end, 0, sizeof word_end);
	z = 1;
}
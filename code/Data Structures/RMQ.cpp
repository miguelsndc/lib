/*
Sparse Table RMQ Range Min/Max Query

Build O(n log n)
Query O(1)
*/

const int MAXN = 1e5 + 5;
const int MAXLG = 31 - __builtin_clz(MAXN) + 1;

int value[MAXN], table[MAXLG][MAXN];

void build(int N){
	for(int i=0; i<N; i++) table[0][i] = value[i];

	for(int p=1; p < MAXLG; p++)
		for(int i=0; i + (1 << p) <= N; i++)
			table[p][i] = min(table[p-1][i], table[p-1][i+(1 << (p-1))]); // ou max
}

int query(int l, int r){
	int p = 31 - __builtin_clz(r - l + 1);	//floor log
	return min(table[p][l], table[p][ r - (1<<p) + 1 ]);
}
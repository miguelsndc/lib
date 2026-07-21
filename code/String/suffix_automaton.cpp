struct suffix_automaton {
	struct node {
		int len, link;
		array<int, 26> nxt;
		node(int _len): len(_len) {
			link = -1; nxt.fill(-1);
		}
	};
	vector<node> st;
	int last;
	suffix_automaton(int n = 1) {
		st.reserve(2 * n);
		st.emplace_back(0);
		last = 0;
	}
	void extend(char c) {
		int curr = (int)st.size();
		st.emplace_back(st[last].len + 1);
		int p = last;
		while(p != -1 and st[p].nxt[c - 'a'] == -1) {
			st[p].nxt[c - 'a'] = curr;
			p = st[p].link;
		}
		if (p == -1) {
			st[curr].link = 0;
		} else {
			int q = st[p].nxt[c - 'a'];
			if (st[q].len == st[p].len + 1) {
				st[curr].link = q;
			} else {
				int clone = (int)st.size();
				st.push_back(st[q]);
				st[clone].len = st[p].len + 1;
				while(p != -1 and st[p].nxt[c - 'a'] == q) {
					st[p].nxt[c - 'a'] = clone;
					p = st[p].link;
				}
				st[q].link = clone;
				st[curr].link = clone;
			}
		}
		last = curr;
	}
};

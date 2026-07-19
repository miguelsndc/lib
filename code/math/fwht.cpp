vector<int> FWHT(char ch, vector<int> a, const bool inv = false) {
	for (int n = szo(a), step = 1; step < n; step *= 2) {
		for (int i = 0; i < n; i += 2 * step) {
			for (int j = i; j < i + step; j++ ) {
				auto &u = a[j], &v = a[j + step];
				if (ch == '^') tie(u, v) = pii(u + v, u - v);
				if (ch == '&') tie(u, v) = inv ? pii(v - u, u): pii(v, u + v);
				if (ch == '|') tie(u, v) = inv ? pii(v, u - v): pii(u + v, u);
			}
		}
	}
	if (ch == '^' and inv) for (int &x: a) x /= szo(a);
	return a;
}
vector<int> conv(char ch, vector<int> a, vector<int> b) {
	auto A = FWHT(ch, a, 0);
	auto B = FWHT(ch, b, 0);
	for (int i = 0; i < szo(A); i++) A[i] *= B[i];
	return FWHT(ch, A, 1);
}

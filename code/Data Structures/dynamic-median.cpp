template <typename T>
struct FastDynamicMedian {
    std::priority_queue<T> L, L_del; 
    std::priority_queue<T, std::vector<T>, std::greater<T>> R, R_del; 
    
    int size_L = 0, size_R = 0; 
    T sum_L = 0, sum_R = 0;   

    void clean() {
        while (!L.empty() && !L_del.empty() && L.top() == L_del.top()) { L.pop(); L_del.pop(); }
        while (!R.empty() && !R_del.empty() && R.top() == R_del.top()) { R.pop(); R_del.pop(); }
    }

    void rebalance() {
        if (size_L > size_R + 1) {
            T val = L.top();
            R.push(val); L.pop();
            sum_L -= val; sum_R += val;
            size_L--; size_R++;
            clean();
        } else if (size_R > size_L) {
            T val = R.top();
            L.push(val); R.pop();
            sum_R -= val; sum_L += val;
            size_R--; size_L++;
            clean();
        }
    }

    void insert(T x) {
        if (size_L == 0 || x <= L.top()) {
            L.push(x); size_L++; sum_L += x;
        } else {
            R.push(x); size_R++; sum_R += x;
        }
        rebalance();
    }

    void erase(T x) {
        if (size_L > 0 && x <= L.top()) {
            L_del.push(x); size_L--; sum_L -= x;
        } else {
            R_del.push(x); size_R--; sum_R -= x;
        }
        clean(); 
        rebalance();
    }

    T median() { 
        return L.top(); 
    }
    T equalization_cost() {
        if (size() == 0) return 0;
        T med = median();
        return (size_L * med - sum_L) + (sum_R - size_R * med);
    }

    int size() const { return size_L + size_R; }
    bool empty() const { return size_L == 0 && size_R == 0; }
};
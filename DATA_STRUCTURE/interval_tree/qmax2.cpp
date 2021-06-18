// https://oj.vnoi.info/problem/qmax2
#include <iostream>
#include <vector>

using namespace std;
const int NEGATIVE_INFINITY = -1;

template <typename T>
class IntervalTree {
private:
    vector<T> data, lazy; 
    const T& (*fn) (const T& , const T&);
    void lazy_update(int, int, int);
public:
    IntervalTree(int, const T& (*) (const T&, const T&));
    void add(int, int, int, int, int, T);
    T get_fn(int, int, int, int, int); 
};

template <typename T>
class Solution {
private:
    int n, m;
    IntervalTree<T> *tree;
public:
    void solve();
};

int main() {
    ios_base::sync_with_stdio(false);
    Solution<int> sol;
    sol.solve();
    return 0;
}

template <typename T>
IntervalTree<T>::IntervalTree(int tree_size, const T& (*compare) (const T&, const T&)) {
    fn = compare;
    data.resize(tree_size * 4, 0);
    lazy.resize(tree_size * 4, 0);
}

template <typename T>
void IntervalTree<T>::lazy_update(int node, int l, int r) {
    data[node] += lazy[node];
    if (l < r) {
        lazy[node << 1] += lazy[node];
        lazy[node << 1 | 1] += lazy[node];
    }
    lazy[node] = 0;
}

template <typename T>
void IntervalTree<T>::add(int node, int l, int r, int x, int y, T k) {
    lazy_update(node, l, r); 
    if (y < l || r < x) return;
    if (x <= l && r <= y) {
        data[node] += k;
        if (l < r) {
            lazy[node << 1] += k;
            lazy[node << 1 | 1] += k;
        }
        return ;
    }
    int m = (l + r) >> 1;
    add(node << 1, l, m, x, y, k);
    add(node << 1 | 1, m + 1, r, x, y, k);
    data[node] = fn(data[node << 1], data[node << 1 | 1]);
}

template <typename T>
T IntervalTree<T>::get_fn(int node, int l, int r, int x, int y) {
    lazy_update(node, l, r);
    if (y < l || r < x) return NEGATIVE_INFINITY;
    if (x <= l && r <= y) {
        return data[node];
    }
    int m = (l + r) >> 1;
    return fn(
        get_fn(node << 1, l, m, x, y),
        get_fn(node << 1 | 1, m + 1, r, x, y)
    );
}

template <typename T>
void Solution<T>::solve() {
    cin >> n >> m;
    tree = new IntervalTree<int>(n, max<int>);
    for (int _ = 0, query, x, y; _ < m; ++ _) {
        cin >> query >> x >> y;
        if (query == 0) {
            int k;
            cin >> k;
            tree->add(1, 1, n, x, y, k);
        } else if (query == 1) {
            cout << tree->get_fn(1, 1, n, x, y) << endl; 
        }
    }
}

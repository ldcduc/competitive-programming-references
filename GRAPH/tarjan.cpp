// Tested with: https://vn.spoj.com/problems/TJALG/
// num[] initialized to be all 0
void dfs(int u) {
    stack_.push(u); 
    num[u] = low[u] = ++counter;
    for (auto v : adj[u]) {
        if (num[v]) {
            minimize(low[u], num[v]);
        } else {
            dfs(v);
            minimize(low[u], low[v]);
        }
    }
    if (num[u] == low[u]) {
        ++connected_component_counter; 
        int v;
        do {
            v = stack_.top();
            stack_.pop();
            num[v] = low[v] = 1e9; // +inf;
        } while (v != u);
    }
}

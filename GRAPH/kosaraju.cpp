// Tested with: https://vn.spoj.com/problems/TJALG/
// visited[] initialized to be all 0

void dfs(int u, int time_) {
    ++visited[u];
    // adj[0][u] contains original arcs (start from u) 
    // adj[1][u] contains inverse arcs (go into u)
    for (auto v : adj[time_ - 1][u]) {
        if (visited[v] < time_) {
            dfs(v, time_);
        }
    }
    if (time_ == 1) {
        stack_.push(u);
    }
}

void solve() {
    for (int i=1; i<=n; ++i) {
        if (!visited[i]) {
            dfs(i, 1);
        }
    }
    while (!stack_.empty()) {
        int u = stack_.top();
        stack_.pop();
        if (visited[u] < 2) {
            ++connected_component_counter;
            dfs(u, 2);
        }
    }
    cout << connected_component_counter <<  endl;
}

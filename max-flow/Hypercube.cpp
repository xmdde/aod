#include "Hypercube.h"
#include <queue>
#include <algorithm>

int Hypercube::EdmondsKarp(int s, int t) {
    std::vector<Edge*> pred(v, nullptr);
    int flow = 0;
    do {
        std::queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (Edge* e : adj[cur]) {
                if (pred[e->t] == nullptr && e->t != s && e->capacity > e->flow) {
                    pred[e->t] = e;
                    q.push(e->t);
                }
            }
        }

        if (pred[t] != nullptr) {
            int df = INT_MAX;
            for (auto e = pred[t]; e != nullptr; e = pred[e->s]) {
                df = std::min(df, e->capacity - e->flow);
            }
            for (auto e = pred[t]; e != nullptr; e = pred[e->s]) {
                e->flow += df;
                e->rev->flow -= df; //? czy inaczej init
            }
            flow += df;
        }
        else break;
    } while (pred[t] == nullptr);
    return flow;
}

int Hypercube::maxFlow(int s, int t, int& paths) {
    int ans = 0;
    int a;
    do {
        a = EdmondsKarp(s, t);
        ans += a;
        paths++;
    } while (a != 0);
    return ans;
}

void Hypercube::printFlow() {
    for (auto i : adj) {
        for (auto edge : i) {
            std::cout << edge->s << " -> " << edge->t << " : " << edge->flow << "\n";
        }
    }
}
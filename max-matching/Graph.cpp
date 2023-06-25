#include "Graph.h"
#include <set>
#include <random>
#include <queue>
#include <iostream>

void Graph::addNeighbors(const int node) {
    int d = 0;
    std::set<int> tmp;
    srand(time(nullptr));
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, pow(2, k)); //0...2^k - 1
    int shift = pow(2,k);
    while (d < this->i) {
        int nbh = floor(dist(mt)) + shift;
        if (!tmp.contains(nbh)) {
            Edge* e1 = new Edge(node, nbh);
            Edge* e2 = new Edge(nbh, node);
            e1->rev = e2;
            e2->rev = e1;
            adj[node].push_back(e1);
            adj[nbh].push_back(e2);
            tmp.insert(nbh);
            d++;
        }
    }
}

void Graph::linkSourceSink() {
    for (int cur = 0; cur < pow(2, k); cur++) { //link source (v-2) to all nodes in V1
        Edge* e1 = new Edge(cur, v-2);
        Edge* e2 = new Edge(v-2, cur);
        e1->rev = e2;
        e2->rev = e1;
        adj[cur].push_back(e1);
        adj[v-2].push_back(e2);
    }
    for (int cur = pow(2,k); cur < pow(2, k+1); cur++) { //link sink (v-1) to all nodes in V2
        Edge* e1 = new Edge(cur, v-1);
        Edge* e2 = new Edge(v-1, cur);
        e1->rev = e2;
        e2->rev = e1;
        adj[cur].push_back(e1);
        adj[v-1].push_back(e2);
    }
}

int Graph::EdmondsKarp(int s, int t) {
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

int Graph::maxMatching(int& paths) {
    int ans = 0;
    int a;
    do {
        a = EdmondsKarp(v-2, v-1);
        ans += a;
        paths++;
    } while (a != 0);
    return ans;
}

void Graph::printMatching() {
    for (int cur = 0; cur < pow(2,k); cur++) {
        for (auto edge : adj[cur]) {
            if (edge->flow == 1)
                std::cout << cur << " - " << edge->t << "\n";
        }
    }
}
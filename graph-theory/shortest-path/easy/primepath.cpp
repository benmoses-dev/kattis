#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool isPrime(int x) {
    if (x < 2)
        return false;
    int squirt = sqrt(x);
    for (int i = 2; i <= squirt; i++) {
        if (x % i == 0)
            return false;
    }
    return true;
}

bool differsByOne(int a, int b) {
    int differences = 0;
    for (int i = 0; i < 4; i++) {
        int da = a % 10;
        int db = b % 10;
        if (da != db)
            differences++;
        a /= 10;
        b /= 10;
    }
    if (differences == 1)
        return true;
    return false;
}

vector<int> undirectedBfs(vector<vector<int>> &adj, int start) {
    int n = adj.size();

    // Track state
    vector<int> parent(n, -1);
    vector<int> colours(n, -1);
    vector<int> distances(n, -1);
    int i = start;

    queue<int> q;
    q.push(i);
    colours[i] = 0;
    distances[i] = 0;

    while (!q.empty()) {
        int next = q.front();
        q.pop();

        /**
         * Start a BFS through all neighbours.
         * If we get back to a node that has already been visited, we have a cycle.
         */
        for (const int &neighbour : adj[next]) {
            if (colours[neighbour] == -1) {
                colours[neighbour] = colours[next] ^ 1;
                distances[neighbour] = distances[next] + 1;
                parent[neighbour] = next;
                q.push(neighbour);
            }
        }
    }

    return distances;
}

int getPrimeIndex(vector<int> &primes, int prime) {
    int start = 0;
    int end = primes.size() - 1;
    while (start <= end) {
        int pivot = start + (end - start) / 2;
        int i = primes[pivot];
        if (i == prime)
            return pivot;
        if (prime > i) {
            start = pivot + 1;
        } else {
            end = pivot - 1;
        }
    }
    return -1;
}

int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    int C;
    cin >> C;

    vector<int> primes;
    for (int i = 1000; i < 10000; i++) {
        if (isPrime(i))
            primes.push_back(i);
    }

    vector<vector<int>> adj(primes.size());
    for (int i = 0; i < primes.size(); i++) {
        int pa = primes[i];
        for (int j = i + 1; j < primes.size(); j++) {
            int pb = primes[j];
            if (differsByOne(pa, pb)) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    for (int c = 0; c < C; c++) {
        int a, b;
        cin >> a >> b;
        if (a == b) {
            cout << 0 << endl;
            continue;
        }
        int ia = getPrimeIndex(primes, a);
        int ib = getPrimeIndex(primes, b);
        vector<int> distances = undirectedBfs(adj, ia);
        int distance = distances[ib];
        if (distance == -1) {
            cout << "Impossible" << endl;
            continue;
        }
        cout << distance << endl;
    }

    return 0;
}

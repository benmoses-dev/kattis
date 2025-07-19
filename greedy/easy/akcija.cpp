#include <iostream>
#include <queue>

using namespace std;

/**
 * We will group them together with the greater prices in the same group.
 * This will maximise the value of the third book in each group.
 */
int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;

    // Sort by price in descending order
    priority_queue<int> pq;
    for (int n = 0; n < N; n++) {
        int c;
        cin >> c;
        pq.push(c);
    }

    // Calculate the total price excluding every third book
    int total = 0;
    int book = 0;
    while (!pq.empty()) {
        book++;
        int price = pq.top();
        pq.pop();
        if (book % 3 == 0) { // Every third book is free
            continue;
        }
        total += price;
    }
    cout << total << endl;
    return 0;
}

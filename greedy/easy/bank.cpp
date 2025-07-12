#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, T;
    cin >> n >> T;
    vector<pair<int, int>> customers(n);
    vector<bool> greedySchedule(T, false);
    
    // Process the queue into a list of customers
    for (int i = 0; i < n; i++) {
        int cash, patience;
        cin >> cash >> patience;
        customers[i].first = cash; customers[i].second = patience;
    }
    
    // Sort the customers by cash (highest value first)
    sort(customers.begin(), customers.end(), [](pair<int, int>& a, pair<int, int>& b) {
        return a.first > b.first;
    });
    
    int total = 0;
    for (int i = 0; i < n; i++) {
        pair<int, int>& customer = customers[i];
        // Get the next most valuable customer and assign them as late as possible in the schedule
        for (int pos = customer.second; pos >= 0; pos--) {
            if (greedySchedule[pos] == false) {
                greedySchedule[pos] = true;
                total += customer.first;
                break;
            }
        }
    }
    
    cout << total << "\n";
    return 0;
}

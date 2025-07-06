#include <cstdio>
#include <vector>
#include <set>
using namespace std;
int main() {
    while (true) {
        int n, m;
        scanf("%d %d", &n, &m);
        if (n == 0 && m == 0) {
            break;
        }
        set<int> jack;
        vector<int> results;
        for (int i = 0; i < n; i++) {
            // Process Jack's CDs
            int num;
            scanf("%d", &num);
            jack.insert(num);
        }
        for (int i = 0; i < m; i++) {
            // Process Jill's CDs
            int numJill;
            scanf("%d", &numJill);
            if (jack.contains(numJill)) {
                results.push_back(numJill);
            }
        }
        printf("%d", results.size());
        printf("\n");
    }
}

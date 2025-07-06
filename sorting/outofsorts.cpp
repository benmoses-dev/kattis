#include <cstdio>
#include <set>
#include <vector>

using namespace std;

long n, m, a, c, start;

long getVal(long last) {
    long result = ((a * last) + c) % m;
    return result;
}

int main() {
    scanf("%d %d %d %d %d", &n, &m, &a, &c, &start);
    
    // Build list of numbers
    vector<long> nums;
    long first = getVal(start);
    nums.push_back(first);
    for (long i = 1; i < n; i++) {
        nums.push_back(getVal(nums[i - 1]));
    }
    
    // For each number, check whether it can be found
    long count = 0;
    for (long j = 0; j < nums.size(); j++) {
        long test = nums[j];
        long low = 0;
        long high = nums.size() - 1;
        long mid = (high + low) / 2;
        while (high >= low) {
            long pivot = nums[mid];
            if (pivot == test) {
                count++;
                break;
            }
            if (test < pivot) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
            mid = (high + low) / 2;
        }
    }
    printf("%d\n", count);
}

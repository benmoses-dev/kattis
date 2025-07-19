#include <vector>

using namespace std;

int binarySearch(vector<int> &nums, int num) {
    int start = 0;
    int end = nums.size() - 1;
    while (start <= end) {
        int pivot = start + (end - start) / 2;
        int i = nums[pivot];
        if (i == num)
            return pivot;
        if (num > i) {
            start = pivot + 1;
        } else {
            end = pivot - 1;
        }
    }
    return -1;
}

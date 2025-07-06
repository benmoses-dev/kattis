#include <deque>
#include <cstdio>
#include <cstring>

using namespace std;

class MyTeque {
    private:
    deque<long> left;
    deque<long> right;
    
    public:
    void push_back(long x) {
        right.push_back(x);
        if (right.size() > left.size()) {
            long y = right.front();
            right.pop_front();
            left.push_back(y);
        }
    }
    void push_front(long x) {
        left.push_front(x);
        if (left.size() > right.size() + 1) {
            long y = left.back();
            left.pop_back();
            right.push_front(y);
        }
    }
    void push_middle(long x) {
        if (left.size() > right.size()) {
            right.push_front(x);
        } else {
            left.push_back(x);
        }
    }
    long get(long index) {
        if (index >= left.size()) {
            index = index - left.size();
            return right.at(index);
        } else {
            return left.at(index);
        }
    }
};

int main() {
    MyTeque teque;
    long n;
    scanf("%ld", &n);
    for (long i = 0; i < n; i++) {
        char s[20];
        long x;
        scanf("%s %ld", s, &x);
        if (strcmp(s, "push_back") == 0) {
            teque.push_back(x);
        } else if (strcmp(s, "push_front") == 0) {
            teque.push_front(x);
        } else if (strcmp(s, "push_middle") == 0) {
            teque.push_middle(x);
        } else if (strcmp(s, "get") == 0) {
            long y = teque.get(x);
            printf("%ld", y);
            printf("\n");
        }
    }
    return 0;
}

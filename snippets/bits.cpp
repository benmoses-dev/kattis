using ui = unsigned int;

constexpr bool isPowerOfTwo(int x) { return x > 0 && (x & (x - 1)) == 0; }

constexpr int countSetBits(int x) {
    int count = 0;
    while (x) {
        x &= (x - 1);
        count++;
    }
    return count;
}

constexpr ui lowestBit(ui x) { return x & (-x); }

constexpr bool bitIsSet(int x, int k) { return (x & (1 << k)) != 0; }

constexpr int clearLowestBit(int x) { return x & (x - 1); }

constexpr int flipBits(int x) { return ~x; }

constexpr int toggleBit(int x, int k) { return x ^ (1 << k); }

constexpr int setBit(int x, int k) { return x | (1 << k); }

constexpr int clearBit(int x, int k) { return x & ~(1 << k); }

constexpr int halveNTimes(int x, int n) { return x >> n; }

constexpr int doubleNTimes(int x, int n) { return x << n; }

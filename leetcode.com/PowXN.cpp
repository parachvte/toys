class Solution {
public:
    double myPow(double x, int n) {
        long long N = n;
        if (abs(x) < 1e-8) return 0.0;
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }
        double res = 1;
        double mul = x;
        while (N) {
            if (N & 1) res *= mul;
            mul *= mul;
            N >>= 1;
        }
        return res;
    }
};
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>

//constants

// Q3
#define Q3_MAX_SCORE    1000000
// Q4
#define Q4_MAX_ITEMS    1000
#define Q4_MAX_CAP      100000

using namespace std;
extern "C" int ans1(int d, int ip, int rp) {
    return 0;
}

int x3[Q3_MAX_SCORE + 10];
extern "C" int ans3(int* s, int sl, int* y, int yl) {
    sort(s, s + sl);
    int nl = unique(s, s+sl) - s, bs = 0, bc = -1;
    vector<int> rs(yl);
    for(int i=0;i<yl;i++) {
        int r = (lower_bound(s, s + nl, y[i]) - s);
        int rk = nl - r + (s[r] != y[i]);
        x3[rk]++;
        if (x3[rk] > bs) {
            bs = x3[rk];
            bc = rk;
        } else if (x3[rk] == bs) {
            bc = max(bc, rk);
        }
    }
    return bc;
}

int dp4[Q4_MAX_ITEMS + 10][Q4_MAX_CAP + 10];
extern "C" int ans4(int* v, int *c, int len, int cap) {
    for (int i=1;i<=len;i++) {
        for (int j=0;j<=cap;j++) {
            if (j < c[i]) dp4[i][j] = dp4[i-1][j];
            else dp4[i][j] = max(dp4[i-1][j], dp4[i-1][j-c[i]] + v[i]);
        }
    }
    return dp4[len][cap];
}

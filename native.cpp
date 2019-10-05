#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>

using namespace std;
typedef pair<int, int> ii;

//constants

// Q3
#define Q3_MAX_SCORE    1000000
// Q4
#define Q4_MAX_ITEMS    1000
#define Q4_MAX_CAP      100000
// Q5
#define Q5_MAX_N        1000000

extern "C" int ans1(int d, int ip, int rp) {
    return 0;
}

int x3[Q3_MAX_SCORE + 10];
extern "C" int ans3(int* s, int sl, int* y, int yl) {
    sort(s, s + sl);
    int nl = unique(s, s+sl) - s, bs = 0, bc = -1;
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
        int cc = c[i-1], cv = v[i-1];
        for(int j=0;j<=cap;j++) {
            if (j < cc) dp4[i][j] = dp4[i-1][j];
            else dp4[i][j] = max(dp4[i-1][j-cc] + cv, dp4[i-1][j]);
        }
    }
    return dp4[len][cap];
}

ii d5[Q5_MAX_N + 10];
bool cmp(ii a, ii b) {
    return a.first < b.first;
}
extern "C" int ans5(int* d) {
    int n = d[0];
    for(int i=0;i<n;i++) {
        int ix = (i + 1) * 2;
        d5[i].second = d[ix];
        d5[i].first = d[ix - 1];
    }
    sort(d5, d5 + n, cmp);
    vector<ii> f;
    f.push_back(d5[0]);
    for(int i=1;i<n;i++){
        int bm = 1<<30, bj = -1;
        for (int j=0;j<f.size();j++){
            int td = d5[i].first - f[j].first, vd = abs(d5[i].second - f[j].second);
            if (td >= vd && vd < bm) {
                bj = j;
            }
        }
        //printf("%d, %d -> %d, %d\n", f[bj].first, f[bj].second, d5[i].first, d5[i].second);
        if (bj == -1) f.push_back(d5[i]);
        else f[bj] = d5[i];
    }
    return f.size();
}
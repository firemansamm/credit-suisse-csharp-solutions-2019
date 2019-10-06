#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>

using namespace std;
typedef pair<int, int> ii;

//constants
// Q2
#define Q2_MAX_LENGTH   10000
// Q3
#define Q3_MAX_SCORE    1000000
// Q4
#define Q4_MAX_ITEMS    1000
#define Q4_MAX_CAP      100000
// Q5
#define Q5_MAX_N        1000000

//#define DEBUG
#ifdef DEBUG
    #define TEST printf("native compiled %s %s\n", __DATE__, __TIME__)
#else 
    #define TEST
#endif

extern "C" int ans1(int d, int ip, int rp) {
    TEST;
    return 0;
}

ii sd2[Q2_MAX_LENGTH + 10];
bool cmp2(ii a, ii b) {
    if (a.first == b.first) return a.second > b.second;
    else return a.first < b.first;
}
extern "C" int ans2(int* t, int tl, int* r, int* b, int len) {
    TEST;
    for (int i=0;i<len;i++){
        sd2[i] = ii(r[i], b[i]);
    }
    sort(sd2, sd2 + len, cmp2);
    for(int i=1;i<len;i++) {
        sd2[i].second = max(sd2[i].second, sd2[i-1].second);
    }
    int ans = 0;
    for(int i=0;i<tl;i++) {
        int idx = upper_bound(sd2, sd2 + len, ii(t[i], 0), cmp2) - sd2 - 1;
        ans += sd2[idx].second;
    }
    return ans;
}

int x3[Q3_MAX_SCORE + 10];
extern "C" int ans3(int* s, int sl, int* y, int yl) {
    TEST;
    sort(s, s + sl);
    int nl = unique(s, s+sl) - s, bs = 0, bc = nl + 1;
    memset(x3, 0, sizeof x3);
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
    TEST;
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
    TEST;
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
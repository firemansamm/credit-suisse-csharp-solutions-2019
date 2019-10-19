#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <bitset>

using namespace std;
typedef pair<int, int> ii;

//constants
// Q2
#define Q2_MAX_LENGTH   150
// Q3
// Q4
#define Q4_MAX_ITEMS    250
#define Q4_MAX_CAP      10000
// Q5
#define Q5_MAX_N        150

//#define DEBUG
#ifdef DEBUG
    #define TEST printf("native compiled %s %s\n", __DATE__, __TIME__)
#else 
    #define TEST
#endif

extern "C" int ans1(double d, double ip, double rp) {
    TEST;
    double r = d * rp / 100.0;
    double p = d / 10.0;
    double sf = r * 100.0 / ip;
    double ii = (ip / 100.0) + 1.0;
    double lh = log(ii);
    double rh = log((r - sf) / (d - sf));
    double pm = ceil(rh / lh);
    double rem = pow(ii, pm) * (d - sf) + sf;
    return round((r * pm) + p + rem);
}

/*ii sd2[Q2_MAX_LENGTH + 10];
bool cmp2(ii a, ii b) {
    if (a.first == b.first) return a.second > b.second;
    else return a.first < b.first;
}*/
unsigned char sd2[Q2_MAX_LENGTH];
extern "C" int ans2(int* t, int tl, int* r, int* b, int len) {
    TEST;
    memset(sd2, 0, sizeof sd2);
    for (int i=0;i<len;i++){
	    if (b[i] > sd2[r[i]]) sd2[r[i]] = b[i];
    }
    sort(r, r + len);
    sort(t, t + tl);
    int dx = 0,
        ans = 0;
    unsigned char cm = 0;
    for (int i=0;i<tl;i++){
        while (dx < len && r[dx] <= t[i]) {
            cm = max(sd2[r[dx]], cm);
            dx++;
        }
        ans += cm;
    }
    return ans;
}

extern "C" int ans3(int* s, int sl, int* y, int yl) {
    TEST;
    sort(s, s + sl);
    sort(y, y + yl);
    int nl = unique(s, s+sl) - s,
        bp = -1,
        bc = 0,
        p = nl + 1,
        c = 0,
        ix = 0;
    for(int i=0;i<yl;i++) {
        //printf("ix = %d\n", ix);
        while (ix < nl && y[i] >= s[ix]) {
            if (c > 0) {
                //printf("comparing %d (%d), %d (%d)\n", bc, bp, c, p);
                if (c > bc) {
                    bc = c;
                    bp = p;
                } else if (c == bc) {
                    bp = max(bp, p);
                }
            }
            c = 0;
            p--;
            ix++;
        }
        c++;
        //printf("%d -> %d = %d\n", y[i], p, c);
    }
     if (c > 0) {
        if (c > bc) {
            bc = c;
            bp = p;
        } else if (c == bc) {
            bp = max(bp, p);
        }
    }
    return bp;
}

int dp4[Q4_MAX_ITEMS][Q4_MAX_CAP];
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

ii d5[Q5_MAX_N];
bool v5[Q5_MAX_N];
short p5[Q5_MAX_N];
bool Aug(int x, int n) {
    if (v5[x]) return 0;
    v5[x] = 1;
    for (int i=x+1;i<n;i++) {
        if (d5[i].first - d5[x].first < abs(d5[i].second - d5[x].second)) continue;
        if (p5[i] == -1 || Aug(p5[i], n)) {
            p5[i] = x;
            return 1;
        }
    }
    return 0;
}
extern "C" int ans5(int* d) {
    TEST;
    memset(p5, -1, sizeof p5);
    int n = d[0];
    //d5 = (ii*)(d + 1);
    for(int i=0,k=1;i<n;i++) {
        d5[i].first = d[k];
        d5[i].second = d[k + 1];
        k += 2;
    }
    sort(d5, d5 + n);
    int matchings = 0;
    for (int i = n - 1; i >= 0; i--) {
        memset(v5, 0, sizeof v5);
        matchings += Aug(i, n);
    }
    return n - matchings;
}

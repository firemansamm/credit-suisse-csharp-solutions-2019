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
#define Q2_MAX_LENGTH   100
// Q3
// Q4
#define Q4_MAX_ITEMS    250
#define Q4_MAX_CAP      10000
// Q5
#define Q5_MAX_N        1050

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
extern "C" int ans2(int* t, int* r, int* b, int len) {
    TEST;
    memset(sd2, 0, sizeof sd2);
    for (int i=0;i<len;i++){
	    if (b[i] > sd2[r[i]]) sd2[r[i]] = b[i];
    }
    sort(r, r + len);
    sort(t, t + len);
    int dx = 0,
        ans = 0;
    unsigned char cm = 0;
    for (int i=0;i<len;i++){
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

/*struct ii5 {
    int first, second;
    bool operator<(const ii5& other) {
        // lexographical like std::pair
        return (first == other.first && second < other.second) || first < other.first;
    }
};*/

ii d5[Q5_MAX_N];
int n5;
int v5[Q5_MAX_N];
int v5s[Q5_MAX_N];
int p5[Q5_MAX_N];
bool Aug(int x) {
    for (int i=x+1;i<n5;i++){
        if (v5[i]) continue;
        if (d5[i].first - d5[x].first < abs(d5[i].second - d5[x].second)) continue;
        v5[i] = 1;
        if (p5[i] < 0 || Aug(p5[i])) {
            p5[i] = x;
            return 1;
        }
    }
    return 0;
}
extern "C" int ans5(int* d) {
    TEST;
    memset(p5, -1, sizeof p5);
    memset(v5s, 0, sizeof v5s);
    n5 = d[0];
#pragma GCC ivdep
    for(int i=0;i<n5;i++) {
        d5[i].first = d[(i * 2) + 1];
        d5[i].second = d[(i + 1) * 2];
    }
    //d5 = (ii5*)(d + 1);
    sort(d5, d5 + n5);
    int matchings = 0;
    for (int x=0;x<n5;x++){
        for (int i=x+1;i<n5;i++){
            if (d5[i].first - d5[x].first < abs(d5[i].second - d5[x].second)) continue;
            if (p5[i] < 0) {
                p5[i] = x;
                matchings++;
                v5s[x] = 1;
                break;
            }
        }
    }
    for (int i = n5 - 1; i >= 0; i--) {
        if (v5s[i]) continue;
        matchings += Aug(i);
        memset(v5, 0, sizeof v5);
    }
    return n5 - matchings;
}

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
#define Q3_MAX_SCORE    1000000
// Q4
#define Q4_MAX_ITEMS    500
#define Q4_MAX_CAP      10000
// Q5
#define Q5_MAX_N        100

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
int sd2[Q2_MAX_LENGTH + 10];
extern "C" int ans2(int* t, int tl, int* r, int* b, int len) {
    TEST;
    memset(sd2, 0, sizeof sd2);
    for (int i=0;i<len;i++){
	    sd2[r[i]] = max(sd2[r[i]], b[i]);
    }
    sort(r, r + len);
    sort(t, t + tl);
    int nl = unique(r, r + len) - r;
    int dx = 0;
    int ans = 0;
    int cm = sd2[r[0]];
    for (int i=0;i<tl;i++){
        while (r[dx] < t[i] && dx < nl - 1) {
            cm = max(sd2[r[dx]], cm);
            dx++;
        }
        ans += cm;
    }
    return ans;
}

/*extern "C" int ans3(int* s, int sl, int* y, int yl) {
    TEST;
    sort(s, s + sl);
    sort(y, y + yl);
    int nl = unique(s, s+sl) - s,
        bg = -1,
        bc = 0,
        g = nl + 1,
        c = 0,
        ix = 0,
        lp = -1,
        le = s[0];
    for(int i=0;i<yl;i++) {
        if (y[i] == lp || y[i] < le) {
            c++;
            continue;
        }
        while(le <= y[i]) {
            if (c > 0) {
                if (c > bc) {
                    bg = g;
                    bc = c;
                } else if (c == bc) {
                    bg = max(bg, g);
                }
            }
            ix++;
            g--;
            c = 0;
            if (ix < nl) le = s[ix];
            else le = 1<<30;
        }
        lp = y[i];
    }
    if (c > bc) {
        bg = g;
        bc = c;
    } else if (c == bc) {
        bg = max(bg, g);
    }
    return bg;
}*/

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
    f.push_back(d5[n-1]);
    for(int i=n-2;i>=0;i--){
        int bm = 1<<30, bj = -1;
        for (int j=0;j<f.size();j++){
            int td = f[j].first - d5[i].first, vd = abs(d5[i].second - f[j].second);
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

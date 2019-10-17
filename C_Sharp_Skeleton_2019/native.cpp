#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <bitset>
#include <queue>
#include <future>

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
    int dx = 0,
        ans = 0,
        cm = 0;
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
struct state5{
    vector<ii> fs;
    int ldx;
    state5(ii init, int _ldx) : ldx(_ldx) {
        fs.push_back(init);
    }
    state5(int _ldx) : ldx(_ldx) {}
};
extern "C" int ans5(int* d) {
    TEST;
    int n = d[0];
    for(int i=0;i<n;i++) {
        int ix = (i + 1) * 2;
        d5[i].second = d[ix];
        d5[i].first = d[ix - 1];
    }
    sort(d5, d5 + n);
    /*int nl = unique(d5, d5 + n) - d5; // only unique ones matter
    if (nl < 15) {
        queue<state5> f;
        f.emplace(d5[nl-1], nl-1);
        int ans = 1<<30, cp = 0;
        // n^2 bfs, n ~ 80-100
        while (!f.empty()) {
            state5 s = f.front();
            f.pop();
            //printf("got state @ %d, size = %d\n", s.ldx, s.fs.size());
            if (s.ldx == 0) {
                ans = min(ans, (int)s.fs.size());
                continue;
            }
            int nx = s.ldx - 1;
            for (int i=0;i<s.fs.size();i++){
                int td = s.fs[i].first - d5[nx].first, fd = abs(s.fs[i].second - d5[nx].second);
                if (td >= fd) {
                    state5 ns(nx);
                    // replace-push
                    ns.fs = s.fs;
                    ns.fs[i] = d5[nx];
                    f.push(ns);
                    cp++;
                }
            }
            // non-replace-push
            state5 ns(nx);
            ns.fs = s.fs;
            ns.fs.push_back(d5[nx]);
            f.push(ns);
            cp++;
        }
        return ans;
    } else {*/
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
    //}
}

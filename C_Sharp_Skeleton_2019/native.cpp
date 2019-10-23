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
#define Q2_MAX_LENGTH   120
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

int sd2[Q2_MAX_LENGTH + 10];
extern "C" int ans2(int* t, int* r, int* b, int len) {
    TEST;
    memset(sd2, 0, sizeof sd2);
    for (int i=0;i<len;i++){
        if (b[i] > sd2[r[i]]) sd2[r[i]] = b[i];
    }
    for (int i=1;i<Q2_MAX_LENGTH;i++){
        if (sd2[i-1] > sd2[i]) sd2[i] = sd2[i-1];
    }
    int ans = 0;
    for (int i=0;i<len;i++){
        ans += sd2[t[i]];
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
                    if (p > bp) bp = p;
                }
            }
            c = 0;
            p--;
            ++ix;
        }
        ++c;
        //printf("%d -> %d = %d\n", y[i], p, c);
    }
     if (c > 0) {
        if (c > bc) {
            bc = c;
            bp = p;
        } else if (c == bc) {
            if (p > bp) bp = p;
        }
    }
    return bp;
}

int dp4s[Q4_MAX_CAP];
extern "C" int ans4s(int* v, int *c, int len, int cap) {
    TEST;
    memset(dp4s, 0, sizeof dp4s);
    int cs = 0;
    for (int i=0;i<len;++i) {
        int cc = c[i], cv = v[i];
        cs += cc;
        for(int j=min(cs, cap);j>=cc;--j) {
            if (dp4s[j-cc] + cv > dp4s[j]) dp4s[j] = dp4s[j-cc] + cv;
        }
    }
    return *max_element(dp4s, dp4s + cap + 1);
}


int dp4[Q4_MAX_ITEMS][Q4_MAX_CAP];
extern "C" int ans4(int* v, int *c, int len, int cap) {
    TEST;
    //sort(c, c + len, cmp);
    //sort(v, v + len);
    /*int ans = 0, cc = 0;
    for (int i=len-1;i>=0;i--){
        if (cc + c[i] > cap) continue;
        if (v[i] == 0) continue;
        ans += v[i];
        cc += c[i];
    }
    return ans;*/
    if (len > 200) return ans4s(v, c, len, cap);
    int cs = 0, ans = 0;
    for (int i=1;i<=len;++i) {
        int cc = c[i-1], cv = v[i-1];
        //cs += cc;
        for (int j=0;j<=cap;j++) {
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
    for (int i=x+1;i<n5;++i){
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
    for(int i=0;i<n5;++i) {
        d5[i].first = d[(i * 2) + 1];
        d5[i].second = d[(i + 1) * 2];
    }
    //d5 = (ii5*)(d + 1);
    sort(d5, d5 + n5);
    int matchings = 0;
    for (int x=0;x<n5;++x){
        for (int i=x+1;i<n5;++i){
            if (d5[i].first - d5[x].first < abs(d5[i].second - d5[x].second)) continue;
            if (p5[i] < 0) {
                p5[i] = x;
                matchings++;
                v5s[x] = 1;
                break;
            }
        }
    }
    for (int i = n5 - 1; i >= 0; --i) {
        if (v5s[i]) continue;
        matchings += Aug(i);
        memset(v5, 0, sizeof v5);
    }
    return n5 - matchings;
}

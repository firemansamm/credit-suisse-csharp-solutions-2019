#include <algorithm>
#include <cstring>
#include <vector>

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

#define fabs(x) ((x ^ (x >> 31)) - (x >> 31))

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
bool cmp(ii a, ii b) {
    return a.first < b.first;
}
extern "C" int ans5(int* d) {
    TEST;
    /*int n = d[0];
    for(int i=0, k = 1;i<n;i++) {
        d5[i].second = d[k];
        d5[i].first = d[k + 1];
        k += 2;
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
    return f.size();*/
    return 0;
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

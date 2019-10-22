#include <algorithm>
#include <cstring>

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

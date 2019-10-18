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
#define Q5_MAX_N        100

//#define DEBUG
#ifdef DEBUG
    #define TEST printf("native compiled %s %s\n", __DATE__, __TIME__)
#else 
    #define TEST
#endif

int sd2[Q2_MAX_LENGTH];
extern "C" int ans2(int* t, int tl, int* r, int* b, int len) {
    TEST;
    memset(sd2, 0, sizeof sd2);
    for (int i=0;i<len;i++){
	    sd2[r[i]] = max(sd2[r[i]], b[i]);
    }
    /*for (int i=0;i<len;i++){
        sd2[i].first = r[i];
        sd2[i].second = b[i];
    }
    sort(sd2, sd2 + len, cmp2);*/
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

#include <algorithm>

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

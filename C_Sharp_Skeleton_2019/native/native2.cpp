#include <cstring>
//constants
// Q2
#define Q2_MAX_LENGTH   120
// Q3
// Q4
#define Q4_MAX_ITEMS    250
#define Q4_MAX_CAP      10000
// Q5
#define Q5_MAX_N        1050

#define LOWER_MASK ((1 << 16) - 1)
#define UPPER_MASK (((1 << 30) - 1) ^ LOWER_MASK)

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

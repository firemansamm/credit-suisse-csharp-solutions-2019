#include <cstdio>
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
    //printf("sanity check: %x / %x\n", UPPER_MASK, LOWER_MASK);
    for (int i=0;i<len;i++){
        sd2[i] = (r[i] << 16) | b[i];
        //printf("%d, %d\n", sd2[i] >> 16, sd2[i] & LOWER_MASK);
    }
    sort(sd2, sd2 + len);
    int cm = sd2[0] & LOWER_MASK;
    for (int i=1;i<len;i++){
        if (cm > (sd2[i] & LOWER_MASK)) sd2[i] = (sd2[i] & UPPER_MASK) | cm;
        cm = sd2[i] & LOWER_MASK;
    }
    int ans = 0;
    for(int i=0;i<len;i++) {
        int idx = lower_bound(sd2, sd2 + len, (t[i] + 1) << 16) - sd2 - 1;
        ans += sd2[idx] & LOWER_MASK;
    }
    return ans;
}

/*int main(){
    int t[] = {6, 7, 2, 8, 1, 2}, r[] = {5, 4, 3, 1, 8, 1}, b[] = {9, 9, 1, 9, 4, 8};
    printf("%d\n", ans2(t, r, b, 6));
}*/
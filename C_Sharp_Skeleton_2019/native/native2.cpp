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

int sd2[Q2_MAX_LENGTH];
extern "C" int ans2(int* t, int* r, int* b, int len) {
    TEST;
    memset(sd2, 0, sizeof sd2);
    for (int i=0;i<len;++i){
	    if (b[i] > sd2[r[i]]) sd2[r[i]] = b[i];
    }
    sort(r, r + len);
    sort(t, t + len);
    int dx = 0,
        ans = 0,
        cm = 0;
    for (int i=0;i<len;++i){
        while (dx < len && r[dx] <= t[i]) {
            if (sd2[r[dx]] > cm) cm = sd2[r[dx]];
            ++dx;
        }
        ans += cm;
    }
    return ans;
}

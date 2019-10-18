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

int dp4[Q4_MAX_ITEMS][Q4_MAX_CAP];
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

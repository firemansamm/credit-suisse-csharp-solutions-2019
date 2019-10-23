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
int rs4[Q4_MAX_ITEMS], id[Q4_MAX_ITEMS];
int* tmp;
bool cmp(int a, int b) {
    return tmp[a] > tmp[b];
}
extern "C" int ans4(int* v, int *c, int len, int cap) {
    TEST;
    return 0;
    //sort(c, c + len, cmp);
    //sort(v, v + len);
    int ans = 0, cc = 0;
    for (int i=len-1;i>=0;i--){
        if (cc + c[i] > cap) continue;
        if (v[i] == 0) continue;
        ans += v[i];
        cc += c[i];
    }
    return ans;
    /*if (len > 200) return ans4s(v, c, len, cap);
    int cs = 0, ans = 0;
    for (int i=1;i<=len;++i) {
        int cc = c[i-1], cv = v[i-1];
        //cs += cc;
        for (int j=0;j<=cap;j++) {
            if (j < cc) dp4[i][j] = dp4[i-1][j];
            else dp4[i][j] = max(dp4[i-1][j-cc] + cv, dp4[i-1][j]);
        }
    }
    return dp4[len][cap];*/
}

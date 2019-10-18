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

ii d5[Q5_MAX_N];
/*struct state5{
    vector<ii> fs;
    int ldx;
    state5(ii init, int _ldx) : ldx(_ldx) {
        fs.push_back(init);
    }
    state5(int _ldx) : ldx(_ldx) {}
};*/
//bool v5[Q5_MAX_N + 10];
extern "C" int ans5(int* d) {
    TEST;
    //memset(v5, 0, sizeof v5);
    int n = d[0];
    for(int i=0,k=1;i<n;i++) {
        d5[i].first = d[k];
        d5[i].second = d[k + 1];
        k += 2;
    }
    sort(d5, d5 + n);
    //int vx = n;
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
        //if (bj != -1) printf("%d, %d -> %d, %d\n", f[bj].first, f[bj].second, d5[i].first, d5[i].second);
        //else printf("** %d, %d\n", d5[i].first, d5[i].second);
        if (bj == -1) f.push_back(d5[i]);
        else f[bj] = d5[i];
    }
    return f.size();
}

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

extern "C" int ans1(double d, double ip, double rp) {
    TEST;
    double r = d * rp / 100.0;
    double p = d / 10.0;
    double sf = r * 100.0 / ip;
    double ii = (ip / 100.0) + 1.0;
    double lh = log(ii);
    double rh = log((r - sf) / (d - sf));
    double pm = ceil(rh / lh);
    double rem = pow(ii, pm) * (d - sf) + sf;
    return round((r * pm) + p + rem);
}

/*ii sd2[Q2_MAX_LENGTH + 10];
bool cmp2(ii a, ii b) {
    if (a.first == b.first) return a.second > b.second;
    else return a.first < b.first;
}*/
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
                    bp = max(bp, p);
                }
            }
            c = 0;
            p--;
            ix++;
        }
        c++;
        //printf("%d -> %d = %d\n", y[i], p, c);
    }
     if (c > 0) {
        if (c > bc) {
            bc = c;
            bp = p;
        } else if (c == bc) {
            bp = max(bp, p);
        }
    }
    return bp;
}

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

struct AugPath {
    int A, B;   //size of left, right groups
    vector<vector<int> > G; //size A
    vector<bool> visited;   //size A
    vector<int> P;          //size B
    
    AugPath(int _A, int _B): A(_A), B(_B), G(_A), P(_B, -1) {}
    
    void AddEdge(int a, int b) {    //a from left, b from right
        G[a].push_back(b);
    }
    bool Aug(int x) {
        if (visited[x]) return 0;
        visited[x] = 1;
        /* Greedy heuristic */
        for (auto it:G[x]) {
            if (P[it] == -1) {
                P[it] = x;
                return 1;
            }
        }
        for (auto it:G[x]) {
            if (Aug(P[it])) {
                P[it] = x;
                return 1;
            }
        }
        return 0;
    }
    int MCBM() {
        int matchings = 0;
        for (int i = 0; i < A; ++i) {
            visited.resize(A, 0);
            matchings += Aug(i);
            visited.clear();
        }
        return matchings;
    }
    vector<pair<int, int> > GetMatchings() {
        vector<pair<int, int> > matchings;
        for (int i = 0; i < B; ++i) {
            if (P[i] != -1) matchings.emplace_back(P[i], i);
        }
        return matchings;
    }
};

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
int s5[Q5_MAX_N];
int k5[Q5_MAX_N];
extern "C" int ans5(int* d) {
    TEST;
    //memset(v5, 0, sizeof v5);
    memset(k5, 0, sizeof k5);
    int n = d[0];
    for(int i=0,k=1;i<n;i++) {
        d5[i].first = d[k];
        d5[i].second = d[k + 1];
        k += 2;
    }
    sort(d5, d5 + n);
    int vs = n, ans = 0;
    for (int i=0;i<n;i++){
        int cv = 0;
        for (int j=0;j<i;j++){
            if (d5[i].first - d5[j].first >= abs(d5[i].second - d5[j].second)) {
                cv = max(cv, s5[j]);
            }
        }
        s5[i] = cv + 1;
        k5[s5[i]]++;
        ans = max(ans, k5[s5[i]]);
        //printf("%d = %d\n", i, cv + 1);
    }
    return ans;
}

int main() {
    int d[] = {8, 3, 4, 8, 11, 3, 6, 7, 6, 8, 11, 8, 5, 6, 9, 5, 11};
    printf("%d\n", ans5(d));
}
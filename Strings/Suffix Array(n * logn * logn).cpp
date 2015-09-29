#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <utility>
#include <vector>
#include <assert.h>
using namespace std;
/*
All the suffixes of the given string are identified according to the position of first letter in the given string
i.e in string "abcde" suffix "bcde" is identified with 1

suffix array gives the list of suffixes sorted lexographically
Complexity : O(N (log N) * (log N))

LCP function is used to get the longest common prefix of two suffixes.
Complexity O(log N)

*/
#define MAXL 100005
#define MAXLG 17    // smallest power of 2 greater than MAXL
char* S; int N, stp;
pair < pair<int, int> , int > L[MAXL];  // auxilary array which stores the suffixes in sorted order
int P[MAXLG][MAXL], sa[MAXL], lcp[MAXL];
// Array P stores the rank of i'th suffix at kth step;
// N = total length of the string
// sa = sorted array of suffix i.e sa[i] stores the index of the suffix at rank i;
// lcp = stores the longest common prefix between sa[i] and sa[i - 1];
//N = strlen(S);
void contruct() {
    int cnt;
    for(int i = 0; i < N; i++) P[0][i] = S[i];
    for(stp = 1, cnt = 1; cnt < N; stp++, cnt <<= 1) {
        for(int i = 0; i < N; i++) L[i] = make_pair(make_pair(P[stp - 1][i], ((i + cnt) < N )? P[stp - 1][i + cnt] : -1), i);
        sort(L, L + N);
        P[stp][L[0].second] = 0;
        for(int i = 1; i < N; i++) P[stp][L[i].second] = ((L[i].first == L[i - 1].first) ? (P[stp][L[i - 1].second]): i);
    }
    for(int i = 0; i < N; i++) sa[i] = L[i].second;
}
int LCP(int x, int y) {     // return the length of longest common prefix of two suffix that starts with x and y
    int k, ans = 0;
    if(x == y) return N - x;
    for(k = stp - 1; k >= 0 && x < N && y < N; k--)
        if(P[k][x] == P[k][y]) x += (1LL << k), y += (1LL << k), ans += (1LL << k);
    return ans;
}
void getSuffixArray(char* p, int len) {
    S = p; N = len;
    //assert(0);  // N = strlen(S);
    contruct();
}
char str[MAXL];
void solve() {
    int N;
    scanf("%d", &N);
    scanf("%s", str);
    printf("%s\n", str);
    getSuffixArray(str, N);
    for(int i = 0; i < N; i++) cout << sa[i] << " "; cout << endl;
    cout << LCP(0, 1) << endl;
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) solve();
}


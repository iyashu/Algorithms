#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
#define MAXN 100005
char* S; int N;
int Z[MAXN];  // stores the length of longest common prefix with original string(0'th suffix) and i'th suffix.
void _Z() {
    int L = 0, R = 0;
    Z[0] = N;
    for(int i = 1; i < N; i++) {
        if(i > R) {
            L = R = i;
            while((R < N) && S[R - L] == S[R]) R++;
            Z[i] = R - L; R--;
        }
        else {
            int p = i - L;
            if(Z[p] != (R - i + 1)) Z[i] = min(Z[p], R - i + 1);
            else {
                L = i; ++R;
                while(S[R - i] == S[R]) ++R;
                Z[i] = R - L; --R;
            }
        }
    }
    for(int i = 0; i < N; i++) printf("%d ", Z[i]); printf("\n");
}
char str[MAXN];
void get(char* str, int n) {
    S = str; N = n;
    _Z();
}
void solve() {
    scanf("%s", str);
    int N = strlen(str);
    get(str, N);
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) solve();
}

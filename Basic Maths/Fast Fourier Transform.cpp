#include <stdio.h>
#include <math.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <complex>
using namespace std;
/*
typedef complex<long double> base;
#define re real()
#define im imag()
*/
struct base {
    typedef long double T;
    T re, im;
    base(): re(0), im(0) {}
    base(T re) : re(re), im(0) {}
    base(T re, T im) : re(re), im(im) {}
    base operator+ (const base& to) const { return base(re + to.re, im + to.im); }
    base operator- (const base& to) const { return base(re - to.re, im - to.im); }
    base operator* (const base& to) const { return base((re * to.re) - (im * to.im), (re * to.im) + (im * to.re)); }
    base& operator/= (const T N) { re /= N, im /= N; return *this; }
    base conj() const { return base(re, -im);}
};
struct FFT {
    typedef long double T;
    vector<base> A, B;  // taking two vector for multiplying them without calculating revtab for each of them
    vector<int> revtab;
    int logn;
    void getLogn(int N) {
        logn = 0;
        while((1LL << logn) < N) logn++;
    }
    void init(int N) {  // N denotes the size of polynomial of which we need to find the fourier transform
        getLogn(N);
        int NN = (1LL << logn);
        build_revtab(NN);
    }
    void build_revtab(int NN) {
        revtab.resize(NN);
        for(int i = 0; i < NN; i++) {
            int k = 0;
            for(int j = 0; j < logn; j++) k |= (((i >> j) & 1) << (logn - 1 - j));
            revtab[i] = k;
        }
    }
    void getDFT(vector<int> &coeff, int flag = 1) {
        DFT(coeff, A, 1, flag);
    }
    void getIDFT(vector<base> &coeff, int flag = 1) {
        DFT(coeff, A, -1, flag);
    }
    void DFT(vector<base> &coeff, vector<base> &ans,int invert = 1, int flag = 1) {
        int N = coeff.size();
        getLogn(N);
        int NN = 1LL << logn;
        if(flag) build_revtab(NN);
        ans.resize(NN);
        for(int i = 0; i < N; i++) ans[i] = coeff[i];
        fourierTrans(ans, invert);
    }
    void DFT(vector<long double> &coeff, vector<base> &ans,int invert = 1, int flag = 1) {
        int N = coeff.size();
        getLogn(N);
        int NN = 1LL << logn;
        if(flag) build_revtab(NN);
        ans.resize(NN);
        for(int i = 0; i < N; i++) ans[i] = base(coeff[i]);
        fourierTrans(ans, invert);
    }
    void DFT(vector<int> &coeff, vector<base> &ans,int invert = 1, int flag = 1) {
        int N = coeff.size();
        getLogn(N);
        int NN = 1LL << logn;
        if(flag) build_revtab(NN);
        ans.resize(NN);
        for(int i = 0; i < N; i++) ans[i] = base((long double)coeff[i]);
        fourierTrans(ans, invert);
    }

    void fourierTrans(vector<base> &to, int invert = 1) {
        assert((invert == 1) || (invert == -1));
        int N = to.size();
        getLogn(N);
        for(int i = 0; i < N; i++) if( i > revtab[i]) swap(to[i], to[revtab[i]]);

        vector<base> omegan(N);
        long double angle = 2 * (M_PI) / N;angle = angle * invert;
        base omega(cos(angle), sin(angle));
        omegan[0] = base(1, 0);
        for(int i = 1; i < N; i++) omegan[i] = omegan[i - 1] * omega;

        for(int len = 2, shift = N >> 1LL; len <= N; len <<= 1LL, shift >>= 1LL) {
            int half = len >> 1LL;
            for(int i = 0; i < N; i += len) {
                for(int j = 0; j < half; j++) {
                    base temp = to[i + j + half] * omegan[j * shift];
                    to[i + j + half] = to[i + j] - temp;
                    to[i + j] = to[i + j] + temp;
                }
            }
        }
        if(invert <= 0) for(int i = 0; i < N; i++) to[i].re /= N, to[i].im /= N;
    }
    void multiply(vector<long long>& coeff1, vector<long long>& coeff2, vector<long long>& ans) {
        int n = coeff1.size();
        int m = coeff2.size();
        int maxi = max(n,m);
        getLogn(maxi);
        logn++;int NN = 1LL << logn;
        ans.resize(NN);A.resize(NN);B.resize(NN);
        for(int i = 0; i < n; i++) A[i].re = coeff1[i];
        for(int i = 0; i < m; i++) B[i].re = coeff2[i];

        build_revtab(NN);
        fourierTrans(A, 1);fourierTrans(B, 1);
        for(int i = 0; i < NN; i++) A[i] = A[i] * B[i];
        fourierTrans(A, -1);
        for(int i = 0; i < NN; i++) ans[i] = (long long)(A[i].re + 0.5);
    }

};
#define MAXN 300005
char S[MAXN];
void solve() {
    int N;
    scanf("%s", S);
    N = strlen(S);
    vector<long long> A(N);
    for(int i = N - 1; i >= 0; i--) A[N - 1 - i] = S[i] - '0';
    scanf("%s", S);
    N = strlen(S);
    vector<long long> B(N);
    for(int i = N - 1; i >= 0; i--) B[N - 1 - i] = S[i] - '0';
    vector<long long> ans;
    FFT fft;
    fft.multiply(A, B, ans);
    N = ans.size();
    for(int i = 1; i < N; i++) ans[i] += (ans[i - 1]/10);
    for(int i = 0; i < N; i++) ans[i] %= 10;
    int j;for(j = N - 1; j > 0 && ans[j] == 0; j--);
    for(int i = j; i >= 0; i--)printf("%d",ans[i]);printf("\n");
}
int main()
{
    int t;
    scanf("%d", &t);
    while(t--) solve();
}

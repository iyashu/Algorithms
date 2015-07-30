#include <stdio.h>
using namespace std;
#define MAXN 1000000
int small[MAXN + 1], primes[MAXN], miu[MAXN + 1], phi[MAXN], total;
void sieve() {
    phi[1] = miu[1] = small[1] = 1;
    for(int i = 2; i <= MAXN; i++) {
        if(!small[i]) {
            small[i] = primes[total++] = i;
            phi[i] = i - 1;
            miu[i] = -1;
        }
        int upto = MAXN / i;
        for(int j = 0; j < total && primes[j] <= upto; j++) {
            small[i * primes[j]] = primes[j];
            if(small[i] == primes[j]) {
                phi[i * primes[j]] = phi[i] * primes[j];
                miu[i * primes[j]] = 0;
                break;
            }
            else phi[i * primes[j]] = phi[i] * (primes[j] - 1), miu[i * primes[j]] = -miu[i];
        }
    }
    for(int i = 0; i <= 20; i++) printf("%d ", primes[i]);printf("\n");
    for(int i = 1; i <= 20; i++) printf("%d ", phi[i]);printf("\n");
    for(int i = 1; i <= 20; i++) printf("%d ,", miu[i]);printf("\n");
}
int main() {
    total = 0;
    sieve();
}

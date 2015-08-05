#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
/*
    Fenwick Tree is also known as Binary Indexed Tree (BIT)
    Similar to RMQ data Structure
    Each index, i, of the Array contains the sum of all the elements from [(i - (i & (-i))) , i )
    So index 4 contains the sum from [0, 3] or [0, 4)
Suggested Reading :
https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/
http://bitdevu.blogspot.in/
*/
class FenwickTree
{
    public:
    typedef long long T;
    vector<T> v;
    void init(int n){ v.assign(n+1,0); }
    void add(int i,T x) {
        int sz = v.size();
        for(++i;i<sz;i+=(i & (-i)))v[i]+=x;
    }
    T sum(int i) const {	//[0, i)
		T r = 0;
		for(;i > 0; i-= (i & (-i))) r += v[i];
		return r;
	}
	T sum(int left, int right) const {	//[left, right)
		return sum(right) - sum(left);
	}
    int findG(int bitMask,T upto)
    {
        // return smallest index i such that sum ([0,i]) = upto
        // bitMask is the largest power of 2 less than sz
        int sz = v.size();
        T store = upto;
        int idx = 0;
        int ans = sz;
        int flag = 0;
        while ((bitMask != 0) && (idx < sz)) {
            int tIdx = idx + bitMask;
            //if(tIdx >= sz){bitMask>>=1;continue;}
        if(upto==v[tIdx]) ans = min(ans,tIdx);
		if (tIdx < sz && upto>v[tIdx]) {
			idx = tIdx;
			upto -= v[tIdx];
		}
		bitMask >>= 1;
	}
	if (sum(ans)!=store) return -1;
	else return (ans-1LL);
    }
    void output()
    {
        int sz = v.size();
        for(int i=0;i<sz;i++)printf("%lld ", v[i]);printf("\n");
    }
};
int main() {
    FenwickTree T;
    int N = 10;
    T.init(10);
    for(int i = 0; i < N; i++) {
        printf("%d ", i);
        T.add(i, i);
    } printf("\nValues stored in each index : \n");
    for(int i = 1; i <= N; i++) {
        printf("%lld ", T.v[i]);
    }
    printf("\nSum in range [4,10) : ");
    printf("%lld\n", T.sum(4, 10));
}

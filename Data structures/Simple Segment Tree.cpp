#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
struct Node
{
    // define the data inside this section
    long long sum;
    Node():sum(0){}
    explicit Node(long long val) {
        sum = val;
    }
    Node &operator += (const Node &to) {
        return *this = *this + to;
    }
    // how to combine the two nodes write here
    Node operator + (const Node &to) const {
        Node res;
        res.sum = sum + to.sum;
        return res;
    }
};
template <class T>
struct GetSegmentTree {
    static T combineNode(const T &x, const T &y) { return x + y; }
    static void combineNodes(T &x, const T &y) { x += y; }
    static T identityNode() { return T(); }

    vector<T> tree;
    int N;
    GetSegmentTree(int n, const T &val = T()):N(n) {
        tree.resize((N),identityNode());
        tree.resize((N << 1LL),val);
        build();
    }
    GetSegmentTree(const vector<T> &A) {
        N = A.size();
        tree.resize((N),identityNode());
        tree.insert(tree.end(), A.begin(), A.end());
        build();
    }
    void build() {
        for (int i = N - 1; i > 0; --i) tree[i] = tree[i<<1] + tree[i<<1|1];// tree[i] = combineNode(tree[i<<1] , tree[i<<1|1]);
    }
    T get(int i) {
        return tree[i+N];
    }
    T getWhole() {
		return queryRange(0,N);
	}
    T queryRange(int l, int r) {     // [l,r)
        T resl, resr;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) resl = resl + tree[l++]; //combineNode(resl, tree[l++]);
            if (r&1) resr = tree[--r] + resr;//combineNode(tree[--r], resr);
        }
        return resl + resr;//combineNode(resl, resr);
    }
    T updatePoint(int p, const Node &val) {
        for (tree[p += N] = val; p >>= 1; ) tree[p] = tree[p<<1] + tree[p<<1|1]; // combine(t[p<<1], t[p<<1|1]);
    }
};

void solve() {
    int N,temp;
    string st;
    scanf("%d",&N);
    vector<Node> A;
    for(int i =0;i<N;i++) scanf("%d",&temp),A.push_back(Node(temp));
    GetSegmentTree<Node> segt(A);
    int Q;
    scanf("%d",&Q);
    while(Q--) {
        cin >> st;
        if(st == "U") {
            int p, val;
            cin >> p >> val;
            segt.updatePoint(p, Node(val));
        }else {
            int l,r;
            cin >> l >> r;
            Node ans = segt.queryRange(--l,r);
            cout << ans.sum << endl;
        }
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        solve();
    }
}

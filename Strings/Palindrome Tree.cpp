#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
#define MAXN 100005
char str[MAXN];
/*
    As in any tree-like data structure in palindromic tree we have nodes.
    Directed edge between nodes u and v marked with some letter - let's say X - means that we can obtain the palindrome of node v by adding letter X to the both sides of the palindrome of node u
    A suffix link from node u goes to such node w, that the palindrome of node w is the largest palindrome which is also a proper suffix of the palindrome of node u
    Every node corresponding to some palindrome-substring of given string

Suggested Readings :
http://adilet.org/blog/25-09-14/

*/
class Node {
public:
    Node() {
        for(int i = 0; i < 26; i++) next[i] = 0;
        times = sufflink = len = 0;
    }
    int next[26];   //correspond to another Node when sandwiched to current Node
    int len;    // denotes the length of palindrome corresponding to Node
    int sufflink;   // denotes the suffix link of Node
    int times;      // denotes the number of times the palindrome occurs in string
    int start;      // denotes the start position of the first occurence of palindrome
    void clean() {
        for(int i = 0; i < 26; i++) next[i] = 0;
        start = times = sufflink = len = 0;
    }
};
class PalinTree {
public:
    int total, suff;    // suff denotes largest suffix palindrome of the processed prefix string
    vector <Node> tree;
    void construct(int N, char* str) {
        init(N);
        for(int i = 0; i < N; i++) add(i, str);
        propagate();
    }
    void init(int N) {
        tree.resize(N + 3);
        total = 2; suff = 2;
        tree[1].sufflink = tree[2].sufflink = 1;
        tree[1].len = -1; tree[2].len = 0;
    }
    // return true if new node is created, i.e new palindrome occurs;
    bool add(int pos, char* str) {
        int curr = suff;
        int letter = str[pos] - 'a';
        while(1) {
            int curlen = tree[curr].len;
            if((pos - curlen - 1) >= 0 && (str[pos] == str[pos - curlen - 1])) break;
            curr = tree[curr].sufflink;
        }
        // curr is the largest suffix palindrome on which on sandwiching id str[pos] results in next suff

        // if it already exits
        if(tree[curr].next[letter]) {
            suff = tree[curr].next[letter];
            tree[suff].times ++;
            // if u wanna to store all the occurrence of this palindrome
            // then create a vector corresponding to this palindrome and push all its pos
            return false;
        }
        suff = ++total;
        tree[total].len = tree[curr].len + 2;
        tree[total].times = 1;
        tree[curr].next[letter] = total;
        if(tree[total].len == 1) {
            tree[total].sufflink = 2;
            tree[total].start = pos;
            return true;
        }
        if(tree[curr].start > 0)tree[total].start = tree[curr].start - 1;
        else tree[total].start = 0;
        while(1) {
            curr = tree[curr].sufflink;
            int curlen = tree[curr].len;
            if((pos - curlen - 1) >= 0 && str[pos] == str[pos - curlen - 1]) break;
        }
        tree[total].sufflink = tree[curr].next[letter];
    }

    void propagate() {
        // propagates value of number of occurrence among the up to tree using suffix links;
        for(int i = total; i > 2; i--) {
            tree[tree[i].sufflink].times += tree[i].times;
        }
    }
};
void solve() {
    PalinTree T;
    int N;
    scanf("%s", str);
    N = strlen(str);
    T.construct(N, str);    // passing only str results in runtime error : http://www.spoj.com/problems/LPS/

    // do some fun here
    for(int i = 3; i <= T.total; i++) {
        printf("%d %d %d \n", T.tree[i].start, T.tree[i].len, T.tree[i].times);
    }
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) solve();
}

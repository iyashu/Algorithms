#include<iostream>
using namespace std;
int pow(long long a, int b, int c){
    long long r = 1;
    
    while(b){
        if(b & 1) r = r * a % c;
        a = a * a % c;
        b >>= 1;
    }
    
    return r;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        cout<<pow(a,b,c)<<endl;
    }
}

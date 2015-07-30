#include<iostream>
using namespace std;
int gcd(int x, int y)
{
	while(y) y^=x^=y^=x%=y;
	return x;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,m;
        cin>>n>>m;
        cout<<gcd(n,m)<<endl;
    }
}


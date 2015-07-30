#include<iostream>
using namespace std;
void comb(int m,int n)
{
    int a[70];
    a[0]=1;
    for(int i=1;i<70;i++)a[i]=0;
    if(n<(m/2))n=m-n;
    for(int j=n+1;j<=m;j++)
        {
            for(int i=0;i<70;i++)
            {
                a[i]=a[i]*j;
                for(;a[i]>=10;i++)
                {
                    a[i+1]=(a[i]/10)+(a[i+1]*j);
                    a[i]=a[i]%10;
                    if(a[i+1]<10)
                    {
                        i=i+1;
                        break;
                    }    
                }
            }
        }
        int count=0;
        for(int i=69;i>=0;i--)
        {
            if(a[i]%10==0) count++;
            else break;
        }
        long long y,r=0;
        for(int j=1;j<=(m-n);j++)
        {
        for(int i=(69-count);i>=0;i--)
        {
        y=(r*10)+a[i];
        r=y%j;
        a[i]=y/j;
        }
        }
        int k=0;
        for(int i=69-count;i>=0;i--)
        {
            if(a[i]%10==0) k++;
            else break;
        }
        for(int i=69-(count+k);i>=0;i--)
        cout<<a[i];
        return;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,k;
        cin>>n>>k;
        comb(n,k);
        cout<<endl;
    }
}

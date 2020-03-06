#include<iostream>
#include<cstdio>
#include<cmath>
#include<map>
#include<algorithm>
#include<cstring>
#include<queue>
#include<stack>
#include<vector>
#define LL long long
using namespace std;
const int maxn=100005;
const int INF=0x3f3f3f3f;
const int mod=998244353;
const double eps=1e-10;
const double Pi=acos(-1.0);
int main()
{
    freopen("cmnist-512.txt","r", stdin);
    freopen("ccmnist-512.txt","w", stdout);
    string ss,s1,s2;
    map<string, int> mp;
    while(cin>>ss) {
        if (ss == "cudaLaunchKernel") {
            cin>>s1;
            cin>>s2;
        } else {
            continue;
        }
        string tt=s1+" "+s2;
        if (mp.find(tt)!= mp.end()) {
            mp[tt]++;
        } else {
            mp[tt]=1;
        }

    }
    map<string, int>::iterator it;
    for (it=mp.begin(); it != mp.end();it++) {
        cout<<it->first<<" "<<it->second<<endl;
    }
    return 0;
}

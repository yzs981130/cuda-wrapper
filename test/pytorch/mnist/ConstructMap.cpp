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
struct Node {
    int count;
    int add;
    LL crc;
    map<LL,int> dis;
}res[40];
int main()
{
    freopen("ccmnist-512.txt","r", stdin);
    //freopen("mnist-ret.txt","w", stdout);
    int cnt=0;
    LL a,b,c;
    LL ans[50];
    while(cin>>dec>>a>>hex>>b>>dec>>c) {
        res[cnt].add=(b&0xFFF);
        res[cnt].crc=a;
        res[cnt].count=c;
        ans[cnt]=b;
        cnt++;
    }
    cnt = 0;
    int colo[32];
    memset(colo,0,sizeof(colo));
    for (int i=0;i<30;i++) {
        if (!colo[i]) {
            cnt++;
            colo[i]=cnt;
        }
        for (int j=0;j<30;j++) {
            if (i==j) {
                continue;
            }
            LL tmp=ans[j]-ans[i];
            if (labs(tmp)<=(1<<16)) { //以4K划分
                res[i].dis[tmp]=j;
                colo[j]=colo[i];
            }
        }
    }
    //打印每个链上的Node
    for (int i=1;i<=cnt;i++) {
        for(int j=0;j<30;j++) {
            if (colo[j]==i) {
                printf("%d ",j);
            }
        }
        printf("\n");
    }
    //打印每个Node信息
    for (int i=0;i<30;i++) {
        printf("%d\n",i);
        printf("CRC:\n");
        printf("%lld\n",res[i].crc);
        printf("0x%x\n",res[i].add);
        map<LL,int>::iterator it;
        for (it = res[i].dis.begin();it !=res[i].dis.end();it++) {
            //cout<<"0x"<<hex<<it->first<<" "<<dec<<it->second<<endl;
            cout<<it->first<<" "<<it->second<<endl;
        }
        printf("\n");
    }
    return 0;
}

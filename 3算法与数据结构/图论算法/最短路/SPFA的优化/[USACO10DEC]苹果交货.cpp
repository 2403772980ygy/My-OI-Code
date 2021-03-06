//http://119.29.55.79/problem/3271
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxm 200000
#define maxn 100000
#define INF 0x3f3f3f3f3f3f3f3f
typedef long long ll;
using namespace std;
int n,m;
struct edge{
	int from;
	int to;
	int next;
	int len;
}E[maxm*2+5];
int head[maxn+5];
int sz=1;
void add_edge(int u,int v,int w){
	sz++;
	E[sz].from=u;
	E[sz].to=v;
	E[sz].len=w;
	E[sz].next=head[u];
	head[u]=sz;
}

ll dist[maxn+5];
bool inq[maxn+5];
void spfa(int s){
	queue<int>q;
	for(int i=1;i<=n;i++){
		dist[i]=INF;
		inq[i]=0;
	}
	dist[s]=0;
	q.push(s);
	inq[s]=1;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		inq[x]=0;
		for(int i=head[x];i;i=E[i].next){
			int y=E[i].to;
			if(dist[y]>dist[x]+E[i].len){
				dist[y]=dist[x]+E[i].len;
				if(!inq[y]){
					q.push(y);
					inq[y]=1;
				}
			}
		}
	}
} 


int main(){
	int s,p1,p2;
	int u,v,w;
	scanf("%d %d %d %d %d",&m,&n,&s,&p1,&p2);
	for(int i=1;i<=m;i++){
		scanf("%d %d %d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	spfa(s);
	ll s_p1=dist[p1];
	ll s_p2=dist[p2];
	spfa(p1);
	ll p1_p2=dist[p2];
	printf("%lld\n",min(s_p1+p1_p2,s_p2+p1_p2));
}

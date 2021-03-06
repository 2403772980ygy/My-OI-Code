#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define maxn 500000
#define maxm 1000000
#define bsz 1000
using namespace std;
inline void qread(int &x){
	x=0;
	int sign=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') sign=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	x=x*sign;
}
inline void qprint(int x){
	if(x<0){
		putchar('-');
		qprint(-x);
	}else if(x==0){
		putchar('0');
		return;
	}else{
		if(x>=10) qprint(x/10);
		putchar(x%10+'0');
	}
}

int n,m,q;
struct edge{
	int from;
	int to;
	int val;
	int id;
}E[maxm+5];

int fa[maxn+5];
int sz[maxn+5];
int find(int x){
//	printf("%d\n",x);
	if(fa[x]==x) return x;
	else return find(fa[x]);
}
void ini(int n){
	for(int i=1;i<=n;i++){
		fa[i]=i;
		sz[i]=1;
	}
}
int bel[maxn+5];
int lastx[maxm+5],lasty[maxm+5];//用于记录并查集之前状态，回滚时用 
void merge(int id){
	int x=E[id].from;
	int y=E[id].to;
	int fx=find(x),fy=find(y);
	if(fx!=fy){
		if(sz[fx]>sz[fy]) swap(fx,fy);
		lastx[id]=fx;
		lasty[id]=fy;
		fa[fx]=fy;
		sz[fy]+=sz[fx];
	} 
}

struct oper{
	int type;
	int x;
	int val;
}in[maxn+5];
struct query{//询问 
	int id;
	int x;
	int val;
	query(){
		
	}
	query(int _id,int _x,int _val){
		id=_id;
		x=_x;
		val=_val;
	}
	friend bool operator < (query p,query q){
		return p.val>q.val;
	}
};
vector<query>Q;
struct update{//需要合并的边 
	int id;
	int val;
	update(){
		
	}
	update(int _id,int _val){
		id=_id;
		val=_val;
	}
	friend bool operator < (update p,update q){
		return p.val>q.val;
	}
};
int ans[maxn+5];
bool vis[maxn+5];//标记哪些边的边权需要修改 
bool tmp[maxn+5];//标记当前块需要修改的边 
vector<update>U1;//不需要修改，但是需要合并的边 
vector<int>U2;//需要修改，需要合并的边 
vector<int>back;//回滚用 
void rebuild(int last){
	for(int i=1;i<=m;i++){
		U1.push_back(update(i,E[i].val));
		lastx[i]=0;
	}
	ini(n);
	sort(U1.begin(),U1.end());
	sort(Q.begin(),Q.end());
	for(int i=0,j=0;i<Q.size();i++){////遍历每个询问 
		back.clear();
		while(j<U1.size()&&U1[j].val>=Q[i].val){//双指针找出可以经过的边 
			if(!vis[U1[j].id]){
				merge(U1[j].id);
				lastx[U1[j].id]=0;//不需要回滚 
			}
			j++;
		}
		for(int p=last;p<Q[i].id;p++){
			if(in[p].type==1) tmp[in[p].x]=1; 
		} 
		for(int p=0;p<U2.size();p++){//修改前边权比当前询问要大，
		//由于在后续可能涉及修改，需要进行回滚 
			if(!tmp[U2[p]]&&Q[i].val<=E[U2[p]].val){
				merge(U2[p]);
				back.push_back(U2[p]); 
			}
		}
		for(int p=Q[i].id;p>=last;p--){
		//查询时序之前被修改了，并且修改后边权比当前查询负载要大
        //注意：只有修改后边权比当前查询大的边才会进行合并，所以通过from[s[p]]=-1在回撤时过滤掉不符合要求的边 
			if(in[p].type==1) tmp[in[p].x]=0;//回滚tmp数组 
			if(in[p].type==2||lastx[in[p].x]) continue;//跳过query 
			lastx[in[p].x]=-1;
			back.push_back(in[p].x);
			if(in[p].val>=Q[i].val) merge(in[p].x);//如果修改后变得对答案有影响，就合并 
		}
		ans[Q[i].id]=sz[find(Q[i].x)];
		for(int p=back.size()-1;p>=0;p--){//回滚 
			if(lastx[back[p]]!=-1){ 
				sz[lasty[back[p]]]-=sz[lastx[back[p]]];
				fa[lastx[back[p]]]=lastx[back[p]]; 
			} 
			lastx[back[p]]=0; 
		}
	}
}
int main(){
	qread(n);
	qread(m);
	for(int i=1;i<=m;i++){
		qread(E[i].from);
		qread(E[i].to);
		qread(E[i].val);
		E[i].id=i;
	}
	qread(q);
	for(int i=1;i<=q;i++) bel[i]=i/bsz+1;
	int last=1;
	for(int i=1;i<=q;i++){
		qread(in[i].type);
		qread(in[i].x);
		qread(in[i].val);
		if(in[i].type==1){
			if(!vis[in[i].x]) U2.push_back(in[i].x);
			vis[in[i].x]=1;
		}else{
			Q.push_back(query(i,in[i].x,in[i].val));			
		}
		if(bel[i]!=bel[i+1]){
			///存满一个块，进行一次离线操作
			rebuild(last);
			while(last<=i){//last记录修改和查询到哪里 
				vis[in[last].x]=0; 
				if(in[last].type==1) E[in[last].x].val=in[last].val;
				else{
					qprint(ans[last]);
					putchar('\n');
				}
				last++;
			}
			U1.clear();
			U2.clear();
			Q.clear();
			back.clear();
		}
		
	}
} 

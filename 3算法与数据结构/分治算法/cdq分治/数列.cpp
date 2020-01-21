//http://119.29.55.79/contest/80/problem/3 
//���Ȱ�ѯ��ת�������پ���,(i,a[i])����һ���� 
//ע�⵽�����پ����µ�ԲΪб45�������Σ�Բ�ڵ�ĸ�����Ϊ��
//б�������β��ò�ѯ�������б�ѩ������µ�ԲΪƽ����������������� (�൱����ʱ����ת45��) 
//�������ν��ϵĵ��Լ����µĵ������پ����µ�����ת���б�ѩ������µ�����
//���������������άǰ׺�ͼ��� 
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define maxn 1000000
using namespace std;
int n,m,tim,cnt,qcnt;
int xx[maxn+5],yy[maxn+5];
inline void change(int& x,int& y){//�ı�����ϵ 
	int xx=x,yy=y;
	x=xx+yy;
	y=xx-yy;
}
struct node{
	int a;
	int b;
	int c;
	int type;
	int val;
	int id;
	int ans;
	node(){
		
	}	
	node(int _a,int _b,int _c,int _type){
		a=_a;
		b=_b;
		c=_c;
		type=_type;
	}
	node(int _a,int _b,int _c,int _type,int _val,int _id){
		a=_a;
		b=_b;
		c=_c;
		type=_type;
		val=_val;
		id=_id;
		ans=0;
	}
}q[maxn+5]; 
int cmpa(node p,node q){
	if(p.a==q.a){
		if(p.b==q.b) return p.c<q.c;
		else return p.b<q.b;
	}else return p.a<q.a;
}
int cmpb(node p,node q){
	if(p.b==q.b) return p.c<q.c;
	else return p.b<q.b;
}


struct fenwick_tree{
	int c[maxn+5];
	inline int lowbit(int x){
		return x&(-x);
	}
	inline void update(int pos,int val){
		for(int i=pos;i<=tim;i+=lowbit(i)) c[i]+=val;
	}
	inline int query(int pos){
		int ans=0;
		for(int i=pos;i>0;i-=lowbit(i)) ans+=c[i];
		return ans; 
	}
}T;
node tmp[maxn+5];
void cdq_divide(int l,int r){//orz cdq 
	if(l==r) return;
	int mid=(l+r)>>1;
	cdq_divide(l,mid);
	cdq_divide(mid+1,r);
	int ptr=l-1;
	for(int i=mid+1;i<=r;i++){
		while(ptr<mid&&q[ptr+1].b<=q[i].b){
			ptr++;
			if(q[ptr].type==1) T.update(q[ptr].c,1);
		}
		if(q[i].type==2) q[i].ans+=T.query(q[i].c);
	} 
	for(int i=l;i<=ptr;i++) if(q[i].type==1) T.update(q[i].c,-1);
	
	int num=l-1;
	int pl=l,pr=mid+1;
	while(pl<=mid&&pr<=r){
		if(cmpb(q[pl],q[pr])) tmp[++num]=q[pl++];
		else tmp[++num]=q[pr++];
	}
	while(pl<=mid) tmp[++num]=q[pl++];
	while(pr<=r) tmp[++num]=q[pr++]; 
	for(int i=l;i<=r;i++) q[i]=tmp[i];
} 

char cmd[10]; 
int ans[maxn+5];
int main(){
	int p,k;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		xx[i]=i;
		scanf("%d",&yy[i]);
		tim++;
		q[++cnt]=node(xx[i]+yy[i],xx[i]-yy[i],tim,1);
	}
	for(int i=1;i<=m;i++){
		scanf("%s",cmd);
		if(cmd[0]=='M'){
			scanf("%d %d",&p,&k);
			tim++;
			yy[p]=k;
			q[++cnt]=node(xx[p]+yy[p],xx[p]-yy[p],tim,1); 
		}else{
			int x1,y1,x2,y2;
			scanf("%d %d",&p,&k);
			x1=xx[p]-k;
			y1=yy[p];
			x2=xx[p]+k;
			y2=yy[p];
			change(x1,y1);
			change(x2,y2);
			tim++;
			qcnt++;
			q[++cnt]=node(x2,y2,tim,2,1,qcnt);
			q[++cnt]=node(x1-1,y2,tim,2,-1,qcnt);
			q[++cnt]=node(x2,y1-1,tim,2,-1,qcnt);
			q[++cnt]=node(x1-1,y1-1,tim,2,1,qcnt); 
		}
	}
	sort(q+1,q+1+cnt,cmpa);
	cdq_divide(1,cnt);
	for(int i=1;i<=cnt;i++){
		if(q[i].type==2) ans[q[i].id]+=q[i].val*q[i].ans;
	}
	for(int i=1;i<=qcnt;i++) printf("%d\n",ans[i]);
} 

#include<iostream>
#include<cstring>
using namespace std;
#define max 10000
int compare(int p[],int q[],int len) {
	for(int i=len-1; i>=0; i--) {
		if(p[i]>q[i]) return 1;
		if(p[i]<q[i]) return -1;
		}
		return 0;

}
void jian(int u[],int v[],int total[],int num) {
	int i,k,x;
	k=0;
	x=0;
	while(num>k) {
		if(u[k]<v[k]) {
			u[k]+=10;
			u[k+1]--;

		}
		total[k]=u[k]-v[k];
		k++;
	}
	k--;
	while(total[k]==0) {
		k--;
		if(k==0) {
			break;
		}
	}
	return;
}
void mycopy(int s[],int t[],int weis,int weit){//s传到t的第 weit位 
   int i;
   for(i=0;i<weis;i++) t[i+weit]=s[i]; 
}
void devide(int de1[],int de2[],int result[],int len1,int len2) {
	int temp[max],total[max];
	int g;
	int i ;
	int m ;
	int data1[max],data2[max];
	int res[max];
	memset(data1,0,sizeof(data1));
	memset(data2,0,sizeof(data2));
//	memset(res,0,sizeof(res));
	memset(total,0,sizeof(total));
	
	for(i=0; i<len1; i++) {
		data1[i]=de1[i];
		data2[i]=de2[i];
	}
	
	
	g=len1-len2;
	for(i=g;i>=0;i--){
		memset(temp,0,sizeof(temp));
		mycopy(data2,temp,len2,i);
		while(compare(data1,temp,len1)>=0){
			result[i]++;
		//	res[i]++;
			jian(data1,temp,total,len1);
			for(m=len1-1;m>=0;m--){
				data1[m]=total[m];
				total[m]=0;
			}
			
		}
	}
	
	

     return;
}
int main() {
	string a,c;
	int i,k,out;
	int b[max];
	int d[max];
	int result[max];
	cout<<"请输入被除数："<<'\n' ;
	cin>>a;
	cout<<"请输入除数："<<'\n' ;
	cin>>c;

    memset(b,0,sizeof(b));
    memset(d,0,sizeof(d));
    memset(result,0,sizeof(result));
	for(i=0; i<a.length(); i++) {
		b[a.length()-i-1]=a[i]-48;

	}
	for(i=0; i<c.length(); i++) {
		d[c.length()-i-1]=c[i]-48;
	}
	devide(b,d,result,a.length(),c.length());
	
	 for(i=a.length()-1; i>=0; i--) //0 不输出
		{
			if(result[i]!=0) break;
		}

	for(; i>=0; i--) //输出
		cout<<result[i];	
	return 0;
}


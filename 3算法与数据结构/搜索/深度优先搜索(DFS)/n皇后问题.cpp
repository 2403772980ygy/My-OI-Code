#include<iostream>
#include<cstdio> 
using namespace std;
/*在8X8格的国际象棋上摆放八个皇后，使其不能互相攻击，
即任意两个皇后都不能处于同一行、同一列或同一斜线上，
问有多少种摆法?
*/
int ans[100];//= {3,1,7,4,6,0,2,5};//一组解 
int a=0,n;
bool check(int lie,int num) {//lie就是列数，num是每列的第几个 
	int res=1;
	for(int i=0; i<lie; i++) {
		if(num==ans[i]) res=0;
		if(lie-num==i-ans[i]) res=0;
		if(lie+num==i+ans[i]) res=0;
	}
	return res;
}
int dfs(int loc) {//loc和lie一样 
	if(loc==n) {
		for(int i=0; i<n; i++) cout<<ans[i]<<' ';
		a=a+1;
		cout<<endl;

	}
	for(int i=0; i<n; i++) {
		if(check(loc,i)) {
			ans[loc]=i;
			dfs(loc+1);
		}
	}
}
int main() {
	cin>>n;
	dfs(0);
	cout<<a;
}

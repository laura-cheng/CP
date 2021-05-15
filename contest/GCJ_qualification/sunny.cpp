#include<bits/stdc++.h>
#define int long long 
using namespace std;

int n, m, x, y;
char mp[200][200];
int lft[5][2] = {{1,0},{0,1},{-1,0},{0,-1},{1,0}};
int l, lx, ly, fx, fy;
void init(){
	if(x==0) l=1;
	else if(y==0) l=2;
	else if(x==n-1) l=3;
	else l=4;
	lx = lft[l][0], ly = lft[l][1];
	fx = lft[l-1][0], fy = lft[l-1][1];
}

void turnL(){
	if(l==4) l=1;
	else l++;
	lx = lft[l][0], ly = lft[l][1];
	fx = lft[l-1][0], fy = lft[l-1][1];
}

void turnR(){
	if(l==1) l=4;
	else l--;
	lx = lft[l][0], ly = lft[l][1];
	fx = lft[l-1][0], fy = lft[l-1][1];
}

void print(){
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++) cout << mp[i][j];
		cout << '\n';
	} 
}

signed main(){
	cin >> n >> m;
	x = y = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cin >> mp[i][j];
			if(mp[i][j]=='I') x = i,y = j;
		}
	}
	init();
	bool yes = 0;
	while(true){
		
		for(int i = 0; i < 4; i++) {
			if(mp[x + lft[i][0]][y + lft[i][1]] == 'O') {
				yes = 1;
			}
		}
		if(yes) break;
		if(mp[x+lx][y+ly]!='X'){  //left
			x += lx, y += ly;
			turnL();
			mp[x][y] = '*';
		}
		else if(mp[x+fx][y+fy]!='X'){  //front
			x += fx, y += fy;
			mp[x][y] = '*';
		}
		else turnR();
	}
	print();
}

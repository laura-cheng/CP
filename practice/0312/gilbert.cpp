#include<bits/stdc++.h> 
using namespace std; 
int N; 
// If there are some number a_i = a_j where l <= i < r and (j<l or j>=r) return false; 
// Otherwise, return true. 
bool valid(vector<int> a,int l,int r){            
    vector<int>used(N+1); 
    for(int i=0;i<N;i++){             
        if(i<l||i>=r)used[a[i]]=1; 
    } 
    for(int i=l;i<r;i++) 
        if(used[a[i]])return false; 
    return true;
} 

int main(){ 
    int T; 
    cin >> T;
    while(T--){ 
        vector<int>input; 
        cin >> N;
        for(int i=0;i<N;i++){ 
            int x; 
            cin >> x;
            input.push_back(x); 
        } 
        int an=0; 
        for(int i=0;i<N;i++) 
            for(int j=i+1;j<=N;j++){ 
                if(valid(input,i,j)) an++; 
            } 
        cout << an << '\n';
    } 
    return 0; 
}

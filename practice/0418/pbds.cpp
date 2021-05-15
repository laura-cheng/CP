#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

using namespace __gnu_pbds;  
using namespace std;
// some functions
// 1. find_by_order => return iterator
// 2. order_of_key => return int
// 3. insert, erase
// 4. lower_bound() 
// 5. upper_bound()
// 6. a.join(b) 
// 7. a.split(v, b) key <= v belongs to a, others go to b
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	treap trp, trp1;
	for(int i = 100; i > 0; i -= 2) {
		trp.insert(1);
	} 	
	trp.insert(0);
	cerr << trp.order_of_key(2) << "\n";
	cerr << trp.size() << "\n";
	return 0;
}

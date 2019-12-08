/*
    Problem: 246D. Colorful Graph
    Solution: graphs, dfs, implementation
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int nmax = (int)1e5;
int main() {
	int m,n; cin >> n >> m;
	vector<int> color(n);
	for (auto& it : color) cin >> it;
	vector<vector<int>> arr(1+nmax);	
	while (m--) {
		int a, b; cin >> a >> b; --a,--b;
		if (color[a] != color[b]) {
			arr[color[a]].push_back(color[b]);
			arr[color[b]].push_back(color[a]);
		}
	}
    
	int cmax = *min_element(color.begin(), color.end());
	sort(arr[cmax].begin(), arr[cmax].end());
	arr[cmax].erase(unique(arr[cmax].begin(), arr[cmax].end()), arr[cmax].end());
	
    int limit = *max_element(color.begin(), color.end());
	for (int c = 1; c <= limit; ++c) {
		sort(arr[c].begin(), arr[c].end());
		arr[c].erase(unique(arr[c].begin(), arr[c].end()), arr[c].end());
		if (arr[c].size() > arr[cmax].size()) cmax = c;
	}
	cout << cmax;
	return 0;
}
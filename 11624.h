#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <cstdint> //or <stdint.h>
#include <limits>
#include <climits>
#include <queue>
using namespace std;

class Solution {
    public:
    typedef pair<int, int> pii;
    typedef pair<int, pii> piii;
    void input() {
        int t, r, c;
        
        cin >> t;
        while(t--) {
            int ji, jj;
            vector<pair<int, int>> fires;
            cin>>r>>c;
            vector<string> grid;
            for(int i = 0; i < r; i++) {
                string tmp;
                cin>>tmp;
                grid.push_back(tmp);
                for(int j = 0; j < c; j++) {
                    if (grid[i][j] == 'J') {
                        ji = i;
                        jj = j;
                    }
                    if (grid[i][j] == 'F') {
                        fires.emplace_back(i, j);
                    }
                }
            }
            int res = solve(grid, ji, jj, fires);
            if (res < 0) {
                cout << "IMPOSSIBLE" << endl;
            } else {
                cout << res << endl;
            }
        }
    }

    vector<vector<int>> dir = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
    };

    int solve(vector<string> &grid, int ji, int jj, vector<pair<int, int>>& fires){
        if (grid.size() == 0 || grid[0].size() == 0) return -1;
        int n = grid.size();
        int m = grid[0].size();
        if (ji == 0 || ji == n - 1 || jj == 0 || jj == m - 1) {
            return 1;
        }

        queue<pii> qu;
        vector<vector<int>> fireDist(n, vector<int>(m, INT_MAX));
        for(auto p: fires) {
            fireDist[p.first][p.second] = 1;
            qu.push(p);
        }
        while(!qu.empty()) {
            auto pos = qu.front();
            qu.pop();

            for(int d = 0; d < 4; d++) {
                int ni = pos.first + dir[d][0];
                int nj = pos.second + dir[d][1];
                if (ni >= 0 && ni < n && nj >= 0 && nj < m &&
                grid[ni][nj] != '#' && 
                fireDist[ni][nj] == INT_MAX) {
                    fireDist[ni][nj] = fireDist[pos.first][pos.second] + 1;
                    qu.emplace(ni, nj);
                }
            }
        }
        vector<vector<int>> manDist(n, vector<int>(m, INT_MAX));
        manDist[ji][jj] = 1;
        qu.emplace(ji, jj);
        while(!qu.empty()) {
            auto pos = qu.front();
            qu.pop();
            int dis = manDist[pos.first][pos.second];

            for(int d = 0; d < 4; d++) {
                int ni = pos.first + dir[d][0];
                int nj = pos.second + dir[d][1];
                if (ni >= 0 && ni < n && nj >= 0 && nj < m &&
                grid[ni][nj] != '#' && 
                manDist[ni][nj] == INT_MAX &&
                dis + 1 < fireDist[ni][nj]) {
                    manDist[ni][nj] = dis + 1;
                    if (ni == 0 || nj == 0 || ni == n - 1 || nj == m - 1) {
                        return manDist[ni][nj];
                    }
                    qu.emplace(ni, nj);
                }
            }
        }
        return -1;
    }
};
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <cstdint> //or <stdint.h>
#include <limits>
#include <climits>
#include <string>
#include <queue>
using namespace std;

struct Solution {
    void input() {
        int m, n;
        int testcase = 1;
        while (cin >>m >> n && m > 0 && n > 0)
        {
            vector<string> grid;
            int si, sj;
            //for input, n and m is reverse
            for(int i = 0; i < m; i++) {
                string tmp;
                cin >> tmp;
                grid.push_back(tmp);
                int j = tmp.find('S');
                if (j != string::npos) {
                    si = i;
                    sj = j;
                }
            }
            int res = solve(grid, si, sj);
            if (testcase > 1) cout << endl;
            cout << "Case #" << testcase << endl;
            testcase++;
            if (res < 0) {
                cout << "destination not reachable" << endl;
            } else {
                cout << "minimum time = " << res << " sec" << endl;
            }
        }
        
    }
    vector<vector<int>> direction = {
        {-1, 0},
        {0, 1},
        {1, 0},
        {0, -1}
    };
    struct state
    {
        int i, j, d, c;
    };
    
    typedef pair<int, pair<int, int>> piii;
    int solve(vector<string>& grid, int si, int sj) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<vector<vector<int>>>> dis(n, vector<vector<vector<int>>>(m, vector<vector<int>>(4, vector<int>(5, INT_MAX))));

        queue<state> qu;
        dis[si][sj][0][0] = 0;
        qu.push({si, sj, 0, 0});

        while(!qu.empty()) {
            auto now = qu.front();
            qu.pop();

            for(int nd = -1; nd <= 1; nd += 2) {
                int nnd = (now.d + nd + 4) % 4;
                if (dis[now.i][now.j][nnd][now.c] == INT_MAX) {
                    dis[now.i][now.j][nnd][now.c] = dis[now.i][now.j][now.d][now.c] + 1;
                    qu.push({now.i, now.j, nnd, now.c});
                }
            }
            int ni = now.i + direction[now.d][0];
            int nj = now.j + direction[now.d][1];
            int nc = (now.c + 1) % 5;
            if (ni >= 0 && ni < n && nj >= 0 && nj < m &&
                grid[ni][nj] != '#' && dis[ni][nj][now.d][nc] == INT_MAX) {
                    dis[ni][nj][now.d][nc] = dis[now.i][now.j][now.d][now.c] + 1;
                    qu.push({ni, nj, now.d, nc});
                    if (nc == 0 && 
                        grid[ni][nj] == 'T') 
                        return dis[ni][nj][now.d][nc];
                }
        }
        return -1;
    }
};
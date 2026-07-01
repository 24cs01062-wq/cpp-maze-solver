//
//  main.cpp
//  proj
//
//  Created by Raam Sundaran on 01/07/26.
//
#include <iostream>
#include<vector>
#include<string>
#include<thread>
#include<chrono>
#include<queue>
using namespace std;

int n, m;

vector<string> grid;

pair<int,int> startP, endP;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool inside(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m;
}


string green = "\033[32m";
string yellow = "\033[33m";
string reset = "\033[0m";

void printGrid(vector<vector<int>> &vis, vector<vector<pair<int,int>>> &parent, bool showPath=false) {
    vector<vector<int>> onPath(n, vector<int>(m, 0));

    if (showPath) {
        pair<int,int> cur = endP;
        while (cur != startP) {
            onPath[cur.first][cur.second] = 1;
            cur = parent[cur.first][cur.second];
        }
        onPath[startP.first][startP.second] = 1;
    }

    system("clear");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c = grid[i][j];

            if (c == '#') cout << "# ";
            else if (make_pair(i,j) == startP) cout << "S ";
            else if (make_pair(i,j) == endP) cout << "E ";
            else if (onPath[i][j]) cout << yellow << "* " << reset;
            else if (vis[i][j]) cout << green << ". " << reset;
            else cout << ". ";
        }
        cout << "\n";
    }

    this_thread::sleep_for(chrono::milliseconds(80));
}

void bfs() {
    queue<pair<int,int>> q;
    vector<vector<int>> vis(n, vector<int>(m, 0));
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1,-1}));

    q.push(startP);
    vis[startP.first][startP.second] = 1;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        printGrid(vis, parent, false);

        if (make_pair(x,y) == endP) break;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (inside(nx, ny) && !vis[nx][ny] && grid[nx][ny] != '#') {
                vis[nx][ny] = 1;
                parent[nx][ny] = {x, y};
                q.push({nx, ny});
            }
        }
    }


    for (int i = 0; i < 10; i++) {
        printGrid(vis, parent, true);
    }
}

int main() {
    cin >> n >> m;
    grid.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    cin >> startP.first >> startP.second;
    cin >> endP.first >> endP.second;

    bfs();

    cout << "\nDone!\n";
}

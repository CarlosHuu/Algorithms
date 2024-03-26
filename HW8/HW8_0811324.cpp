#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

const int NUM_ROWS = 17;
const int NUM_COLS = 17;

// 定義節點結構，包含座標和距離
struct Node
{
    int x, y, dist;
    Node(int xCoordinate, int yCoordinate, int distance) : x(xCoordinate), y(yCoordinate), dist(distance) {}
};
// 上、下、左、右的位移量
int rowOffsets[] = { -1, 0, 0, 1 };
int colOffsets[] = { 0, -1, 1, 0 };
bool isValid(vector<vector<int>>& maze, vector<vector<bool>>& visited, int row, int col);// 檢查座標是否有效（在迷宮範圍內且未被訪問）
int ShortestPath(vector<vector<int>>& grid, pair<int, int>& start, pair<int, int>& destination, vector<pair<int, int>>& path, vector<vector<int>>& shortestDistances);// 尋找最短路徑的長度並記錄最短路徑

int main()
{
    // 打開輸入文件
    ifstream inputFile("input.txt");
    if (inputFile.fail()) {
        cout << "Input file opening fail." << endl;
        return 1;
    }

    // 打開輸出文件
    ofstream outputFile("0811324_output.txt");
    if (outputFile.fail()) {
        cout << "Output file opening fail." << endl;
        return 0;
    }

    // 迴圈處理不同模式的迷宮
    for(int patternIndex = 0; patternIndex <= 19; patternIndex++){
        // 創建迷宮地圖和最短距離矩陣
        vector<vector<int> > grid(NUM_ROWS + 1, vector<int>(NUM_COLS + 1, 0));
        vector<vector<int> > shortestDistances(NUM_ROWS + 1, vector<int>(NUM_COLS + 1, 0));

        // 從輸入文件讀取迷宮地圖並初始化最短距離矩陣
        for (int i = 1; i <= NUM_ROWS; i++) {
            for (int j = 1; j <= NUM_COLS; j++) {
                inputFile >> grid[i][j];
                shortestDistances[i][j] = 100000;
            }
        }

        // 寫入輸出文件的標題
        outputFile << "pattern " << patternIndex+1 << "\n";

        // 設定起點和終點的座標
        pair<int, int> start = make_pair(1, 1);
        pair<int, int> destination = make_pair(17, 17);

        // 儲存最短路徑的座標
        vector<pair<int, int> > path;

        // 尋找最短路徑的長度
        int minDistance = ShortestPath(grid, start, destination, path, shortestDistances);

        // 如果找到最短路徑
        if (minDistance != -1)
        {
            // 寫入步數和最短路徑到輸出文件
            outputFile << "step=" << minDistance << endl;
            for (const auto& cell : path)
            {
                outputFile << "(" << cell.first << "," << cell.second << ")"<< endl;
            }
            outputFile << endl;
        }
        else {
            cout << "Cannot reach!!!\n";
        }
    }

    // 關閉文件
    inputFile.close();
    outputFile.close();
    return 0;
}

// 檢查座標是否有效（在迷宮範圍內且未被訪問）
bool isValid(vector<vector<int>>& maze, vector<vector<bool>>& visited, int row, int col) 
{
    return (row >= 0 && row < static_cast<int>(maze.size())) && (col >= 0 && col < static_cast<int>(maze[0].size())) && maze[row][col] && !visited[row][col];
}

// 尋找最短路徑的長度並記錄最短路徑
int ShortestPath(vector<vector<int>>& grid, pair<int, int>& start, pair<int, int>& destination, vector<pair<int, int>>& path, vector<vector<int>>& shortestDistances)
{
    // 檢查迷宮的有效性，起點和終點是否可通行
    if (grid.size() == 0 || grid[start.first][start.second] == 0 || grid[destination.first][destination.second] == 0) {
        return -1;
    }

    int numRows = grid.size();
    int numCols = grid[0].size();

    // 用於記錄節點是否訪問過
    vector<vector<bool>> visited;
    visited.resize(numRows + 1, vector<bool>(numCols + 1));

    // 使用廣度優先搜索（BFS）進行最短路徑尋找
    queue<Node> q;

    int startX = start.first;
    int startY = start.second;

    visited[startX][startY] = true;
    q.push(Node(startX, startY, 0));

    int minDistance = INT_MAX;

    // 用於回溯最短路徑
    vector<vector<pair<int, int>>> prev(numRows + 1, vector<pair<int, int>>(numCols + 1));
    for (int i = 1; i <= numRows; ++i) {
        for (int j = 1; j <= numCols; ++j) {
            prev[i][j] = make_pair(-1, -1);
        }
    }

    while (!q.empty())
    {
        Node node = q.front();
        q.pop();

        int x = node.x;
        int y = node.y;
        int distance = node.dist;

        // 到達終點，更新最短路徑長度並結束搜索
        if (x == destination.first && y == destination.second)
        {
            minDistance = shortestDistances[x][y];
            break;
        }

        // 嘗試四個方向的移動
        for (int k = 0; k < 4; k++)
        {
            if (isValid(grid, visited, x + rowOffsets[k], y + colOffsets[k]))
            {
                if (grid[x + rowOffsets[k]][y + colOffsets[k]] == 1) {
                    // 移動到可通行的節點，距離加1
                    q.push(Node(x + rowOffsets[k], y + colOffsets[k], distance + 1));
                    // 如果新的距離更短，則更新最短距離和前一個節點
                    if (distance + 1 < shortestDistances[x + rowOffsets[k]][y + colOffsets[k]]) {
                        shortestDistances[x + rowOffsets[k]][y + colOffsets[k]] = distance + 1;
                        prev[x + rowOffsets[k]][y + colOffsets[k]] = make_pair(x, y);
                    }
                }
                else if (grid[x + rowOffsets[k]][y + colOffsets[k]] == 2) {
                    // 移動到特殊節點，距離加2
                    q.push(Node(x + rowOffsets[k], y + colOffsets[k], distance + 2));
                    // 如果新的距離更短，則更新最短距離和前一個節點
                    if (distance + 2 < shortestDistances[x + rowOffsets[k]][y + colOffsets[k]]) {
                        shortestDistances[x + rowOffsets[k]][y + colOffsets[k]] = distance + 2;
                        prev[x + rowOffsets[k]][y + colOffsets[k]] = make_pair(x, y);
                    }
                }
            }
        }
        visited[x][y] = true;
    }

    // 如果找到最短路徑，回溯路徑並返回最短距離
    if (minDistance != INT_MAX) {
        int x = destination.first;
        int y = destination.second;

        while (prev[x][y].first != -1 && prev[x][y].second != -1)
        {
            path.push_back(make_pair(x, y));

            if (grid[x][y] == 2)
            {
                // 特殊節點重複添加
                path.push_back(make_pair(x, y));
            }

            int tempX = prev[x][y].first;
            int tempY = prev[x][y].second;
            x = tempX;
            y = tempY;
        }
        path.push_back(make_pair(x, y));
        reverse(path.begin(), path.end());

        return minDistance;
    }

    return -1;
}
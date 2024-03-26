#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void PrintOptimal_BST(const vector<vector<int>>& root, int i, int j, int level) ;
void Optimal_BST(const vector<double>& probabilities, const vector<double>& qValues, int n) ;

int main() {
    int node;
    cout << "Enter the number of nodes: ";
    cin >> node;

    vector<double> probabilities(node + 1), qValues(node + 1);

    cout << "Enter the probabilities for keys (p0 to pn): ";
    for (int i = 0; i <= node; i++) 
    {
        cin >> probabilities[i];
    }

    cout << "Enter the probabilities for dummy keys (q0 to qn): ";
    for (int i = 0; i <= node; i++) 
    {
        cin >> qValues[i];
    }
    // vector<double> p = {0.0, 0.15, 0.10, 0.05, 0.10, 0.20};
    // vector<double> q = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
    // vector<double> p = {0.0, 0.05, 0.15, 0.15, 0.10, 0.10};
    // vector<double> q = {0.05, 0.10, 0.05, 0.10, 0.05, 0.10};
    // int n = 5;
    // 計算並輸出最佳二元搜尋樹
    Optimal_BST(probabilities, qValues, node);
    
    return 0;
}


void PrintOptimal_BST(const vector<vector<int>>& root, int i, int j, int level) 
{
    // 遞迴函數，用於印出最佳二元搜尋樹的結構
    // root：存儲最佳樹的根節點索引的二維向量
    // i：子樹的起始索引
    // j：子樹的結束索引
    // level：父節點的索引

    if (i > j) 
    {
        // 子樹為空，返回
        return;
    }
    if (i == j) 
    {
        // 子樹只有一個節點
        if (level == 0) 
        {
            cout << "k" << i << " is the root" << endl;
        } 
        else if (j < level) 
        {
            cout << "k" << i << " is the left child of k" << level << endl;
        } 
        else 
        {
            cout << "k" << i << " is the right child of k" << level << endl;
        }
        return;
    }

    int r = root[i][j];
    // 獲取子樹的根節點索引
    if (level == 0) 
    {
        cout << "k" << r << " is the root" << endl;
    } 
    else if (r < level) 
    {
        cout << "k" << r << " is the left child of k" << level << endl;
    } 
    else 
    {
        cout << "k" << r << " is the right child of k" << level << endl;
    }
    // 印出節點關係
    PrintOptimal_BST(root, i, r - 1, r);
    PrintOptimal_BST(root, r + 1, j, r);
    // 遞迴處理左子樹和右子樹
}

void Optimal_BST(const vector<double>& probabilities, const vector<double>& qValues, int n) 
{
    // 計算最佳二元搜尋樹的函數
    // probabilities：鍵的概率向量
    // qValues：虛擬鍵的概率向量
    // n：節點數量

    vector<vector<double>> cost(n + 2, vector<double>(n + 1, 0.0));
    vector<vector<double>> e(n + 2, vector<double>(n + 1, 0.0));
    vector<vector<int>> root(n + 1, vector<int>(n + 1, 0));

    // 初始化
    for (int i = 1; i <= n + 1; i++) 
    {
        e[i][i - 1] = qValues[i - 1];
        cost[i][i - 1] = qValues[i - 1];
    }

    // 動態規劃求解
    for (int length = 1; length <= n; length++) 
    {
        for (int i = 1; i <= n - length + 1; i++) 
        {
            int j = i + length - 1;
            e[i][j] = numeric_limits<double>::max();
            cost[i][j] = cost[i][j - 1] + probabilities[j] + qValues[j];
            for (int rootIndex = i; rootIndex <= j; rootIndex++) 
            {
                double temp = e[i][rootIndex - 1] + e[rootIndex + 1][j] + cost[i][j];
                if (temp < e[i][j]) 
                {
                    e[i][j] = temp;
                    root[i][j] = rootIndex;
                }
            }
        }
    }

    // 輸出結果
    cout << "Smallest Search Cost: " << e[1][n] << endl;
    cout << "Root: " << root[1][n] << endl;
    cout << "Optimal BST _ structure: " << endl;
    PrintOptimal_BST(root, 1, n, 0);
    // 印出最佳二元搜尋樹的結果
}
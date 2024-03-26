#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

int MEMOIZED_CUT_ROD_AUX(vector<int>& p, int n, vector<int>& r, vector<int>& s);// max: top-down memoization
int MEMOIZED_CUT_ROD(vector<int>& p, int n, vector<int>& r, vector<int>& s);
int MEMOIZED_CUT_ROD_MIN_AUX(vector<int>& p, int n, vector<int>& r, vector<int>& s);// min: top-down memoization
int MEMOIZED_CUT_ROD_MIN(vector<int>& p, int n, vector<int>& r, vector<int>& s);
int Extended_Bottom_Up_Cut_Rod(int p[], int n, int r[], int s[]);// max: extended bottom-up
int Extended_Bottom_Up_Cut_Rod_MIN(int p[], int n, int r[], int s[]);// min: extended bottom-up
void Print_Cut_Rod_Solution(int s[], int n);// print the cut solution, array input
void Print_Cut_Rod_Solution_vec(vector<int>& s, int n);// print the cut solution, vector input


int main()
{
   
    int p[10];
    vector<int> p_vec;
    
    int n;
    int result;

    cout << "Enter the length of rod: ";
    cin >> n;
    cout << "Enter the price of rod from 1~10: " << endl;
    for (int i = 0; i < n; i++){
        cin >> p[i];
        p_vec.push_back(p[i]);
    } 

    // top_down
    cout << endl << "Top Down: " << endl;

    vector<int> r_td_max(n+1, INT_MIN);
    vector<int> s_td_max(n+1, 0);
    result = MEMOIZED_CUT_ROD(p_vec, n, r_td_max, s_td_max);
    cout << "Maximum Revenue : " << result << endl;

    Print_Cut_Rod_Solution_vec(s_td_max, n);

    vector<int> r_td_min(n+1, INT_MAX);
    vector<int> s_td_min(n+1, 0);
    result = MEMOIZED_CUT_ROD_MIN(p_vec, n, r_td_min, s_td_min);
    cout << "Minimum Revenue : " << result << endl;

    Print_Cut_Rod_Solution_vec(s_td_min, n);

    //bottom-up
    cout << endl << "Bottom Up: " << endl;
   

    int r_bu_max[n+1];
    int s_bu_max[n+1];
    result = Extended_Bottom_Up_Cut_Rod(p, n, r_bu_max, s_bu_max);
    cout << "Maximum Revenue : " << result << endl;
    
    Print_Cut_Rod_Solution(s_bu_max, n);

    int r_bu_min[n+1];
    int s_bu_min[n+1];
    result = Extended_Bottom_Up_Cut_Rod_MIN(p, n, r_bu_min, s_bu_min);
    cout << "Minimum Revenue : " << result << endl;
    
    Print_Cut_Rod_Solution(s_bu_min, n);


    return 0;
}


// 使用頂部向下的記憶化方法求解切割鋼條問題，最大化收益
// 參數：
//   - p: 切割方案價格的向量
//   - n: 需要切割的鋼條長度
//   - r: 傳遞記憶化數據的向量，存儲已計算的子問題解的收益
//   - s: 傳遞記憶化數據的向量，存儲每個子問題的最佳切割方案
int MEMOIZED_CUT_ROD_AUX(vector<int>& p, int n, vector<int>& r, vector<int>& s) 
{
    // 如果已經計算過 r[n]，則直接返回該值，避免重複計算
    if (r[n] >= 0)
        return r[n];

    int q;
    if (n == 0)
        q = 0;
    else 
    {
        q = INT_MIN;
        for (int i = 1; i <= n; i++) 
        {
            // 遞迴調用 MEMOIZED_CUT_ROD_AUX 函數計算子問題的最優解
            // 將問題的規模減小，求解 n-i 長度的子問題的最優解 val
            int val = MEMOIZED_CUT_ROD_AUX(p, n - i, r, s);
            // 判斷當前切割方案的收益是否大於目前最大收益 q
            if (q < p[i - 1] + val) 
            {
                // 更新最大收益 q
                q = p[i - 1] + val;
                // 更新 n 長度的最佳切割方案 s[n]
                s[n] = i;
            }
        }
    }
    // 將計算結果保存到記憶化數據中
    r[n] = q;
    return q;
}

// 使用頂部向下的記憶化方法求解切割鋼條問題，最大化收益
int MEMOIZED_CUT_ROD(vector<int>& p, int n, vector<int>& r, vector<int>& s) 
{
    // 調用 MEMOIZED_CUT_ROD_AUX 函數求解切割鋼條問題，並返回最大化的收益
    return MEMOIZED_CUT_ROD_AUX(p, n, r, s);
}


int MEMOIZED_CUT_ROD_MIN_AUX(vector<int>& p, int n, vector<int>& r, vector<int>& s) 
{
    // 如果已經計算過 r[n]，則直接返回該值，避免重複計算
    if (r[n] <= 0)
        return r[n];

    int q;
    if (n == 0)
        q = 0;
    else 
    {
        q = INT_MAX;
        for (int i = 1; i <= n; i++) 
        {
            // 遞迴調用 MEMOIZED_CUT_ROD_MIN_AUX 函數計算子問題的最優解
            // 將問題的規模減小，求解 n-i 長度的子問題的最優解 val
            int val = MEMOIZED_CUT_ROD_MIN_AUX(p, n - i, r, s);
            // 判斷當前切割方案的成本是否小於目前最小成本 q
            if (q > p[i - 1] + val) 
            {
                // 更新最小成本 q
                q = p[i - 1] + val;
                // 更新 n 長度的最佳切割方案 s[n]
                s[n] = i;
            }
        }
    }
    // 將計算結果保存到記憶化數據中
    r[n] = q;
    return q;
}

int MEMOIZED_CUT_ROD_MIN(vector<int>& p, int n, vector<int>& r, vector<int>& s) 
{
    // 調用 MEMOIZED_CUT_ROD_MIN_AUX 函數求解切割鋼條問題，並返回最小化的成本
    return MEMOIZED_CUT_ROD_MIN_AUX(p, n, r, s);
}



// 使用底部向上的方法求解切割鋼條問題，最大化收益
int Extended_Bottom_Up_Cut_Rod(int p[], int n, int r[], int s[]) 
{
    int q;
    // 初始化 r[0] 和 s[0] 為 0，表示鋼條長度為 0 時的解
    r[0] = 0;
    s[0] = 0;
    for (int j = 1; j <= n; j++) 
    {
        q = INT_MIN;
        for (int i = 0; i < j; i++) 
        {
            // 遍歷各種切割方案，計算最大收益 q 和最佳切割方案 s[j]
            if (q < (p[i] + r[j - i - 1])) 
            {
                q = p[i] + r[j - i - 1];
                s[j] = i + 1;
            }
        }
        // 將計算結果保存到 r[j] 中
        r[j] = q;
    }
    // 返回最大收益 q
    return q;
}


// 使用底部向上的方法求解切割鋼條問題，最小化成本
int Extended_Bottom_Up_Cut_Rod_MIN(int p[], int n, int r[], int s[]) 
{
    int q;
    // 初始化 r[0] 和 s[0] 為 0，表示鋼條長度為 0 時的解
    r[0] = 0;
    s[0] = 0;
    for (int j = 1; j <= n; j++) 
    {
        q = INT_MAX;
        for (int i = 0; i < j; i++) {
            // 遍歷各種切割方案，計算最小成本 q 和最佳切割方案 s[j]
            if (q > (p[i] + r[j - i - 1]))
            {
                q = p[i] + r[j - i - 1];
                s[j] = i + 1;
            }
        }
        // 將計算結果保存到 r[j] 中
        r[j] = q;
    }
    // 返回最小成本 q
    return q;
}



//   - s: 存儲每個子問題的最佳切割方案的陣列
//   - n: 需要切割的鋼條長度
void Print_Cut_Rod_Solution(int s[], int n)
{
    cout << "Cut type: ";
    int count = 0;
    while (n > 0) 
    {
        // 輸出最佳切割方案
        cout << s[n] << " ";
        // 更新鋼條長度 n，繼續輸出切割方案
        n = n - s[n];
        // 統計切割的鋼條片數
        count++;
    }
    // 輸出切割片數
    cout << endl <<"number of pieces: " << count << endl;
}


//   - s: 存儲每個子問題的最佳切割方案的向量
//   - n: 需要切割的鋼條長度
void Print_Cut_Rod_Solution_vec(vector<int>& s, int n)
{
    cout << "Cut type: ";
    int count = 0;
    while (n > 0) 
    {
        // 輸出最佳切割方案
        cout << s[n] << " ";
        // 更新鋼條長度 n，繼續輸出切割方案
        n = n - s[n];
        // 統計切割的鋼條片數
        count++;
    }
    // 輸出切割片數
    cout << endl <<"number of pieces: " << count << endl;
}


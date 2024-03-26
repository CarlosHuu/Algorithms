#include <iostream>
#include <random>
#include <chrono>
//#include <vector>
using namespace std;

void random_array(int* arr, int size);
void insertion_sort(int arr[], int size);
void merge_sort(int* arr, int p, int q);
void merge(int* arr, int p, int q, int m);

int main()
{
	int arr_size;
	cout << "Enter the input size: " ;
	cin >> arr_size;
			
//        vector<int> arr(arr_size);
        int* arr = new int[arr_size];
        random_array(arr, arr_size);

//		// Measure Insertion Sort time
//        auto start_insertion = chrono::high_resolution_clock::now();
        insertion_sort(arr, arr_size);
		for (int i = 0 ; i <arr_size ; i++)
         {
             cout << arr[i] <<" ";
         }
//        auto end_insertion = chrono::high_resolution_clock::now();
//        auto duration_insertion = chrono::duration_cast<chrono:: microseconds>(end_insertion - start_insertion);
//        cout << "Insertion Sort with size " << arr_size << " took " << duration_insertion.count() << " microseconds." << endl;
//
//		random_array(arr, arr_size);
//		// Measure Merge Sort time
//        auto start_merge = chrono::high_resolution_clock::now();
//        merge_sort(arr, 0, arr_size - 1);
         
//        auto end_merge = chrono::high_resolution_clock::now();
//        auto duration_merge = chrono::duration_cast<chrono:: microseconds>(end_merge - start_merge);
//        cout << "Merge Sort with size " << arr_size << " took " << duration_merge.count() << " microseconds." << endl<<endl;


	return 0;
}

void random_array(int* arr, int size)
{
    random_device rd; //隨機設備，創建一個名為rd的random_device對象。
    mt19937 gen(rd());  //亂數產生器，mt19937是一種隨機數生成器引擎，可以生成高品質的隨機數序列。
    uniform_int_distribution<int> dis(1, 1000);//表示生成一個在 1 到 100000 之間的均勻分布的隨機整數
    for (int i = 0; i < size; i++) 
	{
        arr[i] = dis(gen);
    }
}

void insertion_sort(int arr[], int size) //// 定義一個函式名稱為 "insertion_sort"，接收一個指向整數陣列的指標 "arr" 和陣列的大小 "size" 
{
    int i, key, j;
    for (i = 1; i < size; i++) // 使用 for 迴圈，從第二個元素開始比對陣列元素，並遞增迭代
	{
        key = arr[i];// 將目前元素的值存到 key 變數
        j = i - 1; // 將目前迴圈所指向的元素索引值存到 j 變數，並將其減一，用來與前一個元素比對 

        while (j >= 0 && arr[j] > key) // 若 j 不小於 0 且前一個元素的值大於目前元素的值，則進入迴圈 
		{
            arr[j + 1] = arr[j];// 將前一個元素的值往右移動一位 
            j = j - 1;// 減少 j 的值，使其與目前元素繼續比對
        }

        arr[j + 1] = key;// 將目前元素插入到排序好的子序列中
    }
}

void merge_sort(int* arr, int l, int r) // 定義一個合併排序的函數，傳入參數包括一個整數數組arr
                                        // 數組的左邊界p，和右邊界q
{                                       
	if (l < r) // 如果左邊界小於右邊界，表示這個子數組還可以進一步切割
	{
		int m = (l + r) / 2;// 計算中間位置，進一步切割數組
		merge_sort(arr, l, m);  // 對左半邊子數組進行遞歸排序
		merge_sort(arr, m + 1, r); // 對右半邊子數組進行遞歸排序
		merge(arr, l, m, r);  // 合併左右子數組
	}
}

void merge(int* arr, int l, int m, int r) 
{
	int n1 = m - l + 1;// 計算左側陣列的大小
	int n2 = r - m;// 計算右側陣列的大小

	int* L = new int[n1+1];// 建立大小為 n1 的左側陣列
	int* R = new int[n2+1];// 建立大小為 n2 的右側陣列

	for (int i = 0; i < n1; i++) // 將原陣列 arr 中的元素複製到左側陣列 L 和右側陣列 R
	{
		L[i] = arr[l+i]; 
	}
	for (int i = 0; i < n2; i++) 
	{
		R[i] = arr[i+m+1]; 
	}


      L[n1] = R[n2] = INT_MAX; //final item is infinte large

     // 合併暫存陣列 L 和 R 回到 arr
     int i = 0, j = 0;
     for (int k = l; k <= r; k++) 
     {
         if (L[i] <= R[j]) 
         {
             arr[k] = L[i];
             i++;
         }
         else 
         {
             arr[k] = R[j];
             j++;
         }
     }
//    int i = 0, j = 0, k =p ;
//
//    while (i < n1 && j < n2) // 將左側陣列 L 和右側陣列 R 中的元素合併排序
//	{
//        if (L[i] <= R[j]) 
//		{
//            arr[k] = L[i];
//            i++;
//        } 
//		else 
//		{
//            arr[k] = R[j];
//            j++;
//        }
//        k++;
//    }
//
//    while (i < n1) // 將左側陣列 L 或右側陣列 R 中的剩餘元素添加到 arr 中
//	{
//        arr[k] = L[i];
//        i++;
//        k++;
//    }
//
//    while (j < n2) 
//	{
//        arr[k] = R[j];
//        j++;
//        k++;
//    }
	delete[] L;// 釋放動態分配的左側陣列的內存
    delete[] R;// 釋放動態分配的右側陣列的內存
}
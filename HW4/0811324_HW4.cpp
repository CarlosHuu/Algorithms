#include <iostream>
#include <random>
#include <chrono>
using namespace std;

void random_array(int* arr, int size);

void insertion_sort(int* arr, int size);

void merge_sort(int* arr, int l, int r);
void merge(int* arr, int l, int m, int r);

void maxHeapify(int* arr, int n, int i);
void buildMaxHeap(int* arr, int n);
void heap_sort(int* arr, int n);

int partition(int arr[], int low, int high);
void quick_Sort(int arr[], int low, int high);

int RandomizedPartition(int arr[], int low, int high) ;
void Random_quick_Sort(int arr[], int low, int high);

int main()
{
	int arr_size;
	while(1){
	
	cout << "Enter the input size: " ;
	cin >> arr_size;
			

        int* arr = new int[arr_size];
        random_array(arr, arr_size);

		// Measure Insertion Sort time
        auto start_insertion = chrono::high_resolution_clock::now();
        insertion_sort(arr, arr_size);
        auto end_insertion = chrono::high_resolution_clock::now();
        auto duration_insertion = chrono::duration_cast<chrono:: microseconds>(end_insertion - start_insertion);
        cout << "Insertion Sort with size " << arr_size << " took " << duration_insertion.count() << " microseconds." << endl;

		random_array(arr, arr_size);
		// Measure Merge Sort time
        auto start_merge = chrono::high_resolution_clock::now();
        merge_sort(arr, 0, arr_size - 1);
        auto end_merge = chrono::high_resolution_clock::now();
        auto duration_merge = chrono::duration_cast<chrono:: microseconds>(end_merge - start_merge);
        cout << "Merge Sort with size " << arr_size << " took " << duration_merge.count() << " microseconds." << endl;

		random_array(arr, arr_size);
		// Measure Heap Sort time
        auto start_heap = chrono::high_resolution_clock::now();
        heap_sort(arr, arr_size);
        auto end_heap = chrono::high_resolution_clock::now();
        auto duration_heap = chrono::duration_cast<chrono:: microseconds>(end_heap - start_heap);
        cout << "Heap Sort with size " << arr_size << " took " << duration_heap.count() << " microseconds." << endl;


        random_array(arr, arr_size);
		// Measure Quick Sort time
        auto start_Random_quick = chrono::high_resolution_clock::now();
        Random_quick_Sort(arr, 0, arr_size - 1);
        //  for (int i = 0 ; i <arr_size ; i++)
        //  {
        //      cout << arr[i] <<" ";
        //  }
        //  cout << endl;
        auto end_Random_quick = chrono::high_resolution_clock::now();
        auto duration_Random_quick = chrono::duration_cast<chrono:: microseconds>(end_Random_quick - start_Random_quick);
        cout << "Ramdom Quick Sort with size " << arr_size << " took " << duration_Random_quick.count() << " microseconds." << endl << endl;        
    }

	return 0;
}

void random_array(int* arr, int size)
{
    random_device rd; //隨機設備，創建一個名為rd的random_device對象。
    mt19937 gen(rd());  //亂數產生器，mt19937是一種隨機數生成器引擎，可以生成高品質的隨機數序列。
    uniform_int_distribution<int> dis(1, 100000);//表示生成一個在 1 到 100000 之間的均勻分布的隨機整數
    for (int i = 0; i < size; i++) 
	{
        arr[i] = dis(gen);
    }
}

void insertion_sort(int* arr, int size) //// 定義一個函式名稱為 "insertion_sort"，接收一個指向整數陣列的指標 "arr" 和陣列的大小 "size" 
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
	delete[] L;// 釋放動態分配的左側陣列的內存
    delete[] R;// 釋放動態分配的右側陣列的內存
}



void maxHeapify(int* arr, int n, int i) 
{
    int largest = i;// 初始化最大值的位置爲 i
    int left = 2*i + 1;// 左子節點的位置
    int right = 2*i + 2; // 右子節點的位置
    
    // 找出三個節點中最大值的位置
    if (left < n && arr[left] > arr[largest])// 如果左子節點比當前節點更大
        largest = left; // 則更新最大值的索引

    if (right < n && arr[right] > arr[largest])// 如果右子節點比當前節點更大
        largest = right;// 則更新最大值的索引
    // 如果最大值不是當前位置 i，交換兩者的值，然後遞迴進行最大堆化
    if (largest != i) {
        swap(arr[i], arr[largest]);// 則交換兩個元素，將最大值移到當前節點
        maxHeapify(arr, n, largest);
    }
}

void buildMaxHeap(int* arr, int n) // 建立最大堆，n 爲數組大小
{
    for (int i = n / 2 - 1; i >= 0; i--)// 從最後一個非葉子節點開始進行最大堆化，直到根節點位置
        maxHeapify(arr, n, i);
}

void heap_sort(int* arr, int n) // 堆排序，n 爲數組大小
{
    buildMaxHeap(arr, n);// 先建立最大堆

    for (int i = n-1; i >= 0; i--)  // 從最後一個元素開始，將最大元素移到數組末尾
    {
        swap(arr[0], arr[i]);// 將堆頂元素與當前未排序部分的最後一個元素交換
    
        maxHeapify(arr, i, 0);// 維護最大堆的性質 ， i = n--;
    }
}




int partition(int arr[], int low, int high) 
{
    int pivot = arr[high];  // 將最後一個元素作為基準點
    int i = low - 1;        // i 為小於基準點的元素的最後一個索引
    for (int j = low; j < high; j++) {
        // 如果當前元素小於等於基準點，則將 i 往後移動一位，並交換 i 和 j 所指的元素
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    // 最後將 i 往後移動一位，並交換 i 和 high 所指的元素
    swap(arr[i+1], arr[high]);
    return i+1;  // 回傳基準點所在的索引
}

int RandomizedPartition(int arr[], int low, int high) // 隨機切分，將基準點選擇隨機位置的元素
{
    srand(time(nullptr));// 使用 srand 和 time 函數來設置隨機種子
    int randomIndex = rand() % (high - low + 1) + low;// 隨機選擇一個位置，作為基準點
    swap(arr[randomIndex], arr[high]);// 將選擇的基準點放到區間的最右邊（也就是 high 的位置）
    return partition(arr, low, high);// 調用 partition 函數進行切分
}

void Random_quick_Sort(int arr[], int low, int high) 
{
    if (low < high) {
        int pi = RandomizedPartition(arr, low, high);  // 分割 arr[]
        Random_quick_Sort(arr, low, pi-1);  // 對分割後的左半部分排序
        Random_quick_Sort(arr, pi+1, high);  // 對分割後的右半部分排序
    }
}





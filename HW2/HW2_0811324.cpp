#include<stdlib.h>
#include<fstream>
#include<math.h>
#include<iostream>
#include<string>
#include<vector>
#include <algorithm>
#define MINUS_INFINITY -1e10 // 負無限大
using namespace std;

float Find_max_cross_subarray(int I[],float A[]);// 找到橫跨中點的最大子數列和
float Find_max_subarray(int I[],float A[],vector<float>&same);// 分治法找到最大子數列和
bool Equal (float a , float b);
int main()
{
	float max_sum; // 最大子數列和
	int I[2];// 儲存最大子數列的起點和終點


	
	string l;
	int line;
	ifstream input;// 讀取檔案
	input.open("data.txt");// 開啟檔案
	
 	if (input.fail()) // 如果檔案無法開啟
	{
	    cerr << "Cannot open the file." << endl;
	    exit (1);// 結束程式
    }
    
	while(getline(input,l))// 統計檔案行數
	{
		line++;
	}
	input.close();// 關閉檔案
	
	input.open("data.txt");// 再次開啟檔案
	float *A =new float[line];// 動態配置陣列
	
	vector <float>same;
	
	for (int i =0 ; i<2*line ;i++)// 將檔案內容存入陣列中
	{
		input >> A[i/2];
	}

	I[0] = 0;// 初始最大子數列的起點
	I[1] = line-1;// 初始最大子數列的終點
	max_sum = Find_max_subarray(I,A,same); // 使用分治法找到最大子數列和
	cout << "Maximum subarray start index: " << I[0]+1 << endl << "Maximum subarray finish index: " << I[1]+1 << endl << "subarray summation: " << max_sum << endl;
	
	cout << "index of possible combinations of the same sum: "<<endl;
	 


	int s= 0;
	vector <float>same_final_L;
	vector <float>same_final_R;
	for (float i=0 ; i<same.size();i=i+2)
	{	
	
		if(((same[i+1]-same[i]) == (I[1]-I[0])))//因為相同總和項可能會因為是在subbary的問題導致輸出錯的，因此這裡確保尺寸相同存入same_final
		{
			same_final_L.push_back(same[i]);
			same_final_R.push_back(same[i+1]);
			s++;
		}
		
	}
	// 以下將相同計算到的index進行刪除，並輸出最終結果
	sort(same_final_L.begin(), same_final_L.end());
	same_final_L.erase(unique(same_final_L.begin(), same_final_L.end()), same_final_L.end());
	sort(same_final_R.begin(), same_final_R.end());
	same_final_R.erase(unique(same_final_R.begin(), same_final_R.end()), same_final_R.end());

	auto iterA = same_final_L.begin();
    auto iterB = same_final_R.begin();
    while (iterA != same_final_L.end() && iterB != same_final_R.end()) 
	{
        cout << *iterA+1 << " " << *iterB+1 << endl;
        ++iterA;
        ++iterB;
    }


	
	if(s==0)//若沒相同項則輸出none
	cout << "NONE";

	input.close();// 關閉檔案
	delete []A;// 釋放陣列空間
	return 0;
}

float Find_max_cross_subarray(int I[],float A[])
{
	// 設定左、右、跨越中點三種情況的最大子數列和初始值
    float left_sum = MINUS_INFINITY;// 左半邊最大子數列和的初始值為負無限大
    float right_sum = MINUS_INFINITY;// 右半邊最大子數列和的初始值為負無限大
    float sum = 0; // 橫跨中點的最大子數列和的初始值為 0
    int left_max,right_max,i;

    for(i=I[2];i>=I[0];i--)// 從中點往左找最大子數列和
	{
        sum = sum + A[i];
        if(sum > left_sum)// 如果目前的子數列和比左邊大
		{
	        left_sum = sum;// 更新左邊最大子數列和
	        left_max = i;// 更新左邊最大子數列和的結束位置
        }
    }
    sum = 0;// 重設 sum 為 0，準備從中點往右找最大子數列和
    for(i=I[2]+1;i<=I[1];i++)// 從中點往右找最大子數列和
	{
    	sum = sum + A[i];// 加上當前元素，計算目前的子數列和
	    if(sum > right_sum)// 如果目前的子數列和比右邊大
		{
	        right_sum = sum;// 更新右邊最大子數列和
	        right_max = i;// 更新右邊最大子數列和的結束位置
	    }	
	}
	I[0] = left_max;// 更新最大子數列和的開始位置
	I[1] = right_max;// 更新最大子數列和的結束位置
	sum = left_sum + right_sum;// 計算橫跨中點的最大子數列和
	return sum; // 回傳最大子數列和
}

float Find_max_subarray(int I[],float A[],vector<float>&same)
{

	float sum,mid;// 設定變數
	// 設定左、右、跨越中點三種情況的子數列起始與結束位置的陣列
	int left[2];
	int right[2];
	int cross[3];
	
	float left_sum,right_sum,cross_sum;// 設定左、右、跨越中點三種情況的最大子數列和
	if(I[0] == I[1])// 如果子數列只有一個元素
	{
	    sum = A[I[0]];// 直接回傳該元素
	}
	
	else 
	{
		// 取中間的 index，並分割成左半部分和右半部分
	    mid = floor((I[0]+I[1])/2);// 計算中點
	    left[0] = I[0];
	    left[1] = mid;
	    right[0] = mid + 1;
	    right[1] = I[1];
		// 設定橫跨中點的 subarray 範圍
	    cross[0] = I[0];
	    cross[1] = I[1];
	    cross[2] = mid;
	    // 以遞迴方式找到左半部分、右半部分和橫跨中點的 subarray 的總和
		left_sum = Find_max_subarray(left,A,same);
	    right_sum = Find_max_subarray(right,A,same);
	    cross_sum = Find_max_cross_subarray(cross,A);
	    
	    
		// 比較三者的總和，找到最大的 subarray 的總和以及它的位置 pushback皆是相同尺寸相同總和回傳
		if((left_sum >= right_sum)&&(left_sum >= cross_sum))
		{
			sum = left_sum;
	        I[0] = left[0];
	        I[1] = left[1];
	        if ( Equal (right_sum,left_sum))
//			if(left_sum == right_sum)//當作左半總和等於右半總和
	        {
	        	if((left[1]-left[0])>(right[1]-right[0]))//左半尺寸大於右半尺寸
	        	{	//回傳右半部分
					I[0] = right[0];
	    		    I[1] = right[1];
				}
				if((left[1]-left[0])==(right[1]-right[0]))
	        	{	
					same.push_back(right[0]);
	    		    same.push_back(right[1]);
				}
				
			}
			if ( Equal (left_sum ,cross_sum))
//			if(left_sum == cross_sum)//當左半總和等於橫跨總和
	        {
	        	if((left[1]-left[0])>(cross[1]-cross[0]))//左半尺寸大於橫跨尺寸
	        	{	//回傳橫跨部分
					I[0] = cross[0];
	    		    I[1] = cross[1];
	    		}
	    		if((left[1]-left[0])==(cross[1]-cross[0]))
	        	{	
					same.push_back(cross[0]);
	    		    same.push_back(cross[1]);
	    		}
			}
	    }
	    if((right_sum >= left_sum)&&(right_sum >= cross_sum))
		{
			sum = right_sum;
	        I[0] = right[0];
	        I[1] = right[1];
	        if ( Equal (right_sum,left_sum))
//			if(right_sum == left_sum)//當右半總和等於左半總和
	        {
	        	if((right[1]-right[0])>(left[1]-left[0]))//右半尺寸大於左半尺寸
	        	{	//回傳左半部分
					I[0] = left[0];
	    		    I[1] = left[1];
				}
				if((right[1]-right[0])==(left[1]-left[0]))
	        	{	 
					same.push_back(left[0]);
	    		    same.push_back(left[1]);
				}
			}	
			if ( Equal (right_sum,cross_sum))
//			if(right_sum == cross_sum)//當右半總和等於橫跨總和
	        {
	        	if((right[1]-right[0])>(cross[1]-cross[0]))//左半尺寸大於橫跨尺寸
	        	{	//回傳橫跨部分
					I[0] = cross[0];
	    		    I[1] = cross[1];
				}
			 	if((right[1]-right[0])==(cross[1]-cross[0]))
	        	{	
					same.push_back(cross[0]);
	    		    same.push_back(cross[1]);
				}
			}
	    }
	    if((cross_sum >= left_sum)&&(cross_sum >= right_sum))
//	    else
		{
	        sum = cross_sum;
	        I[0] = cross[0];
	        I[1] = cross[1];
	        if ( Equal (left_sum,cross_sum))
//	        if(cross_sum == left_sum)//橫跨總和等於左半總和
	        {
	        	if((cross[1]-cross[0])>(left[1]-left[0]))//橫跨尺寸大於左半尺寸
	        	{	//回傳左半部分
					I[0] = left[0];
	    		    I[1] = left[1];
				}
				if((cross[1]-cross[0])==(left[1]-left[0]))
	        	{	
					same.push_back(left[0]);
	    		    same.push_back(left[1]);
				}
			}
			if ( Equal (right_sum,cross_sum))
//			if(cross_sum == right_sum)//橫跨總和等於右半總和
	        {
	        	if((cross[1]-cross[0])>(right[1]-right[0]))//橫跨尺寸大於右半尺寸
	        	{	//回傳右半部分
					I[0] = right[0];
	    		    I[1] = right[1];
				}
				if((cross[1]-cross[0])==(right[1]-right[0]))//橫跨尺寸大於右半尺寸
	        	{	//回傳右半部分
					same.push_back(right[0]);
	    		    same.push_back(right[1]);
				}
			}
	    }

	    
	}
	return sum;
}

bool Equal (float a , float b)
{
	if( (a-b>-0.0000001) && (a-b < 0.0000001))
		return true;
	else
		return false;
}

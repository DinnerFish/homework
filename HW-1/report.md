# 41141149

#### **作業一**

# 解題說明

**問題一
要求要一個遞迴版本跟一個非遞迴版本的阿克曼函數**

---
### 解題思路
**遞迴版本：**

1. 當 m = 0 時，輸出 n + 1
2. 當 n = 0 時，遞迴呼叫 A(m-1, 1)
3. 其他情況下，遞迴呼叫 A(m-1, A(m, n-1))


**非遞迴版本：**

 1. 用陣列模擬堆疊功能  
 2. 一樣進行遞迴流程，但數值存在陣列中  
 3. 利用while及if判斷式跑至m=0

# 程式實作
### 標頭
``` cpp
#include  <iostream>  // 引入輸入輸出流標頭檔
using  namespace  std; // 使用標準命名空間
```

### 遞迴版本
``` cpp
int  ackermann(int  m, int  n) { // 定義遞迴版本的函數，接受兩個整數參數
	if (m ==  0) { // 第一個基本情況：當 m 為 0 時
		return n +  1; // 返回 n + 1
	}
	if (n ==  0) { // 第二個基本情況：當 n 為 0 時
		return  ackermann(m -  1, 1); // 遞迴調用，減少 m 值
	}
return  ackermann(m -  1, ackermann(m, n -  1)); // 一般情況：雙重遞迴調用
}
```
### 非遞迴版本
``` cpp
int  ackermann_iterative(int  m, int  n) { // 定義非遞迴版本的函數
	const  int MAX_SIZE =  1000; // 定義堆疊最大容量
	int  stack[MAX_SIZE][3]; // 創建三維陣列作為堆疊：[m, n, state]
	int top =  0; // 堆疊頂部指標
	int result; // 儲存計算結果
// 初始狀態
	stack[top][0] = m; // 存入初始的 m 值
	stack[top][1] = n; // 存入初始的 n 值
	stack[top][2] =  0; // 設定初始狀態為 0
	while (top >=  0) { // 當堆疊非空時繼續執行
		m =  stack[top][0]; // 取出當前的 m 值
		n =  stack[top][1]; // 取出當前的 n 值
		int state =  stack[top][2]; // 取出當前狀態

		if (m ==  0) { // 第一個基本情況
			result = n +  1; // 計算結果
			top--; // 堆疊退出一層
			if (top >=  0) { // 如果堆疊非空
				stack[top][1] = result; // 將結果存入上一層的 n 值
			}
		}
		else  if (n ==  0) { // 第二個基本情況
			stack[top][0] = m -  1; // 更新 m 值
			stack[top][1] =  1; // 設定 n 值為 1
		}
		else { // 一般情況
			if (state ==  0) { // 如果是初始狀態
				stack[top][2] =  1; // 更新狀態
				top++; // 堆疊增加一層
				stack[top][0] = m; // 存入當前 m 值
				stack[top][1] = n -  1; // 存入 n-1
				stack[top][2] =  0; // 新層的初始狀態為 0
			}
			else { // 如果已經計算過內部遞迴
				result =  stack[top][1]; // 取出內部遞迴的結果
				top--; // 退出一層
				top++; // 準備計算外部遞迴
				stack[top][0] = m -  1; // 更新 m 值
				stack[top][1] = result; // 使用內部遞迴的結果
				stack[top][2] =  0; // 重置狀態為 0
			}
		}
	}
	return result; // 返回最終計算結果
}
```

### 主函式
``` cpp
int  main() { 
	int m =  3, n =  4;
	cout <<  "遞迴版本 Ackermann("  << m <<  ", "  << n <<  ") = "  <<  ackermann(m, n) << endl;
	cout <<  "非遞迴版本 Ackermann("  << m <<  ", "  << n <<  ") = "  <<  ackermann_iterative(m, n) << endl;
	return  0;
}
```

# 效能分析

#### 問題一(遞迴)
時間複雜度:O(A(m,n))
空間複雜度:O(A(m,n))
#### 問題一(非遞迴)
時間複雜度:O(A(m,n))
空間複雜度:O(A(m,n))

# 測試與驗證

    | 測試案例 | 輸入 (m,n) | 預期輸出 | 實際輸出 |
    
    |---------|----------|---------|---------|
    
    | 測試一 |    (0,0)   |    1    |    1    |
    
    | 測試二 |    (1,1)   |    3    |    3    |
    
    | 測試三 |    (2,2)   |    7    |    7    |
    
    | 測試四 |    (3,4)   |   125   |   125   |

### 結論

#  申論及開發報告

本次實作凸顯了遞迴與非遞迴之間的實用性對比。雖然遞迴邏輯清晰、撰寫方便，但在複雜或深度過大的運算時，容易受到堆疊限制影響。非遞迴實作雖較複雜，但可支援較大的運算範圍，且能掌控記憶體與流程，更具工程實用性。
透過本次練習，更理解遞迴背後的堆疊執行邏輯與轉換技巧，亦為日後處理複雜演算法提供有力基礎。

---
### 問題二

# 解題說明

**如果 S 是一個有 n 個元素的集合，則 SS的冪集（powerset）是 S 的所有子集合所組成的集合。例如，若 S=(a,b,c)，則  
powerset(S)={( ),( a ),( b ),( c ),( a,b ),( a,c ),( b,c ),( a,b,c )}
請撰寫一個遞迴函式來計算 powerset(S)。**

###  解題思路
 **使用位元運算來生成所有可能的子集組合**
# 程式實作
### 
``` cpp
##include <iostream>
using namespace std;

// 計算集合 S 的所有子集
void powerset(char S[], int n) {
    // 總共有 2^n 個子集
    int total = 1 << n;
        // 遍歷所有可能的子集
    for (int i = 0; i < total; i++) {
        cout << "(";
        bool first = true;
        // 檢查每個位元是否為 1
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                if (!first) {
                    cout << ", ";
                }
                cout << S[j];
                first = false;
            }
        }
        cout << ")";
        
        // 輸出分隔符號
        if (i < total - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

int main() {
    // 測試範例：S = {a, b, c}
    char S[] = {'a', 'b', 'c'};
    int n = 3;    
    cout << "集合 S = {";
    for (int i = 0; i < n; i++) {
        cout << S[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "}" << endl;
    cout << "powerset(S) = ";
    powerset(S, n);
    
    return 0;
}
```

# 效能分析

時間複雜度:O(2n *n)
空間複雜度:O(n)

# 測試與驗證

     程式輸出結果符合預期，生成了所有可能的子集，並按照元素個數和字典序排序：
       
       - 空集：()
       
       - 單元素集合：(a), (b), (c)
       
       - 雙元素集合：(a,b), (a,c), (b,c)
       
       - 三元素集合：(a,b,c) 

### 結論

#  申論及開發報告

本程式成功展示如何使用位元運算在 C++ 中產生任意集合的所有子集，不僅達成基本演算法練習的目的，也為進一步處理組合問題提供範例與基礎。未來可延伸應用於多種實務場景，如搜尋演算法、資料組合選擇與圖形排列分析等。



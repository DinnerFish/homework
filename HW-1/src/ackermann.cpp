#include <iostream>    // 引入輸入輸出流標頭檔
using namespace std;    // 使用標準命名空間

// 遞迴版本的 Ackermann 函數
int ackermann(int m, int n) {    // 定義遞迴版本的函數，接受兩個整數參數
    if (m == 0) {    // 第一個基本情況：當 m 為 0 時
        return n + 1;    // 返回 n + 1
    }
    if (n == 0) {    // 第二個基本情況：當 n 為 0 時
        return ackermann(m - 1, 1);    // 遞迴調用，減少 m 值
    }
    return ackermann(m - 1, ackermann(m, n - 1));    // 一般情況：雙重遞迴調用
}

// 非遞迴版本的 Ackermann 函數
int ackermann_iterative(int m, int n) {    // 定義非遞迴版本的函數
    const int MAX_SIZE = 1000;    // 定義堆疊最大容量
    int stack[MAX_SIZE][3];    // 創建三維陣列作為堆疊：[m, n, state]
    int top = 0;    // 堆疊頂部指標
    int result;    // 儲存計算結果
    
    // 初始狀態
    stack[top][0] = m;    // 存入初始的 m 值
    stack[top][1] = n;    // 存入初始的 n 值
    stack[top][2] = 0;    // 設定初始狀態為 0
    
    while (top >= 0) {    // 當堆疊非空時繼續執行
        m = stack[top][0];    // 取出當前的 m 值
        n = stack[top][1];    // 取出當前的 n 值
        int state = stack[top][2];    // 取出當前狀態
        
        if (m == 0) {    // 第一個基本情況
            result = n + 1;    // 計算結果
            top--;    // 堆疊退出一層
            if (top >= 0) {    // 如果堆疊非空
                stack[top][1] = result;    // 將結果存入上一層的 n 值
            }
        }
        else if (n == 0) {    // 第二個基本情況
            stack[top][0] = m - 1;    // 更新 m 值
            stack[top][1] = 1;    // 設定 n 值為 1
        }
        else {    // 一般情況
            if (state == 0) {    // 如果是初始狀態
                stack[top][2] = 1;    // 更新狀態
                top++;    // 堆疊增加一層
                stack[top][0] = m;    // 存入當前 m 值
                stack[top][1] = n - 1;    // 存入 n-1
                stack[top][2] = 0;    // 新層的初始狀態為 0
            }
            else {    // 如果已經計算過內部遞迴
                result = stack[top][1];    // 取出內部遞迴的結果
                top--;    // 退出一層
                top++;    // 準備計算外部遞迴
                stack[top][0] = m - 1;    // 更新 m 值
                stack[top][1] = result;    // 使用內部遞迴的結果
                stack[top][2] = 0;    // 重置狀態為 0
            }
        }
    }
    
    return result;    // 返回最終計算結果
}

int main() {    // 主函數
    int m = 3, n = 4;    // 設定測試值
    cout << "遞迴版本 Ackermann(" << m << ", " << n << ") = " << ackermann(m, n) << endl;    // 輸出遞迴版本結果
    cout << "非遞迴版本 Ackermann(" << m << ", " << n << ") = " << ackermann_iterative(m, n) << endl;    // 輸出非遞迴版本結果
    return 0;    // 程式結束
}
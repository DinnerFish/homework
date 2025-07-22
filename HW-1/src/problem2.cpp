#include <iostream>

using namespace std;

// 計算二進位中1的個數
int countBits(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// 比較兩個子集的順序
bool compareSubsets(int i, int j, int n) {
    // 首先比較元素個數
    int countI = countBits(i);
    int countJ = countBits(j);
    if (countI != countJ) {
        return countI < countJ;
    }
    
    // 如果元素個數相同，按二進位表示的大小反向排序
    return i > j;
}

// 計算集合 S 的所有子集
void powerset(char S[], int n) {
    // 總共有 2^n 個子集
    int total = 1 << n;
    
    // 創建索引陣列並初始化
    int indices[1 << 10]; // 假設n最大為10
    for (int i = 0; i < total; i++) {
        indices[i] = i;
    }
    
    // 對索引進行排序
    for (int i = 0; i < total; i++) {
        for (int j = i + 1; j < total; j++) {
            if (compareSubsets(indices[i], indices[j], n)) {
                // 交換索引
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }
    
    // 按排序後的順序輸出子集
    for (int k = 0; k < total; k++) {
        int i = indices[k];
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
        if (k < total - 1) {
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
    
    cout << "powerset(S) = {";
    powerset(S, n);
    
    return 0;
}

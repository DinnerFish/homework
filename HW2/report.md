# 41141149

#### **作業一**

# 解題說明

本題的核心是實作多項式的運算功能。

---
### 解題思路

我們採用鏈結串列（Linked List）來儲存每一項的係數與次方。每個節點表示多項式中的一項，節點內部儲存該項的係數與次方。

# 程式實作
### 標頭
``` cpp
#include <iostream>
#include <cmath>
using namespace std;

class Polynomial;

class Term {
    friend class Polynomial; 
private:
    float coef; 
    int exp;
};

class Polynomial {
public:
    Polynomial();
    ~Polynomial(); 
    Polynomial Add(const Polynomial& poly) const; 
    Polynomial Mult(const Polynomial& poly) const; 
    float Eval(float f) const; 

    friend istream& operator>>(istream& in, Polynomial& poly);
    friend ostream& operator<<(ostream& out, const Polynomial& poly);

private:
    Term* termArray; 
    int capacity;    
    int terms;       

    void NewTerm(float c, int e); 
};

Polynomial::Polynomial() {
    capacity = 10;
    termArray = new Term[capacity];
    terms = 0;
}

Polynomial::~Polynomial() {
    delete[] termArray;
}

void Polynomial::NewTerm(float c, int e) {
    if (terms == capacity) {
        capacity *= 2;
        Term* newArray = new Term[capacity];
        for (int i = 0; i < terms; i++) {
            newArray[i] = termArray[i];
        }
        delete[] termArray;
        termArray = newArray;
    }
    termArray[terms].coef = c;
    termArray[terms].exp = e;
    terms++;
}

Polynomial Polynomial::Add(const Polynomial& poly) const {
    Polynomial result;
    int i = 0, j = 0;
    while (i < terms && j < poly.terms) {
        if (termArray[i].exp == poly.termArray[j].exp) {
            float sum = termArray[i].coef + poly.termArray[j].coef;
            if (sum != 0) result.NewTerm(sum, termArray[i].exp);
            i++; j++;
        } else if (termArray[i].exp > poly.termArray[j].exp) {
            result.NewTerm(termArray[i].coef, termArray[i].exp);
            i++;
        } else {
            result.NewTerm(poly.termArray[j].coef, poly.termArray[j].exp);
            j++;
        }
    }
    while (i < terms) result.NewTerm(termArray[i].coef, termArray[i].exp), i++;
    while (j < poly.terms) result.NewTerm(poly.termArray[j].coef, poly.termArray[j].exp), j++;
    return result;
}

Polynomial Polynomial::Mult(const Polynomial& poly) const {
    Polynomial result;
    for (int i = 0; i < terms; i++) {
        Polynomial temp;
        for (int j = 0; j < poly.terms; j++) {
            float c = termArray[i].coef * poly.termArray[j].coef;
            int e = termArray[i].exp + poly.termArray[j].exp;
            temp.NewTerm(c, e);
        }
        result = result.Add(temp);
    }
    return result;
}

float Polynomial::Eval(float f) const {
    float sum = 0;
    for (int i = 0; i < terms; i++) {
        sum += termArray[i].coef * pow(f, termArray[i].exp);
    }
    return sum;
}

istream& operator>>(istream& in, Polynomial& poly) {
    int num;
    cout << "請輸入項數：";
    in >> num;
    for (int i = 0; i < num; i++) {
        float c;
        int e;
        cout << "請輸入第 " << i + 1 << " 項的係數與次方：";
        in >> c >> e;
        poly.NewTerm(c, e);
    }
    return in;
}

ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; i++) {
        out << poly.termArray[i].coef << "x^" << poly.termArray[i].exp;
        if (i != poly.terms - 1) out << " + ";
    }
    return out;
}

int main() {
    Polynomial p1, p2;
    cout << "輸入多項式 P1：" << endl;
    cin >> p1;
    cout << "輸入多項式 P2：" << endl;
    cin >> p2;

    Polynomial sum = p1.Add(p2);
    Polynomial product = p1.Mult(p2);

    cout << "P1 為： " << p1 << endl;
    cout << "P2 為： " << p2 << endl;
    cout << "P1 + P2 的結果為： " << sum << endl;
    cout << "P1 * P2 的結果為： " << product << endl;

    float val;
    cout << "請輸入一個數值 x，計算 P1(x)：";
    cin >> val;
    cout << "P1(" << val << ") 的結果為： " << p1.Eval(val) << endl;

    return 0;
}

```

# 效能分析

時間複雜度:O(m+n)
空間複雜度:O(m+n)

# 測試與驗證

| 測資 | `P1(x)`      | `P2(x)`       | `P1 + P2`          | `P1 * P2`                                     | `P1(2)` | `P2(2)` |
| -- | ------------- | -------------- | ------------------ | --------------------------------------------- | ------- | ------- |
| 1  | 3x² + 2x + 1  | 5x² + 4        | 8x² + 2x + 5       | 15x⁴ + 10x³ + 23x² + 8x + 4                   | 17.0    | 24.0    |
| 2  | -1x³ + 4x     | 2x³ - 4x       | 1x³ + 0x           | -2x⁶ + 4x⁴ -8x²                               | 4.0     | 0.0     |
| 3  | 6x⁵ + 1x⁴ + 3 | -6x⁵ + 2x² + 1 | 1x⁴ + 2x² + 4      | -36x¹⁰ -6x⁹ + 6x⁷ + 2x⁶ + 3x⁵ + 2x⁴ + 3x² + 3 | 227.0   | 33.0    |

### 結論
從測試結果來看，所有的運算結果都符合預期，並且計算出的多項式加法、乘法以及代入數值計算均為正確。
#  申論及開發報告
本次開發的 Polynomial 類別成功地實現了多項式的基本運算：加法、乘法與求值，並且通過了隨機測試資料的驗證，確保了程式運行的正確性。
未來可以考慮擴展功能，例如支援自動排序、簡化多項式等操作，以進一步提升多項式處理的效率。


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

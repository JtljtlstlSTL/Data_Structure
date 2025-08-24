#include <algorithm>

class Term {
  friend class Polynomial;

 private:
  float coef;//系数
  int exp;//指数
};

class Polynomial {
 public:
  Polynomial();
  Polynomial Add(Polynomial b);
  Polynomial Mult(Polynomial poly);
  float Eval(float f);

  void NewTem(float coef, int exp);

 private:
  Term* termArray;
  int capacity;
  int terms;
};

void Polynomial::NewTem(float const coef, int const exp) {
  if (terms == capacity) {
    capacity   *= 2;
    Term* temp  = new Term[capacity];
    std::copy(termArray, termArray + terms, temp);
    delete[] termArray;
    termArray = temp;
  }
  termArray[terms].coef = coef;
  termArray[terms].exp  = exp;
  terms++;
}

//多项式相加
//时间复杂度为O(n+m)，n和m分别为两个多项式的项数
Polynomial Polynomial::Add(Polynomial b) {
  Polynomial c;
  int aPos = 0, bPos = 0;
  while (aPos < terms && bPos < b.terms) {
    if (termArray[aPos].exp == b.termArray[bPos].exp) {
      float t = termArray[aPos].coef + b.termArray[bPos].coef;
      if (t) {
        c.NewTem(t, termArray[aPos].exp);
      }
      aPos++;
      bPos++;
    } else if (termArray[aPos].exp < b.termArray[bPos].exp) {
      c.NewTem(termArray[aPos].coef, termArray[aPos].exp);
      aPos++;
    } else {
      c.NewTem(b.termArray[bPos].coef, b.termArray[bPos].exp);
      bPos++;
    }
  }
  for (; aPos < terms; aPos++) {
    c.NewTem(termArray[aPos].coef, termArray[aPos].exp);
  }
  for (; bPos < b.terms; bPos++) {
    c.NewTem(b.termArray[bPos].coef, b.termArray[bPos].exp);
  }
  return c;
}

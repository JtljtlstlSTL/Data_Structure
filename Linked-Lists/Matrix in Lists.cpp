#include <algorithm>
#include <iostream>
#include <istream>

struct Triple {
  int row, col, value;
};

class Matrix;

class MatrixNode {
  friend class Matrix;
  friend std::istream& operator>>(std::istream&, Matrix&);

 private:
  MatrixNode *down, *right;
  bool head;
  union {
    MatrixNode* next;
    Triple triple;
  };
  MatrixNode(bool, Triple*);
};

MatrixNode::MatrixNode(bool b, Triple* t) {
  head = b;
  if (b) {
    right = down = this;
  } else {
    triple = *t;
  }
}

class Matrix {
  friend std::istream& operator>>(std::istream&, Matrix&);

 public:
  ~Matrix();

 private:
  MatrixNode* headnode;
  static MatrixNode* av;
};

//读入一个稀疏矩阵
std::istream& operator>>(std::istream& is, Matrix& matrix) {
  Triple s;
  is >> s.row >> s.col >> s.value;
  int p = std::max(s.row, s.col);
  if (p == 0) {
    matrix.headnode->right = matrix.headnode;
    return is;
  }
  MatrixNode** head = new MatrixNode*[p];
  for (int i = 0; i < p; i++) {
    head[i] = new MatrixNode(true, 0);
  }
  int currentRow   = 0;
  MatrixNode* last = head[0];

  for (int i = 0; i < s.value; i++) {
    Triple t;
    is >> t.row >> t.col >> t.value;
    if (t.row > currentRow) {
      last->right = head[currentRow];
      currentRow  = t.row;
      last        = head[currentRow];
    }
    last = last->right = new MatrixNode(false, &t);
    head[t.col]->next = head[t.col]->next->down = last;
  }

  last->right = head[currentRow];
  for (int i = 0; i < s.col; i++) {
    head[i]->next->down = head[i];
  }
  for (int i = 0; i < p - 1; i++) {
    head[i]->next = head[i + 1];
  }
  head[p - 1]->next      = matrix.headnode;
  matrix.headnode->right = head[0];
  delete[] head;
  return is;
}

//删除稀疏矩阵
Matrix::~Matrix() {
  if (!headnode) {
    return;
  }
  MatrixNode* x   = headnode->right;
  headnode->right = av;
  av              = headnode;
  while (x != headnode) {
    MatrixNode* y = x->right;
    x->right      = av;
    av            = y;
    x             = x->next;
  }
  headnode = 0;
}

#include <algorithm>

class MatrixTerm {
  friend class SparseMatrix;

 private:
  int row, col,
      value;  //行、列、值
};

class SparseMatrix {
 public:
  SparseMatrix(int r, int c, int t);
  SparseMatrix Transpose();
  SparseMatrix FastTranspose();
  SparseMatrix Add(SparseMatrix b);
  SparseMatrix Multiply(SparseMatrix b);

  void ChangeSizelD(int const newSize);
  void StoreSum(int const sum, int const r, int const c);

 private:
  int rows, cols, terms, capacity;
  MatrixTerm* smArray;
};

//矩阵转置
//时间复杂度为O(terms*col)
SparseMatrix SparseMatrix::Transpose() {
  SparseMatrix b(cols, rows, terms);
  if (terms > 0) {
    int currentB = 0;
    for (int c = 0; c < cols; c++) {
      for (int i = 0; i < terms; i++) {
        if (smArray[i].col == c) {
          b.smArray[currentB].row     = c;
          b.smArray[currentB].col     = smArray[i].row;
          b.smArray[currentB++].value = smArray[i].value;
        }
      }
    }
  }
  return b;
}

//快速矩阵转置
//时间复杂度为O(terms+col)
SparseMatrix SparseMatrix::FastTranspose() {
  SparseMatrix b(cols, rows, terms);
  if (terms > 0) {
    int i         = 0;
    int* rowSize  = new int[cols];  //每一列的非零元素个数
    int* rowStart = new int[cols];  //每一列转置后元素的起始位置
    std::fill(rowSize, rowSize + cols, 0);
    for (i = 0; i < terms; i++) {
      rowSize[smArray[i].col]++;
    }
    rowStart[0] = 0;
    for (i = 1; i < cols; i++) {
      rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
    }
    for (i = 0; i < terms; i++) {
      int j              = rowStart[smArray[i].col];
      b.smArray[j].row   = smArray[i].col;
      b.smArray[j].col   = smArray[i].row;
      b.smArray[j].value = smArray[i].value;
      rowStart[smArray[i].col]++;
    }
    delete[] rowSize;
    delete[] rowStart;
  }
  return b;
}

//改变矩阵大小
void SparseMatrix::ChangeSizelD(int const newSize) {
  if (newSize < terms) {
    throw "New size must be>=number of terms";
  }
  MatrixTerm* temp = new MatrixTerm[newSize];
  std::copy(smArray, smArray + terms, temp);
  delete[] smArray;
  smArray  = temp;
  capacity = newSize;
}

void SparseMatrix::StoreSum(int const sum, int const r, int const c) {
  if (sum != 0) {
    if (terms == capacity) {
      ChangeSizelD(capacity * 2);
      smArray[terms].row   = r;
      smArray[terms].col   = c;
      smArray[terms].value = sum;
    }
  }
}

//矩阵乘法
SparseMatrix SparseMatrix::Multiply(SparseMatrix b) {
  if (cols != b.rows) {
    throw "Icompatible matrices";
  }
  SparseMatrix bXpose = b.FastTranspose();
  SparseMatrix d(rows, b.cols, 0);
  int currRowIndex = 0, currRowBegin = 0, currRowA = smArray[0].row;
  if (terms == capacity) {
    ChangeSizelD(terms + 1);
  }
  bXpose.ChangeSizelD(bXpose.terms + 1);
  smArray[terms].row          = rows;
  bXpose.smArray[b.terms].row = b.cols;
  bXpose.smArray[b.terms].col = -1;
  int sum                     = 0;
  while (currRowIndex < terms) {
    int currColB     = bXpose.smArray[0].row;
    int currColIndex = 0;
    while (currColIndex < bXpose.terms) {
      if (smArray[currRowIndex].row != currRowA) {
        d.StoreSum(sum, currRowA, currColB);
        sum      = 0;
        currColB = currRowBegin;
        while (bXpose.smArray[currColIndex].row == currColB) {
          currColIndex++;
        }
        currColB = bXpose.smArray[currColIndex].row;
      } else if (bXpose.smArray[currColIndex].col != currColB) {
        d.StoreSum(sum, currRowA, currColB);
        sum          = 0;
        currRowIndex = currRowBegin;
        currColB     = bXpose.smArray[currColIndex].row;
      } else {
        if (smArray[currRowIndex].col < bXpose.smArray[currColIndex].col) {
          currRowIndex++;
        } else if (smArray[currRowIndex].col == bXpose.smArray[currRowIndex].col) {
          sum += smArray[currRowIndex].value * bXpose.smArray[currColIndex].value;
          currRowIndex++;
          currColIndex++;
        } else {
          currColIndex++;
        }
      }
    }
  }
  while (smArray[currRowIndex].row == currRowA) {
    currRowIndex++;
    currRowBegin = currRowIndex;
    currRowA     = smArray[currRowIndex].row;
  }
  return d;
}

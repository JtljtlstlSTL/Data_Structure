//P155-156
#include <algorithm>
#include <fstream>
#include <iostream>

class Enode {
  friend void Equivalence();

 public:
  Enode(int d = 0) {
    data = d;
    link = 0;
  }
  Enode(int d, Enode* l) {
    data = d;
    link = l;
  }

 private:
  int data;
  Enode* link;
};

void Equivalence() {
  std::ifstream inFile("equiv.in", std::ios::in);
  if (!inFile) {
    throw "Cannot open input file.";
  }
  int i, j, n;
  inFile >> n;
  Enode** first = new Enode*[n];
  bool* out     = new bool[n];
  std::fill(first, first + n, nullptr);
  std::fill(out, out + n, false);

  inFile >> i >> j;
  while (inFile.good()) {
    first[i] = new Enode(j, first[i]);
    first[j] = new Enode(i, first[j]);
    inFile >> i >> j;
  }

  for (i = 0; i < n; i++) {
    if (!out[i]) {
      std::cout << '\n' << "A new class:" << i;
      out[i]     = true;
      Enode* x   = first[i];
      Enode* top = 0;
      while (1) {
        while (x) {
          j = x->data;
          if (!out[j]) {
            std::cout << "," << j;
            out[j]   = true;
            Enode* y = x->link;
            x->link  = top;
            top      = x;
            x        = y;
          } else {
            x = x->link;
          }
        }
        if (!top) {
          break;
        }
        x   = first[top->data];
        top = top->link;
      }
    }
  }
  for (i = 0; i < n; i++) {
    while (first[i]) {
      Enode* delnode = first[i];
      first[i]       = delnode->link;
      delete delnode;
    }
  }
  delete[] first;
  delete[] out;
}
